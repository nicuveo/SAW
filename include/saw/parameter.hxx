//
// parameter.hxx for saw
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef SAW_PARAMETER_HXX_
# define SAW_PARAMETER_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <saw/parameter.hh>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace saw
{


  template <typename T>
  inline Parameters
  plist(T const& x)
  {
    Parameters res = x;
    return res;
  }


}



#endif /* !SAW_PARAMETER_HXX_ */
