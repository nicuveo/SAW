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

#include "shared/shared_database.hh"
#include "error.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace saw
{


  SharedDatabase::SharedDatabase(const char* database)
  {
    if (sqlite3_open(database, &data_) != SQLITE_OK)
      throw RuntimeError("could not open database");
  }

  SharedDatabase::~SharedDatabase()
  {
    sqlite3_close(data_);
  }


}
