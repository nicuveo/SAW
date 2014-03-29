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

#include <cstring>
#include <iomanip>
#include <nauths/saw/blob.hh>
#include "misc/foreach.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace saw
{


  // constructors

  Blob::Blob()
  {
  }

  Blob::Blob(const char* data)
    : Super(reinterpret_cast<const unsigned char*>(data),
            reinterpret_cast<const unsigned char*>(data) + strlen(data))
  {
  }

  Blob::Blob(const char* data, int size)
    : Super(reinterpret_cast<const unsigned char*>(data),
            reinterpret_cast<const unsigned char*>(data) + size)
  {
  }

  Blob::Blob(const unsigned char* data)
    : Super(data, data + strlen(reinterpret_cast<const char*>(data)))
  {
  }

  Blob::Blob(const unsigned char* data, int size)
    : Super(data, data + size)
  {
  }

  Blob::Blob(const std::string& data)
    : Super(data.begin(), data.end())
  {
  }

  Blob::Blob(const std::vector<Byte>& data)
    : Super(data)
  {
  }



  // operators

  std::ostream&
  operator<<(std::ostream& ostr, const Blob& blob)
  {
    saw_foreach (Byte b, blob)
      ostr << std::hex << b;
    return ostr;
  }


}
