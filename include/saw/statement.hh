//
// statement.hh for saw
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef SAW_STATEMENT_HH_
# define SAW_STATEMENT_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <string>
# include <vector>
# include <boost/bind.hpp>
# include <saw/detail/owner.hh>
# include <saw/detail/proxy.hh>
# include <saw/parameter.hh>
# include <saw/database.hh>
# include <saw/value.hh>
# include <saw/types.hh>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace saw
{

  class Statement : protected detail::Owner<SharedStatement>
  {
    public:
      // types

      typedef detail::Proxy<Value const&> Proxy;
      typedef std::string ColumnName;
      typedef std::vector<ColumnName> ColumnNames;


      // constructors

      Statement();
      Statement(Database db, const char* query);


      // accessors

      bool busy() const;
      bool ready() const;
      bool empty() const;

      int current_row_index() const;
      Row& current_row() const;

      int columns_number() const;
      const ColumnName& column_name(int column) const;
      const ColumnNames& columns_names() const;

      Database database() const;
      sqlite3_stmt* raw_data() const;


      // parameter binding

      Proxy operator[](const ParameterKey& key);
      Proxy operator[](const ParameterName& name);
      Proxy operator[](const ParameterIndex& param);

      friend Statement& operator<<(Statement& stmt, const Parameter& param);
      friend Statement& operator<<(Statement& stmt, const Parameters& params);

      Statement& bind(const Parameter& param);
      Statement& bind(const Parameters& params);
      Statement& bind(const ParameterKey& key, const Value& value);
      Statement& bind(const ParameterName& name, const Value& value);
      Statement& bind(const ParameterIndex& index, const Value& value);


      // execution

      Rows exec();
      Rows exec(const Parameters& params);
      void exec(const RowCallback& callback);
      void exec(const RowCallback& callback, const Parameters& params);

      RowRange result();
      RowRange result(const Parameters& params);

      bool step();
      void reset();


    private:
      // internal

      friend class RowIterator;

      RowIterator next();


      // data

      Database db_;
  };

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <saw/statement.hxx>



#endif /* !SAW_STATEMENT_HH_ */
