//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <cstdlib>
#include <iostream>
#include <nauths/saw/saw.hh>

#define BOOST_TEST_MODULE cache
#include <boost/test/included/unit_test.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local code

namespace
{

  class Cache : public saw::detail::Cache<Cache, int>
  {
    public:
      typedef saw::detail::Cache<Cache, int> Super;

      Cache(int size)
        : Super(size)
      {
      }

    private:
      int fetch(int) const
      {
        return 42;
      }

      void fail(int i) const
      {
        throw i;
      }
  };

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

BOOST_AUTO_TEST_CASE(cache_00)
{
  Cache c1(2);
  Cache c2(0);

  BOOST_REQUIRE_EQUAL(2, c1.size());
  BOOST_REQUIRE_EQUAL(0, c2.size());

  c2.resize(2);

  BOOST_REQUIRE_EQUAL(2, c2.size());

  BOOST_REQUIRE(not c1.all_cached());
  BOOST_REQUIRE(not c1.cached(0));
  BOOST_REQUIRE(not c1.cached(1));
  BOOST_REQUIRE(not c2.all_cached());
  BOOST_REQUIRE(not c2.cached(0));
  BOOST_REQUIRE(not c2.cached(1));

  int a1 = c1.get(0);
  int a2 = c2[0];

  BOOST_REQUIRE_EQUAL(42, a1);
  BOOST_REQUIRE_EQUAL(42, a2);
  BOOST_REQUIRE(not c1.all_cached());
  BOOST_REQUIRE(    c1.cached(0));
  BOOST_REQUIRE(not c1.cached(1));
  BOOST_REQUIRE(not c2.all_cached());
  BOOST_REQUIRE(    c2.cached(0));
  BOOST_REQUIRE(not c2.cached(1));

  int b1 = c1.get(1);
  int b2 = c2[1];

  BOOST_REQUIRE_EQUAL(42, b1);
  BOOST_REQUIRE_EQUAL(42, b2);
  BOOST_REQUIRE(    c1.all_cached());
  BOOST_REQUIRE(    c1.cached(0));
  BOOST_REQUIRE(    c1.cached(1));
  BOOST_REQUIRE(    c2.all_cached());
  BOOST_REQUIRE(    c2.cached(0));
  BOOST_REQUIRE(    c2.cached(1));
}

BOOST_AUTO_TEST_CASE(cache_01)
{
  Cache c(2);

  BOOST_REQUIRE(not c.all_cached());
  BOOST_REQUIRE(not c.cached(0));
  BOOST_REQUIRE(not c.cached(1));

  const std::vector<int>& v = c.values();

  BOOST_REQUIRE_EQUAL(42, v[0]);
  BOOST_REQUIRE_EQUAL(42, v[1]);
  BOOST_REQUIRE(c.all_cached());
  BOOST_REQUIRE(c.cached(0));
  BOOST_REQUIRE(c.cached(1));
}

BOOST_AUTO_TEST_CASE(cache_02)
{
  const Cache c(2);

  BOOST_REQUIRE(not c.all_cached());
  BOOST_REQUIRE(not c.cached(0));
  BOOST_REQUIRE(not c.cached(1));

  const std::vector<int>& v = c.values();

  BOOST_REQUIRE_EQUAL(42, v[0]);
  BOOST_REQUIRE_EQUAL(42, v[1]);
  BOOST_REQUIRE(not c.all_cached());
  BOOST_REQUIRE(not c.cached(0));
  BOOST_REQUIRE(not c.cached(1));
}
