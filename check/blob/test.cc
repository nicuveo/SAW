//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <cstdlib>
#include <iostream>
#include <saw/saw.hh>

#define BOOST_TEST_MODULE blob
#include <boost/test/included/unit_test.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

using namespace saw;

#define CHECK(a, b) BOOST_CHECK_EQUAL(a, b)

BOOST_AUTO_TEST_CASE(blob_00)
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

  BOOST_REQUIRE_NO_THROW(std::cout << b1);
  BOOST_REQUIRE_NO_THROW(std::cout << b2);
  BOOST_REQUIRE_NO_THROW(std::cout << b3);
  BOOST_REQUIRE_NO_THROW(std::cout << b4);
  BOOST_REQUIRE_NO_THROW(std::cout << b5);
  BOOST_REQUIRE_NO_THROW(std::cout << b6);
}
