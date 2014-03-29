//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef SAW_SHARED_DATABASE_HH_
# define SAW_SHARED_DATABASE_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <sqlite3.h>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace saw
{

  class SharedDatabase
  {
    public:
      // -tors

      SharedDatabase(const char* database);
      ~SharedDatabase();


      // accessors

      sqlite3* data() const;


    private:
      // data

      sqlite3* data_;
  };

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "shared_database.hxx"



#endif /* !SAW_SHARED_DATABASE_HH_ */
