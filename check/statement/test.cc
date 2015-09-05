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

#define BOOST_TEST_MODULE statement
#include <boost/test/included/unit_test.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

BOOST_AUTO_TEST_CASE(statement_00)
{
  saw::Database d("test.db");
  d.exec("drop table if exists toto;");
  d.exec("create table toto (a int, b int, c int);");

  const char* query = "select 42 from toto;";

  saw::Statement s1 = d.make(query);
  saw::Statement s2(d, query);
  saw::Statement s3;

  BOOST_REQUIRE_EQUAL(d.raw_data(), s1.database().raw_data());
  BOOST_REQUIRE_EQUAL(d.raw_data(), s2.database().raw_data());
  BOOST_REQUIRE_EQUAL((sqlite3*) 0, s3.database().raw_data());
}

BOOST_AUTO_TEST_CASE(statement_01)
{
  saw::Database d("test.db");
  d.exec("drop table if exists toto;");
  d.exec("create table toto (a int, b int, c int);");

  const char* query = "select 42 from toto;";

  saw::Statement s1 = d.make(query);
  saw::Statement s2(d, query);
  saw::Statement s3;

  BOOST_REQUIRE(    s1.ready());
  BOOST_REQUIRE(not s1.empty());
  BOOST_REQUIRE(    s2.ready());
  BOOST_REQUIRE(not s2.empty());
  BOOST_REQUIRE(not s3.ready());
  BOOST_REQUIRE(    s3.empty());
}

BOOST_AUTO_TEST_CASE(statement_02)
{
  saw::Database d("test.db");

  d.exec("drop table if exists toto;");
  d.exec("create table toto (a int, b int, c int);");
  d.exec("insert into toto values (42, 42, 42);");

  saw::Statement s1 = d.make("select ?      from toto;");
  saw::Statement s2 = d.make("select ?42    from toto;");
  saw::Statement s3 = d.make("select :name1 from toto;");
  saw::Statement s4 = d.make("select @name2 from toto;");
  saw::Statement s5 = d.make("select $name3 from toto;");

  s1[1] = 101;
  s3[":name1"] = 102;
  s2[saw::ParameterKey(42)] = 103;
  s4[saw::ParameterKey("@name2")] = 104;
  s5[saw::ParameterKey("$name3")] = 105;

  BOOST_REQUIRE_EQUAL(101, s1.exec()[0][0].as_integer());
  BOOST_REQUIRE_EQUAL(102, s3.exec()[0][0].as_integer());
  BOOST_REQUIRE_EQUAL(103, s2.exec()[0][0].as_integer());
  BOOST_REQUIRE_EQUAL(104, s4.exec()[0][0].as_integer());
  BOOST_REQUIRE_EQUAL(105, s5.exec()[0][0].as_integer());
}

BOOST_AUTO_TEST_CASE(statement_03)
{
  saw::Database d("test.db");

  d.exec("drop table if exists toto;");
  d.exec("create table toto (a int, b int, c int);");

  saw::Statement s = d.make("insert into toto values (?, ?, ?);");

  (s << saw::Parameter(1, 11) << saw::Parameter(2, 12) << saw::Parameter(3, 13)).exec();
  (s << SAW_PLIST((1, 21)(2, 22)(3, 23))).exec();
  s.exec(SAW_PLIST((1, 31)(2, 32)(3, 33)));

  const saw::Rows& r = d.exec("select * from toto;");

  BOOST_REQUIRE_EQUAL(3, r.size());
  BOOST_REQUIRE_EQUAL(11, r[0][0].as_integer());
  BOOST_REQUIRE_EQUAL(12, r[0][1].as_integer());
  BOOST_REQUIRE_EQUAL(13, r[0][2].as_integer());
  BOOST_REQUIRE_EQUAL(21, r[1][0].as_integer());
  BOOST_REQUIRE_EQUAL(22, r[1][1].as_integer());
  BOOST_REQUIRE_EQUAL(23, r[1][2].as_integer());
  BOOST_REQUIRE_EQUAL(31, r[2][0].as_integer());
  BOOST_REQUIRE_EQUAL(32, r[2][1].as_integer());
  BOOST_REQUIRE_EQUAL(33, r[2][2].as_integer());
}

namespace
{

  void test_callback(saw::Row& r)
  {
    saw::Row const& cr = r;
    int ri = r.index();

    std::cout << ri << ": NC {";
    for (const saw::Value& v : cr.values())
      std::cout << " " << v.as_integer();
    std::cout << " }" << std::endl
              << ri << ":  C {";
    for (const saw::Value& v : r.values())
      std::cout << " " << v.as_integer();
    std::cout << " }" << std::endl;

    BOOST_REQUIRE_EQUAL(3, cr.columns_number());

    for (int i = 0; i < 3; ++i)
    {
      BOOST_REQUIRE(cr.cached(i));
      BOOST_REQUIRE_EQUAL(ri * 10 + i + 1, cr[i].as_integer());
    }
  }

}

BOOST_AUTO_TEST_CASE(statement_04)
{
  saw::Database d("test.db");

  d.exec("drop table if exists toto;");
  d.exec("create table toto (a int, b int, c int);");
  d.exec("insert into toto values \
( 1,  2,  3), \
(11, 12, 13), \
(21, 22, 23), \
(31, 32, 33);");

  d.exec("select * from toto;", &test_callback);
}

BOOST_AUTO_TEST_CASE(statement_05)
{
  saw::Database d("test.db");

  d.exec("drop table if exists toto;");
  d.exec("create table toto (a int, b int, c int);");
  d.exec("insert into toto values \
( 1,  2,  3), \
(11, 12, 13), \
(21, 22, 23), \
(31, 32, 33);");

  d.exec("select * from toto where c < ?;", &test_callback, SAW_PLIST((1, 50)));
}

BOOST_AUTO_TEST_CASE(statement_06)
{
  saw::Database d("test.db");

  d.exec("drop table if exists toto;");
  d.exec("create table toto (a int, b float, c text, d blob);");
  BOOST_CHECK_NO_THROW(d.exec("insert into toto values (?, ?, ?, ?);", SAW_PLIST(
                                (1, saw::Null())
                                (2, 42.)
                                (3, "foo")
                                (4, saw::Blob("bar")))));
}

BOOST_AUTO_TEST_CASE(statement_07)
{
  saw::Database d("test.db");
  saw::Statement s = d.make("select * from toto;");

  d.exec("drop table if exists toto;");
  d.exec("create table toto (a int, b int, c int);");
  d.exec("insert into toto values \
( 1,  2,  3), \
(11, 12, 13), \
(21, 22, 23), \
(31, 32, 33);");

  saw::RowRange r = s.result();
  BOOST_CHECK_EQUAL(4, std::distance(r.first, r.second));
}

BOOST_AUTO_TEST_CASE(statement_08)
{
  saw::Database d("test.db");
  saw::Statement s = d.make("select * from toto;");

  d.exec("drop table if exists toto;");
  d.exec("create table toto (a int, b int, c int);");
  d.exec("insert into toto values \
( 1,  2,  3), \
(11, 12, 13), \
(21, 22, 23), \
(31, 32, 33);");

  BOOST_CHECK_NO_THROW(s.reset());

  int index = 0;
  for (saw::RowRange r = s.result(); r.first != r.second; ++r.first, ++index)
  {
    BOOST_CHECK_EQUAL(index, s.current_row_index());
    test_callback(*r.first);
  }
  BOOST_CHECK_EQUAL(4, index);

  BOOST_CHECK_NO_THROW(s.reset());

  saw::Statement::ColumnNames cn = s.columns_names();
  BOOST_CHECK_EQUAL(cn[0], s.column_name(0)); BOOST_CHECK_EQUAL(cn[0], "a");
  BOOST_CHECK_EQUAL(cn[1], s.column_name(1)); BOOST_CHECK_EQUAL(cn[1], "b");
  BOOST_CHECK_EQUAL(cn[2], s.column_name(2)); BOOST_CHECK_EQUAL(cn[2], "c");
}
