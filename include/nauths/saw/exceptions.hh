//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef SAW_EXCEPTIONS_HH_
# define SAW_EXCEPTIONS_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <stdexcept>
# include <sqlite3.h>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Macros

# define SAW_EXCEPTION(PARENT, NAME)              \
  class NAME : public PARENT, public Exception    \
  {                                               \
    public:                                       \
      NAME(const char* msg)                       \
        : PARENT(msg)                             \
      {                                           \
      }                                           \
                                                  \
      const char* what() const throw()            \
      {                                           \
        return PARENT::what();                    \
      }                                           \
  }                                               \



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace saw
{

  // base class

  class Exception
  {
    public:
      virtual const char* what() const throw() = 0;
  };


  // error classes

  SAW_EXCEPTION(std::runtime_error, BadAlloc);
  SAW_EXCEPTION(std::logic_error,   LogicError);
  SAW_EXCEPTION(std::out_of_range,  OutOfRange);
  SAW_EXCEPTION(std::runtime_error, RuntimeError);
  SAW_EXCEPTION(std::logic_error,   InternalError);

}



#endif /* !SAW_EXCEPTIONS_HH_ */
