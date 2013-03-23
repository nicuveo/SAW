//
// flag.hxx for saw
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef SAW_FLAG_HXX_
# define SAW_FLAG_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <saw/detail/flag.hh>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local code

namespace saw
{

  namespace detail
  {

    namespace local
    {

      inline void noop(int*)
      {
      }

    }

  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace saw
{

  namespace detail
  {

    inline bool
    Flag::raised() const
    {
      return (*this);
    }


    inline void
    Flag::raise()
    {
      reset(reinterpret_cast<int*>(42), local::noop);
    }

    inline void
    Flag::lower()
    {
      reset();
    }


    inline Watcher::Watcher()
    {
    }

    inline Watcher::Watcher(Flag f)
      : boost::weak_ptr<int>(f)
    {
    }


    inline bool
    Watcher::valid() const
    {
      return lock();
    }

    inline bool
    Watcher::obsolete() const
    {
      return not valid();
    }

  }

}





#endif /* !SAW_FLAG_HXX_ */
