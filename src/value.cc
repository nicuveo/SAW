//
// value.cc for saw
// Made by nicuveo <crucuny@gmail.com>
//



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <saw/value.hh>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace saw
{


  // constructors

  Value::Value(Integer x)
    : Super(x)
  {
  }

  Value::Value(Float x)
    : Super(x)
  {
  }

  Value::Value(Text x)
    : Super(x)
  {
  }

  Value::Value(Blob x)
    : Super(x)
  {
  }

  Value::Value(Null x)
    : Super(x)
  {
  }

  Value::Value()
  {
  }



  // helper constructors

  Value::Value(int x)
    : Super(Integer(x))
  {
  }

  Value::Value(float x)
    : Super(Float(x))
  {
  }

  Value::Value(const char* x)
    : Super(Text(x))
  {
  }


}
