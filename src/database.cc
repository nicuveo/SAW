//
// database.cc for saw
// Made by nicuveo <crucuny@gmail.com>
//



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <saw/row_iterator.hh>
#include <saw/statement.hh>
#include <saw/database.hh>
#include "shared/shared_database.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace saw
{


  // constructors

  Database::Database()
  {
  }

  Database::Database(const char* database)
  {
    connect(database);
  }


  // accessors

  Statement
  Database::make(const char* query) const
  {
    return Statement(*this, query);
  }


  sqlite3*
  Database::raw_data() const
  {
    return (*this) ? data().data() : 0;
  }



  // mutators

  void
  Database::connect(const char* database)
  {
    reset(new SharedDatabase(database));
  }

  void
  Database::disconnect()
  {
    reset();
  }



  // execution

  Rows
  Database::exec(const char* query) const
  {
    return make(query).exec();
  }

  Rows
  Database::exec(const char* query, const Parameters& params) const
  {
    return make(query).exec(params);
  }

  void
  Database::exec(const char* query, const RowCallback& callback) const
  {
    return make(query).exec(callback);
  }

  void
  Database::exec(const char* query, const RowCallback& callback, const Parameters& params) const
  {
    return make(query).exec(callback, params);
  }


  RowRange
  Database::result(const char* query) const
  {
    return make(query).result();
  }

  RowRange
  Database::result(const char* query, const Parameters& params) const
  {
    return make(query).result(params);
  }



}
