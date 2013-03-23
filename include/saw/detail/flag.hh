//
// flag.hh for saw
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef SAW_FLAG_HH_
# define SAW_FLAG_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <boost/weak_ptr.hpp>
# include <boost/shared_ptr.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace saw
{

  namespace detail
  {

    class Flag : private boost::shared_ptr<int>
    {
      public:
        friend class Watcher;

        bool raised() const;

        void raise();
        void lower();
    };

    class Watcher : private boost::weak_ptr<int>
    {
      public:
        Watcher();
        Watcher(Flag f);

        bool valid() const;
        bool obsolete() const;
    };

  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <saw/detail/flag.hxx>



#endif /* !SAW_FLAG_HH_ */
