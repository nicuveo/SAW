//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include "shared/shared_statement.hh"
#include "error.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace saw
{


  // -tors

  SharedStatement::SharedStatement(Database db, const char* statement)
    : row_index_(-1)
  {
    check(db, sqlite3_prepare_v2(db.raw_data(), statement, -1, &data_, 0));
    resize(sqlite3_column_count(data_));
  }

  SharedStatement::~SharedStatement()
  {
    sqlite3_finalize(data_);
  }



  // mutators

  bool
  SharedStatement::step(const Statement& parent)
  {
    Database db = parent.database();

    row_invalidity_.raise();
    switch (sqlite3_step(data()))
    {
      case SQLITE_DONE:
        reset();
        return false;

      case SQLITE_ROW:
        row_ = Row(parent, ++row_index_, row_invalidity_);
        return true;

      default:
        check(db, reset());
    }

    return false;

  }

  int
  SharedStatement::reset()
  {
    row_ = Row();
    row_index_ = -1;
    return sqlite3_reset(data_);
  }



  // helpers

  std::string
  SharedStatement::fetch(int i) const
  {
    return sqlite3_column_name(data(), i);
  }

  void
  SharedStatement::fail(int) const
  {
    throw OutOfRange("column: out of range index");
  }



}
