//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef SAW_PARAMETER_HH_
# define SAW_PARAMETER_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <vector>
# include <utility>
# include <boost/assign.hpp>
# include <nauths/saw/value.hh>
# include <nauths/saw/types.hh>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Macros

# define SAW_PLIST(X) ::saw::plist(boost::assign::list_of< ::saw::Parameter > X)



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace saw
{

  // types

  typedef int ParameterIndex;
  typedef const char* ParameterName;
  typedef boost::variant<ParameterIndex, ParameterName> ParameterKey;
  typedef std::pair<ParameterKey, Value> Parameter;
  typedef std::vector<Parameter> Parameters;


  // functions

  template <typename T>
  Parameters plist(T const& x);

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <nauths/saw/parameter.hxx>



#endif /* !SAW_PARAMETER_HH_ */
