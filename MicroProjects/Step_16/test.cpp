#define FULLY_GENERIC_FOR_EACH
#include "BlockOf.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>

#include <string>

BOOST_AUTO_TEST_CASE(creation)
{
    BlockOf<int> test_object;
    BOOST_CHECK(test_object.empty());

    BlockOf<int> test_object2(42);
    BOOST_CHECK(!test_object2.empty());
}

BOOST_AUTO_TEST_CASE(accessing) {
    BlockOf<int> test_object(42);
    BOOST_CHECK_EQUAL(test_object.get(), 42);
    test_object = 10;
    BOOST_CHECK_EQUAL(test_object.get(), 10);
    ++test_object.get();
    BOOST_CHECK_EQUAL(test_object.get(), 11);
}

void foo(const BlockOf<int> &block) {
    BOOST_CHECK_EQUAL(block.get(), -10);
}

BOOST_AUTO_TEST_CASE(const_indexing)
{
    BlockOf<int> test_object(-10);
    BOOST_CHECK(!test_object.empty());
    foo(test_object);
}

BOOST_AUTO_TEST_CASE(cheap_swapping) {
    BlockOf<int> test_object(42);
    BOOST_CHECK(!test_object.empty());
    BlockOf<int> test_object2;
    BOOST_CHECK(test_object2.empty());

// --------------------------------
    test_object.swap(test_object2);
// --------------------------------

    BOOST_CHECK(test_object.empty());
    BOOST_CHECK(!test_object2.empty());
    BOOST_CHECK_EQUAL(test_object2.get(), 42);
}

BOOST_AUTO_TEST_CASE(move_constructor) {
    BlockOf<int> test_object(42);
    BOOST_CHECK(!test_object.empty());
    BOOST_CHECK_EQUAL(test_object.get(), 42);

// -------------------------------------------------
    BlockOf<int> test_object2(std::move(test_object));
// -------------------------------------------------

    BOOST_CHECK(!test_object2.empty());
    BOOST_CHECK_EQUAL(test_object2.get(), 42);
}

BOOST_AUTO_TEST_CASE(move_assignment) {
    BlockOf<int> test_object(100);
    BOOST_CHECK(!test_object.empty());
    BOOST_CHECK_EQUAL(test_object.get(), 100);

    BlockOf<int> test_object2(-10);
    BOOST_CHECK(!test_object2.empty());
    BOOST_CHECK_EQUAL(test_object2.get(), -10);

// ------------------------------------------
    test_object2 = std::move(test_object);
// ------------------------------------------

    BOOST_CHECK(!test_object2.empty());
    BOOST_CHECK_EQUAL(test_object2.get(), 100);
}

BOOST_AUTO_TEST_CASE(some_more_types) {
    BlockOf<bool> test_object(false);
    BOOST_CHECK(!test_object.empty());
    BOOST_CHECK_EQUAL(test_object.get(), false);

    BlockOf<double> test_object2(1.1);
    BOOST_CHECK(!test_object2.empty());
    BOOST_CHECK_CLOSE(test_object2.get(), 1.1, 0.001);

    BlockOf<std::string> test_object3;
    BOOST_CHECK(test_object3.empty());
    test_object3 = std::string("hi!");
    BOOST_CHECK_EQUAL(test_object3.get(), std::string("hi!"));
}

template<typename T>
void bar(T&& arg) {
    auto local_object(std::forward<T>(arg));
    BOOST_CHECK(!local_object.empty());
    BOOST_CHECK_EQUAL(local_object.get(), std::string("hello, world"));
    local_object = std::string("whatever");
    BOOST_CHECK_EQUAL(local_object.get(), std::string("whatever"));
}

BOOST_AUTO_TEST_CASE(perfect_forwarding) {
    BlockOf<std::string> test_object("hello, world");
    BOOST_CHECK(!test_object.empty());
    BOOST_CHECK_EQUAL(test_object.get(), std::string("hello, world"));
    bar(std::move(test_object));
}

