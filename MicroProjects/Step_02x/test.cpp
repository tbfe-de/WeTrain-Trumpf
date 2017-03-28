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

void foo_ref(BlockOfInt &block) {
    BOOST_CHECK_EQUAL(block[0], 1);
    BOOST_CHECK_EQUAL(block[1], 2);
    BOOST_CHECK_EQUAL(block[2], -10);
    BOOST_CHECK_EQUAL(block[3], 100);
}

void foo_cref(const BlockOfInt &block) {
    BOOST_CHECK_EQUAL(block[0], 1);
    BOOST_CHECK_EQUAL(block[1], 2);
    BOOST_CHECK_EQUAL(block[2], -10);
    BOOST_CHECK_EQUAL(block[3], 100);
}

void foo_ptr(BlockOfInt *block_ptr) {
#if 1
    BOOST_CHECK_EQUAL((*block_ptr)[0], 1);
    BOOST_CHECK_EQUAL((*block_ptr)[1], 2);
    BOOST_CHECK_EQUAL((*block_ptr)[2], -10);
    BOOST_CHECK_EQUAL((*block_ptr)[3], 100);
#else
    BOOST_CHECK_EQUAL(block_ptr->operator[](0), 1);
    BOOST_CHECK_EQUAL(block_ptr->operator[](1), 2);
    BOOST_CHECK_EQUAL(block_ptr->operator[](2), -10);
    BOOST_CHECK_EQUAL(block_ptr->operator[](3), 100);
#endif
}

void foo_cptr(const BlockOfInt *block_ptr) {
#if 1
    BOOST_CHECK_EQUAL((*block_ptr)[0], 1);
    BOOST_CHECK_EQUAL((*block_ptr)[1], 2);
    BOOST_CHECK_EQUAL((*block_ptr)[2], -10);
    BOOST_CHECK_EQUAL((*block_ptr)[3], 100);
#else
    BOOST_CHECK_EQUAL(block_ptr->operator[](0), 1);
    BOOST_CHECK_EQUAL(block_ptr->operator[](1), 2);
    BOOST_CHECK_EQUAL(block_ptr->operator[](2), -10);
    BOOST_CHECK_EQUAL(block_ptr->operator[](3), 100);
#endif
}

BOOST_AUTO_TEST_CASE(ref_indexing)
{
    BlockOfInt test_object(4);
    test_object[0] = 1;
    test_object[1] = 2;
    test_object[2] = -10;
    test_object[3] = 100;

    foo_ref(test_object);
}

BOOST_AUTO_TEST_CASE(cref_indexing)
{
    BlockOfInt test_object(4);
    test_object[0] = 1;
    test_object[1] = 2;
    test_object[2] = -10;
    test_object[3] = 100;

    foo_cref(test_object);
}

BOOST_AUTO_TEST_CASE(ptr_indexing)
{
    BlockOfInt test_object(4);
    test_object[0] = 1;
    test_object[1] = 2;
    test_object[2] = -10;
    test_object[3] = 100;

    foo_ptr(&test_object);
}

BOOST_AUTO_TEST_CASE(cptr_indexing)
{
    BlockOfInt test_object(4);
    test_object[0] = 1;
    test_object[1] = 2;
    test_object[2] = -10;
    test_object[3] = 100;

    foo_cptr(&test_object);
}
