#include "BlockOfInt.h"
#ifndef NDEBUG
std::unordered_set<int *> BlockOfInt::alloc;
#endif

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(creation)
{
    BlockOfInt test_object(4);

    BOOST_CHECK(test_object.size() == 4);
}

BOOST_AUTO_TEST_CASE(indexing)
{
    BlockOfInt test_object(4);
    test_object[0] = 1;
    test_object[1] = 2;
    test_object[2] = -10;
    test_object[3] = 100;

    BOOST_CHECK_EQUAL(test_object[0], 1);
    BOOST_CHECK_EQUAL(test_object[1], 2);
    BOOST_CHECK_EQUAL(test_object[2], -10);
    BOOST_CHECK_EQUAL(test_object[3], 100);
}

BOOST_AUTO_TEST_CASE(show_copy_problem) {
    {
    BlockOfInt test_object(3);
    BlockOfInt test_obtect2(test_object);
    }
    BOOST_CHECK(true);
}

