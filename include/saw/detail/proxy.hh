//
// proxy.hh for saw
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef SAW_PROXY_HH_
# define SAW_PROXY_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <boost/function.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace saw
{

  namespace detail
  {

    template <typename T>
    class Proxy
    {
      public:
        // types

        typedef boost::function1<void, T> Callback;


        // constructor

        Proxy(const Callback& cb);


        // usage

        void operator=(T value);


      private:
        // data

        Callback cb_;
    };

  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <saw/detail/proxy.hxx>



#endif /* !SAW_PROXY_HH_ */
