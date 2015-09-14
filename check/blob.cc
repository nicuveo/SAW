//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <cstdlib>
#include <sstream>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "nauths/saw/saw.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

using namespace saw;

#define CHECK(a, b) BOOST_CHECK_EQUAL(a, b)

BOOST_AUTO_TEST_SUITE(blob)

BOOST_AUTO_TEST_CASE(stable)
{
  const int size = 16;
  const char data[size + 1] = "f00ff00ff00ff00f";
  const char* sdata = data;
  const unsigned char* udata = reinterpret_cast<const unsigned char*>(sdata);
  const std::string str(sdata);

  Blob b1(sdata);
  Blob b2(udata);
  Blob b3(sdata, size);
  Blob b4(udata, size);
  Blob b5(str);
  Blob b6(static_cast<Blob::Super>(b1));

  CHECK(b1, b2);
  CHECK(b1, b3); CHECK(b2, b3);
  CHECK(b1, b4); CHECK(b2, b4); CHECK(b3, b4);
  CHECK(b1, b5); CHECK(b2, b5); CHECK(b3, b5); CHECK(b4, b5);
  CHECK(b1, b6); CHECK(b2, b6); CHECK(b3, b6); CHECK(b4, b6); CHECK(b5, b6);

  std::stringstream s;

  BOOST_REQUIRE_NO_THROW(s << b1);
  BOOST_REQUIRE_NO_THROW(s << b2);
  BOOST_REQUIRE_NO_THROW(s << b3);
  BOOST_REQUIRE_NO_THROW(s << b4);
  BOOST_REQUIRE_NO_THROW(s << b5);
  BOOST_REQUIRE_NO_THROW(s << b6);
}

BOOST_AUTO_TEST_SUITE_END()
