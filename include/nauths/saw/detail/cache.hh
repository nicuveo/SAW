//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef SAW_CACHE_HH_
# define SAW_CACHE_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <vector>
# include <boost/dynamic_bitset.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace saw
{

  namespace detail
  {

    template <typename E, typename T>
    class Cache
    {
      public:
        // types

        typedef T Value;
        typedef E Exact;
        typedef std::vector<Value> Values;
        typedef boost::dynamic_bitset<> Check;


        // constructors

        Cache(int size = 0);


        // accessors

        bool all_cached() const;
        bool cached(int index) const;
        int size() const;


        // cached access

        Value const& operator[](int index);
        Value const& get(int index);
        Values const& values();


        // direct access

        Value operator[](int index) const;
        Value get(int index) const;
        Values values() const;


        // mutators

        Exact& load();
        Exact& load(int index);

        void resize(int newsize);


      protected:
        // data fetching

        virtual Value fetch(int index) const = 0;
        virtual void fail(int index) const = 0;


      private:
        // helper

        const Cache& self();
        const Cache& verify(int index) const;


        // data

        Values data_;
        Check check_;
    };

  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <nauths/saw/detail/cache.hxx>



#endif /* !SAW_CACHE_HH_ */
