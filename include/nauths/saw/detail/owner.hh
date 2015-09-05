//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef SAW_OWNER_HH_
# define SAW_OWNER_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <memory>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace saw
{

  namespace detail
  {

    template <typename T>
    class Owner : public std::shared_ptr<T>
    {
      public:
        T&             data()       { return *this->get(); }
        T const&       data() const { return *this->get(); }
        T&     mutable_data() const { return *this->get(); }
        T const& const_data() const { return *this->get(); }
    };

  }

}



#endif /* !SAW_OWNER_HH_ */
