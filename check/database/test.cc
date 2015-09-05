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
#include <iostream>
#include <nauths/saw/saw.hh>

#define BOOST_TEST_MODULE database
#include <boost/test/included/unit_test.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

BOOST_AUTO_TEST_CASE(database_00)
{
  saw::Database d1("test.db");
  saw::Database d2;

  BOOST_REQUIRE(    d1.connected());
  BOOST_REQUIRE(not d2.connected());

  d1.disconnect();
  d2.connect("test.db");

  BOOST_REQUIRE(not d1.connected());
  BOOST_REQUIRE(    d2.connected());
}

BOOST_AUTO_TEST_CASE(database_01)
{
  saw::Database d("test.db");

  d.exec("drop table if exists toto;");
  d.exec("create table toto (a int, b int, c int);");
  d.exec("insert into toto values (?, ?, ?)", SAW_PLIST((1, 1)(2, 2)(3, 3)));

  saw::RowRange r1 = d.result("select * from toto where c < 4;");
  saw::RowRange r2 = d.result("select * from toto where c < ?;", SAW_PLIST((1, 4)));

  BOOST_CHECK(++r1.first == r1.second);
  BOOST_CHECK(++r2.first == r2.second);
}
