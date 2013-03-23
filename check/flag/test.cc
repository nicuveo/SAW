//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <cstdlib>
#include <iostream>
#include <saw/saw.hh>

#define BOOST_TEST_MODULE flag
#include <boost/test/included/unit_test.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

BOOST_AUTO_TEST_CASE(flag_00)
{
  saw::detail::Flag f;
  saw::detail::Watcher w1(f);
  saw::detail::Watcher w2;
  BOOST_REQUIRE(not  f.raised()  );
  BOOST_REQUIRE(not w1.valid()   );
  BOOST_REQUIRE(    w1.obsolete());
  BOOST_REQUIRE(not w2.valid()   );
  BOOST_REQUIRE(    w2.obsolete());

  f.raise();
  BOOST_REQUIRE(     f.raised()  );
  BOOST_REQUIRE(not w1.valid()   );
  BOOST_REQUIRE(    w1.obsolete());
  BOOST_REQUIRE(not w2.valid()   );
  BOOST_REQUIRE(    w2.obsolete());

  w1 = saw::detail::Watcher(f);
  w2 = saw::detail::Watcher(f);
  BOOST_REQUIRE(     f.raised()  );
  BOOST_REQUIRE(    w1.valid()   );
  BOOST_REQUIRE(not w1.obsolete());
  BOOST_REQUIRE(    w2.valid()   );
  BOOST_REQUIRE(not w2.obsolete());

  f.raise();
  BOOST_REQUIRE(     f.raised()  );
  BOOST_REQUIRE(not w1.valid()   );
  BOOST_REQUIRE(    w1.obsolete());
  BOOST_REQUIRE(not w2.valid()   );
  BOOST_REQUIRE(    w2.obsolete());
}
