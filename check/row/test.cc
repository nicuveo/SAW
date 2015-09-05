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

#define BOOST_TEST_MODULE row
#include <boost/test/included/unit_test.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

BOOST_AUTO_TEST_CASE(row_00)
{
  saw::Database d("test.db");

  d.exec("drop table if exists toto;");
  d.exec("create table toto (a int, b float, c text, d blob);");
  BOOST_CHECK_NO_THROW(d.exec("insert into toto values (?, ?, ?, ?);", SAW_PLIST(
                                (1, saw::Null())
                                (2, 42.)
                                (3, "foo")
                                (4, saw::Blob("bar")))));

  saw::Rows rs = d.exec("select * from toto;");

  BOOST_REQUIRE_EQUAL(1, rs.size());
  BOOST_CHECK(rs[0][0].null());
  BOOST_CHECK_EQUAL(42.,              rs[0][1].as_float());
  BOOST_CHECK_EQUAL("foo",            rs[0][2].as_text() );
  BOOST_CHECK_EQUAL(saw::Blob("bar"), rs[0][3].as_blob() );
}
