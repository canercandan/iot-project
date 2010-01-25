#ifndef TEST_RULES_H_
#define TEST_RULES_H_

#define BOOST_SPIRIT_THREADSAFE /* Always before including spirit headers */
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_dynamic.hpp>

using namespace BOOST_SPIRIT_CLASSIC_NS;

struct	TestRules
{
  BasicRules br;
  TestRules(void)
  {
    TEST = str_p("Jan");
  }

  stored_rule<>	TEST;
};

#endif
