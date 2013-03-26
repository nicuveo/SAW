//
// row.cc for saw
// Made by nicuveo <crucuny@gmail.com>
//



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <boost/bind.hpp>
#include <saw/exceptions.hh>
#include <saw/row.hh>
#include "misc/foreach.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local code

namespace saw
{

  namespace
  {


    inline Value get_null(sqlite3_stmt*, int)
    {
      return Value();
    }

    inline Value get_integer(sqlite3_stmt* stmt, int index)
    {
      return Value(Integer(sqlite3_column_int64(stmt, index)));
    }

    inline Value get_float(sqlite3_stmt* stmt, int index)
    {
      return Value(Float(sqlite3_column_double(stmt, index)));
    }

    Value get_text(sqlite3_stmt* stmt, int index)
    {
      int bytes = sqlite3_column_bytes(stmt, index);
      const char* data = reinterpret_cast<const char*>(sqlite3_column_text(stmt, index));
      return Value(Text(data, bytes));
    }

    Value get_blob(sqlite3_stmt* stmt, int index)
    {
      int bytes = sqlite3_column_bytes(stmt, index);
      const Byte* data = reinterpret_cast<const Byte*>(sqlite3_column_blob(stmt, index));
      return Value(Blob(data, bytes));
    }


  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace saw
{


  // constructor

  Row::Row()
  {
  }

  Row::Row(const Statement& stmt, int index, detail::Flag flag)
    : stmt_(stmt), watcher_(flag), index_(index)
  {
    resize(columns_number());
  }



  // helpers

  Value
  Row::fetch(int i) const
  {
    if (stmt_.empty() or outdated())
      std::abort();

    sqlite3_stmt* stmt = stmt_.raw_data();
    int type = sqlite3_column_type(stmt, i);

    switch (type)
    {
      case SQLITE_INTEGER: return get_integer(stmt, i);
      case SQLITE_FLOAT:   return get_float(stmt, i);
      case SQLITE_TEXT:    return get_text(stmt, i);
      case SQLITE_BLOB:    return get_blob(stmt, i);
      case SQLITE_NULL:    return get_null(stmt, i);
      default:
        throw InternalError("fetch value: unsupported type");
    }

    return Value();
  }

  void
  Row::fail(int) const
  {
    throw OutOfRange("row: out of range index");
  }


}
