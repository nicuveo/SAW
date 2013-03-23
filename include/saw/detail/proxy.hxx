//
// proxy.hxx for saw
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef SAW_PROXY_HXX_
# define SAW_PROXY_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <saw/detail/proxy.hh>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace saw
{

  namespace detail
  {


    // constructor

    template <typename T>
    Proxy<T>::Proxy(const Callback& cb)
      : cb_(cb)
    {
    }


    // usage

    template <typename T>
    inline void
    Proxy<T>::operator=(T value)
    {
      cb_(value);
    }


  }

}



#endif /* !SAW_PROXY_HXX_ */
