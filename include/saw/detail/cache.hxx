//
// cache.hxx for saw
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef SAW_CACHE_HXX_
# define SAW_CACHE_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <saw/detail/cache.hh>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace saw
{

  namespace detail
  {


    // constructors

    template <typename E, typename T>
    Cache<E, T>::Cache(int size)
      : data_(size)
    {
      check_.resize(size, true);
    }



    // accessors

    template <typename E, typename T>
    inline bool
    Cache<E, T>::all_cached() const
    {
      return check_.none();
    }

    template <typename E, typename T>
    inline bool
    Cache<E, T>::cached(int index) const
    {
      return not check_[index];
    }

    template <typename E, typename T>
    inline int
    Cache<E, T>::size() const
    {
      return data_.size();
    }



    // cached access

    template <typename E, typename T>
    inline typename Cache<E, T>::Value const&
    Cache<E, T>::operator[](int index)
    {
      return get(index);
    }

    template <typename E, typename T>
    typename Cache<E, T>::Value const&
    Cache<E, T>::get(int index)
    {
      return load(index).Cache<E, T>::data_[index];
    }

    template <typename E, typename T>
    typename Cache<E, T>::Values const&
    Cache<E, T>::values()
    {
      return load().Cache<E, T>::data_;
    }



    // direct access

    template <typename E, typename T>
    inline typename Cache<E, T>::Value
    Cache<E, T>::operator[](int index) const
    {
      return get(index);
    }

    template <typename E, typename T>
    inline typename Cache<E, T>::Value
    Cache<E, T>::get(int index) const
    {
      return cached(index) ? data_[index] : fetch(index);
    }

    template <typename E, typename T>
    typename Cache<E, T>::Values
    Cache<E, T>::values() const
    {
      Values res = data_;

      for (int i = 0; i < size(); ++i)
        if (not cached(i))
          res[i] = get(i);

      return res;
    }



    // mutators

    template <typename E, typename T>
    typename Cache<E, T>::Exact&
    Cache<E, T>::load()
    {
      if (not all_cached())
        for (int i = 0; i < size(); ++i)
          load(i);
      return *static_cast<Exact*>(this);
    }

    template <typename E, typename T>
    typename Cache<E, T>::Exact&
    Cache<E, T>::load(int index)
    {
      if (not cached(index))
      {
        data_[index] = self().get(index);
        check_.reset(index);
      }
      return *static_cast<Exact*>(this);
    }


    template <typename E, typename T>
    void
    Cache<E, T>::resize(int newsize)
    {
      data_.resize(newsize);
      check_.resize(newsize, true);
    }



    // helper

    template <typename E, typename T>
    Cache<E, T> const&
    Cache<E, T>::self()
    {
      return *this;
    }


  }

}



#endif /* !SAW_CACHE_HXX_ */
