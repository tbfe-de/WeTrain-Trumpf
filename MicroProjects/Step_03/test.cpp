#include "BlockOfInt.h"
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

void foo(const BlockOfInt &block) {
    BOOST_CHECK_EQUAL(block[0], 1);
    BOOST_CHECK_EQUAL(block[1], 2);
    BOOST_CHECK_EQUAL(block[2], -10);
    BOOST_CHECK_EQUAL(block[3], 100);
}

BOOST_AUTO_TEST_CASE(const_indexing)
{
    BlockOfInt test_object(4);
    test_object[0] = 1;
    test_object[1] = 2;
    test_object[2] = -10;
    test_object[3] = 100;

    foo(test_object);
}

BOOST_AUTO_TEST_CASE(cheap_swapping) {
    BlockOfInt test_object(4);
    BOOST_CHECK_EQUAL(test_object.size(), 4);
    test_object[0] = 1;
    test_object[1] = 2;
    test_object[2] = -10;
    test_object[3] = 100;
    BOOST_CHECK_EQUAL(test_object[0], 1);
    BOOST_CHECK_EQUAL(test_object[1], 2);
    BOOST_CHECK_EQUAL(test_object[2], -10);
    BOOST_CHECK_EQUAL(test_object[3], 100);

    BlockOfInt test_object2(2);
    test_object2[0] = 10;
    test_object2[1] = 20;
    BOOST_CHECK_EQUAL(test_object2.size(), 2);
    BOOST_CHECK_EQUAL(test_object2[0], 10);
    BOOST_CHECK_EQUAL(test_object2[1], 20);

// --------------------------------
    test_object.swap(test_object2);
// --------------------------------

    BOOST_CHECK_EQUAL(test_object.size(), 2);
    BOOST_CHECK_EQUAL(test_object[0], 10);
    BOOST_CHECK_EQUAL(test_object[1], 20);
    BOOST_CHECK_EQUAL(test_object2.size(), 4);
    BOOST_CHECK_EQUAL(test_object2[0], 1);
    BOOST_CHECK_EQUAL(test_object2[1], 2);
    BOOST_CHECK_EQUAL(test_object2[2], -10);
    BOOST_CHECK_EQUAL(test_object2[3], 100);
}
