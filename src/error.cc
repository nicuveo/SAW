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

#include <nauths/saw/database.hh>
#include "error.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace saw
{


  void
  check(Database d, int sqlite_code)
  {
    if (sqlite_code == SQLITE_OK)
      return;

    const char* msg = sqlite3_errmsg(d.raw_data());

    switch (sqlite_code)
    {
      case SQLITE_NOMEM:      throw BadAlloc    (msg);
      case SQLITE_RANGE:      throw OutOfRange  (msg);

      case SQLITE_INTERNAL:   throw LogicError  (msg);
      case SQLITE_ABORT:      throw LogicError  (msg);
      case SQLITE_READONLY:   throw LogicError  (msg);
      case SQLITE_NOTFOUND:   throw LogicError  (msg);
      case SQLITE_CONSTRAINT: throw LogicError  (msg);
      case SQLITE_MISMATCH:   throw LogicError  (msg);
      case SQLITE_MISUSE:     throw LogicError  (msg);
      case SQLITE_NOLFS:      throw LogicError  (msg);
      case SQLITE_FORMAT:     throw LogicError  (msg);

      case SQLITE_ERROR:      throw RuntimeError(msg);
      case SQLITE_PERM:       throw RuntimeError(msg);
      case SQLITE_BUSY:       throw RuntimeError(msg);
      case SQLITE_LOCKED:     throw RuntimeError(msg);
      case SQLITE_INTERRUPT:  throw RuntimeError(msg);
      case SQLITE_IOERR:      throw RuntimeError(msg);
      case SQLITE_CORRUPT:    throw RuntimeError(msg);
      case SQLITE_FULL:       throw RuntimeError(msg);
      case SQLITE_CANTOPEN:   throw RuntimeError(msg);
      case SQLITE_PROTOCOL:   throw RuntimeError(msg);
      case SQLITE_EMPTY:      throw RuntimeError(msg);
      case SQLITE_SCHEMA:     throw RuntimeError(msg);
      case SQLITE_TOOBIG:     throw RuntimeError(msg);
      case SQLITE_AUTH:       throw RuntimeError(msg);
      case SQLITE_NOTADB:     throw RuntimeError(msg);

      default:                throw RuntimeError(msg);
    }
  }


}
