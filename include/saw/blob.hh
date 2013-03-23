//
// blob.hh for saw
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef SAW_BLOB_HH_
# define SAW_BLOB_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <vector>
# include <ostream>
# include <saw/types.hh>



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
