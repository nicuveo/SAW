[![Build Status](https://travis-ci.org/nicuveo/SAW.svg?branch=master)](https://travis-ci.org/nicuveo/SAW)
[![Coverage Status](https://coveralls.io/repos/nicuveo/SAW/badge.svg?branch=master&service=github)](https://coveralls.io/github/nicuveo/SAW?branch=master)

*SAW* (Sqlite3 API Wrapper)
===========================

> My heart is full of `saw::Row`.  
-- *Sad anonymous*

> A **Z** that stands for `saw::Row`!  
-- *Illiterate anonymous*


Yet another wrapper
-------------------

Faced with the need to write some code using sqlite3's C API, I've procrastinated the real task at hand by writing a standalone library wrapping it.

The goal of this small library is *NOT* to hide sqlite3's API; if it aimed to do so, it would be far more complicated than it already is. Its goal is simply to facilitate some common sqlite3 tasks, such as managing database connections and statements. All wrapped structures such as `Database` and `Statement` provide access to the raw data that lies beneath.

See below a short example of the clarity it brings to the code. For a more detailed documentation; please see the [wiki](https://github.com/nicuveo/SAW/wiki).


Installation
------------

*SAW* requires [*NPL*](https://github.com/nicuveo/NPL) to build.

``` bash
./configure
make
make doc     # generates doxygen documentation
make check   # runs tests and generates code coverage report using lcov and cppcheck
make install # installs to /usr/local
```

Internal plumbing
-----------------

This library uses C++11 features and lots of `boost` code. For instance, database and statement handlers are shared using reference counting shared pointers. Values are implemented using `boost::variant` and iterators use `boost::iterator_facade`.

The code has been mostly tested and is currently at >90% of code coverage as reported by *lcov*.

If, somehow, you end up using it, please let me know what you think!


C API / _SAW_ comparison
------------------------

### C API

``` c++
int run(const char* name, int score_min)
{
  sqlite3* db = 0;
  sqlite3_stmt* stmt = 0;

  int res = sqlite3_open("test.db", &db);

  if (res != SQLITE_OK)
    return res;

  res = sqlite3_prepare_v2(db, "create table if not exists results (name text, score int)", &stmt, 0);

  if (res != SQLITE_OK)
    return res;

  res = sqlite3_step(stmt);

  if (res != SQLITE_DONE)
    return 1;

  sqlite3_finalize(stmt);

  res = sqlite3_prepare_v2(db, "select score from results where name = ? and score >= ?", &stmt, 0);

  if (res != SQLITE_OK)
    return res;

  res = sqlite3_bind_text(stmt, 1, name, 0, SQLITE_TRANSIENT);

  if (res != SQLITE_OK)
    return res;

  res = sqlite3_bind_int(stmt, 2, score_min);

  if (res != SQLITE_OK)
    return res;

  res = sqlite3_step(stmt);

  while (res != SQLITE_DONE)
  {
    if (res != SQLITE_ROW)
      return res;

    std::cout << "score: " << sqlite3_column_int(stmt, 0) << std::endl;
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);

  return 0;
}
```


### *SAW*

``` c++
void run(const char* name, int score_min)
{
  try
  {
    saw::Database db("test.db");
    saw::Statement stmt;

    db.exec("create table if not exists results (name text, score int)");

    stmt = db.make("select score from results where name = ? and score >= ?");
    stmt[1] = name;
    stmt[2] = score_min;

    for (const saw::Row& row : stmt.result())
      std::cout << "score: " << row[0].as_integer() << std::endl;
  }
  catch (const saw::Exception& e)
  {
    std::cerr << "error: " << e.what() << std::endl;
  }
}
```
