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

#define BOOST_TEST_MODULE errors
#include <boost/test/included/unit_test.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

BOOST_AUTO_TEST_CASE(errors_00)
{
  saw::Database d;
  saw::Statement s;

  BOOST_CHECK_THROW(d.make("select * from toto"), saw::LogicError);
  BOOST_CHECK_THROW(saw::Statement(d, "select * from toto"), saw::LogicError);
  BOOST_CHECK_THROW(s.bind("toto", 2), saw::LogicError);
  BOOST_CHECK_THROW(s.result(), saw::LogicError);
  BOOST_CHECK_THROW(s.exec(), saw::LogicError);
  BOOST_CHECK_THROW(s.step(), saw::LogicError);
  BOOST_CHECK_THROW(s.reset(), saw::LogicError);
}

BOOST_AUTO_TEST_CASE(errors_01)
{
  saw::Database d("test.db");

  d.exec("create table if not exists toto (a int);");
  d.exec("insert into toto values (42), (51);");

  saw::RowRange iterators = d.make("select * from toto;").result();

  saw::Row r1 = *iterators.first;
  saw::Row r2 = *++iterators.first;

  BOOST_CHECK_THROW   (r1[0].as_integer(), saw::LogicError);
  BOOST_CHECK_NO_THROW(r2[0].as_integer());

  ++iterators.first;

  BOOST_CHECK_THROW(*iterators.first, saw::LogicError);
  BOOST_CHECK_THROW(r1[0].as_integer(), saw::LogicError);
  BOOST_CHECK_NO_THROW(r2[0].as_integer()); // cached

  BOOST_CHECK_THROW(++iterators.first, saw::LogicError);

  saw::Statement s = d.make("select * from toto;");
  iterators = s.result();

  BOOST_CHECK_THROW(s.result(), saw::LogicError);

  s.reset();

  BOOST_CHECK_THROW(++iterators.first, saw::LogicError);
}

BOOST_AUTO_TEST_CASE(errors_02)
{
  saw::RowIterator it;

  BOOST_CHECK_THROW(++it, saw::LogicError);
  BOOST_CHECK_THROW(*it, saw::LogicError);
}

BOOST_AUTO_TEST_CASE(errors_03)
{
  saw::Database d("test.db");

  d.exec("create table if not exists toto (a int);");
  d.exec("insert into toto values (42), (51);");

  saw::Statement s(d, "select * from toto;");
  saw::Row r = s.current_row();

  BOOST_CHECK_THROW(r[0], saw::OutOfRange);
}

BOOST_AUTO_TEST_CASE(errors_04)
{
  BOOST_CHECK_THROW(saw::Database("/doesnotexist/impossibru.db"), saw::RuntimeError);
}
