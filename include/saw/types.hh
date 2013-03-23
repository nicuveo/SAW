//
// types.hh for saw
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef SAW_TYPES_HH_
# define SAW_TYPES_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <vector>
# include <cstdlib>
# include <utility>
# include <sqlite3.h>
# include <boost/blank.hpp>
# include <boost/function.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace saw
{

  // data types

  typedef unsigned char     Byte;
  typedef sqlite3_int64     Integer;
  typedef double            Float;
  typedef std::string       Text;
  class                     Blob;
  typedef boost::blank      Null;


  // exported base classes

  class Database;
  class Statement;
  class Value;
  class Row;
  class RowIterator;


  // exported composite classes

  typedef std::vector<Row> Rows;
  typedef std::vector<Value> Values;

  typedef std::pair<RowIterator, RowIterator> RowRange;
  typedef boost::function1<void, Row&> RowCallback;


  // internal classes

  class SharedDatabase;
  class SharedStatement;
  class SharedRow;

}



#endif /* !SAW_TYPES_HH_ */
