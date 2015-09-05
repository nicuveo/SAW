//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef SAW_BLOB_HH_
# define SAW_BLOB_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <vector>
# include <ostream>
# include <nauths/saw/types.hh>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace saw
{


  class Blob : public std::vector<Byte>
  {
    public:
      // types

      typedef std::vector<Byte> Super;


      // constructors

      Blob();
      Blob(const char* data);
      Blob(const char* data, int size);
      Blob(const unsigned char* data);
      Blob(const unsigned char* data, int size);
      Blob(const std::string& data);
      Blob(const std::vector<Byte>& data);


      // operators

      friend std::ostream& operator<<(std::ostream&, const Blob&);
  };


}



#endif /* !SAW_BLOB_HH_ */
