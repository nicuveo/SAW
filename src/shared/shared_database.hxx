//
// shared_database.hxx for saw
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef SAW_SHARED_DATABASE_HXX_
# define SAW_SHARED_DATABASE_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "shared/shared_database.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace saw
{


  inline sqlite3*
  SharedDatabase::data() const
  {
    return data_;
  }


}



#endif /* !SAW_SHARED_DATABASE_HXX_ */
