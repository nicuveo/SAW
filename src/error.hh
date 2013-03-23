//
// error.hh for saw
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef SAW_ERROR_HH_
# define SAW_ERROR_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <saw/exceptions.hh>
# include <saw/types.hh>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace saw
{

  void check(Database d, int sqlite_code);

}



#endif /* !SAW_ERROR_HH_ */
