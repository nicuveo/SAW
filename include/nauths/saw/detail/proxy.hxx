//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef SAW_PROXY_HXX_
# define SAW_PROXY_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <nauths/saw/detail/proxy.hh>



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
