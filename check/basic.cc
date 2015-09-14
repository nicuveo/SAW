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
#include <boost/test/unit_test.hpp>
#include "nauths/saw/saw.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

BOOST_AUTO_TEST_SUITE(basic)

BOOST_AUTO_TEST_CASE(drop_create_insert_select)
{
  saw::Database db("test.db");

  db.exec("drop table if exists toto;");
  db.exec("create table toto (key int, value int);");
  db.exec("insert into toto values (42, 69);");

  saw::Rows rs = db.exec("select * from toto;");

  BOOST_REQUIRE_EQUAL(1, rs.size());
  BOOST_REQUIRE_EQUAL(42, rs[0][0].as_integer());
  BOOST_REQUIRE_EQUAL(69, rs[0][1].as_integer());
}

BOOST_AUTO_TEST_SUITE_END()
