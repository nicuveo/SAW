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

#define BOOST_TEST_MODULE value
#include <boost/test/included/unit_test.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

using namespace saw;

BOOST_AUTO_TEST_CASE(value_00)
{
  Value v1;
  Value v2 = Value(Null());

  BOOST_REQUIRE(v1.null());
  BOOST_REQUIRE_EQUAL(Integer(0), v1.as_integer());
  BOOST_REQUIRE_EQUAL(Float(0),   v1.as_float()  );
  BOOST_REQUIRE_EQUAL(Text(),     v1.as_text()   );
  BOOST_REQUIRE_EQUAL(Blob(),     v1.as_blob()   );

  BOOST_REQUIRE(v2.null());
  BOOST_REQUIRE_EQUAL(Integer(0), v2.as_integer());
  BOOST_REQUIRE_EQUAL(Float(0),   v2.as_float()  );
  BOOST_REQUIRE_EQUAL(Text(),     v2.as_text()   );
  BOOST_REQUIRE_EQUAL(Blob(),     v2.as_blob()   );
}

BOOST_AUTO_TEST_CASE(value_01)
{
  Value v(Integer(1234));

  BOOST_REQUIRE(not v.null());
  BOOST_REQUIRE_EQUAL(Integer(1234), v.as_integer());
  BOOST_REQUIRE_EQUAL(Float(1234),   v.as_float()  );
  BOOST_REQUIRE_EQUAL(Text("1234"),  v.as_text()   );
  BOOST_REQUIRE_EQUAL(Blob("1234"),  v.as_blob()   );
}

BOOST_AUTO_TEST_CASE(value_02)
{
  Value v1(Float(2345));
  Value v2(2345.f);
  Value v3(2345.);

  BOOST_REQUIRE(not v1.null());
  BOOST_REQUIRE_EQUAL(Integer(2345), v1.as_integer());
  BOOST_REQUIRE_EQUAL(Float(2345),   v1.as_float()  );
  BOOST_REQUIRE_EQUAL(Text("2345"),  v1.as_text()   );
  BOOST_REQUIRE_EQUAL(Blob("2345"),  v1.as_blob()   );

  BOOST_REQUIRE(not v2.null());
  BOOST_REQUIRE_EQUAL(Integer(2345), v2.as_integer());
  BOOST_REQUIRE_EQUAL(Float(2345),   v2.as_float()  );
  BOOST_REQUIRE_EQUAL(Text("2345"),  v2.as_text()   );
  BOOST_REQUIRE_EQUAL(Blob("2345"),  v2.as_blob()   );

  BOOST_REQUIRE(not v3.null());
  BOOST_REQUIRE_EQUAL(Integer(2345), v3.as_integer());
  BOOST_REQUIRE_EQUAL(Float(2345),   v3.as_float()  );
  BOOST_REQUIRE_EQUAL(Text("2345"),  v3.as_text()   );
  BOOST_REQUIRE_EQUAL(Blob("2345"),  v3.as_blob()   );
}

BOOST_AUTO_TEST_CASE(value_03)
{
  Value v(Text("3456"));

  BOOST_REQUIRE(not v.null());
  BOOST_REQUIRE_EQUAL(Integer(3456), v.as_integer());
  BOOST_REQUIRE_EQUAL(Float(3456),   v.as_float()  );
  BOOST_REQUIRE_EQUAL(Text("3456"),  v.as_text()   );
  BOOST_REQUIRE_EQUAL(Blob("3456"),  v.as_blob()   );
}

BOOST_AUTO_TEST_CASE(value_04)
{
  Value v(Blob("4567"));

  BOOST_REQUIRE(not v.null());
  BOOST_REQUIRE_EQUAL(Integer(4567), v.as_integer());
  BOOST_REQUIRE_EQUAL(Float(4567),   v.as_float()  );
  BOOST_REQUIRE_EQUAL(Text("4567"),  v.as_text()   );
  BOOST_REQUIRE_EQUAL(Blob("4567"),  v.as_blob()   );
}
