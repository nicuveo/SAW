//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <nauths/saw/statement.hh>
#include <nauths/saw/row_iterator.hh>
#include "shared/shared_statement.hh"
#include "error.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local code

namespace saw
{

  namespace
  {


    class KeyVisitor : public boost::static_visitor<Statement&>
    {
      public:
        KeyVisitor(Statement& stmt, const Value& value)
          : stmt_(stmt), value_(value)
        {
        }

        template <typename T>
        inline Statement& operator()(T const& key) const
        {
          return stmt_.bind(key, value_);
        }

      private:
        Statement& stmt_;
        const Value& value_;
    };

    class BindVisitor : public boost::static_visitor<int>
    {
      public:
        BindVisitor(sqlite3_stmt* stmt, int index)
          : stmt_(stmt), index_(index)
        {
        }

        inline int operator()(Null) const
        {
          return sqlite3_bind_null(stmt_, index_);
        }

        inline int operator()(Integer value) const
        {
          return sqlite3_bind_int64(stmt_, index_, value);
        }

        inline int operator()(Float value) const
        {
          return sqlite3_bind_double(stmt_, index_, value);
        }

        inline int operator()(const Text& value) const
        {
          return sqlite3_bind_text(stmt_, index_, value.c_str(), value.size(), SQLITE_TRANSIENT);
        }

        inline int operator()(const Blob& value) const
        {
          return sqlite3_bind_blob(stmt_, index_, &value[0], value.size(), SQLITE_TRANSIENT);
        }

      private:
        sqlite3_stmt* stmt_;
        int index_;
    };


  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace saw
{


  // constructors

  Statement::Statement()
  {
  }

  Statement::Statement(Database db, const char* query)
    : db_(db)
  {
    if (not db.connected())
      throw LogicError("statement: disconnected database");

    Owner<SharedStatement>::reset(new SharedStatement(db, query));
  }



  // accessors

  int
  Statement::current_row_index() const
  {
    return data().current_row_index();
  }

  Row&
  Statement::current_row() const
  {
    return mutable_data().current_row();
  }


  int
  Statement::columns_number() const
  {
    return data().size();
  }

  Statement::ColumnName const&
  Statement::column_name(int column) const
  {
    return mutable_data()[column];
  }

  Statement::ColumnNames const&
  Statement::columns_names() const
  {
    return mutable_data().values();
  }


  sqlite3_stmt*
  Statement::raw_data() const
  {
    return empty() ? 0 : data().data();
  }


  // parameter binding

  Statement&
  Statement::bind(const Parameters& ps)
  {
    for (const Parameter& p : ps)
      bind(p);
    return *this;
  }

  Statement&
  Statement::bind(const ParameterKey& pk, const Value& value)
  {
    return boost::apply_visitor(KeyVisitor(*this, value), pk);
  }

  Statement&
  Statement::bind(const ParameterName& name, const Value& value)
  {
    if (empty())
      throw LogicError("bind: empty statement");

    int index = sqlite3_bind_parameter_index(raw_data(), name);

    if (index == 0)
      throw OutOfRange("out of range parameter index");

    return bind(index, value);
  }

  Statement&
  Statement::bind(const ParameterIndex& pi, const Value& value)
  {
    if (empty())
      throw LogicError("bind: empty statement");

    boost::apply_visitor(BindVisitor(raw_data(), pi), value);
    return *this;
  }



  // execution

  Rows
  Statement::exec()
  {
    Rows res;

    for (Row& r : result())
      res.push_back(r.load());

    return res;
  }

  Rows
  Statement::exec(const Parameters& ps)
  {
    return bind(ps).exec();
  }

  void
  Statement::exec(const RowCallback& rcb)
  {
    for (Row& r : result())
      rcb(r);
  }


  RowRange
  Statement::result()
  {
    if (empty())
      throw LogicError("result: empty statement");

    if (busy())
      throw LogicError("result: busy statement (recursive call?)");

    return std::make_pair(next(), RowIterator());
  }

  RowRange
  Statement::result(const Parameters& ps)
  {
    return bind(ps).result();
  }


  bool
  Statement::step()
  {
    if (empty())
      throw LogicError("step: empty statement");

    return data().step(*this);
  }

  void
  Statement::reset()
  {
    if (empty())
      throw LogicError("reset: empty statement");

    data().reset();
  }



  // internal

  RowIterator
  Statement::next()
  {
    return step() ? RowIterator(*this) : RowIterator();
  }


}
