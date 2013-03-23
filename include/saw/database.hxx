//
// database.hxx for saw
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef SAW_DATABASE_HXX_
# define SAW_DATABASE_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <saw/database.hh>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace saw
{


  // accessors

  inline bool
  Database::connected() const
  {
    return *this;
  }


}



#endif /* !SAW_DATABASE_HXX_ */
