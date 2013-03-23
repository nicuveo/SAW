//
// shared_statement.cc for saw
// Made by nicuveo <crucuny@gmail.com>
//



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <iostream>
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

    switch (sqlite3_step(data()))
    {
      case SQLITE_DONE:
        reset();
        return false;

      case SQLITE_ROW:
        row_invalidity_.raise();
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



}
