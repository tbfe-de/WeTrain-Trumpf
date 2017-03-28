#define FULLY_GENERIC_FOR_EACH
#include "BlockOf.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>

#include <string>

BOOST_AUTO_TEST_CASE(creation)
{
    BlockOf<int> test_object(4);

    BOOST_CHECK(test_object.size() == 4);
}

BOOST_AUTO_TEST_CASE(indexing)
{
    BlockOf<int> test_object(4);
    test_object[0] = 1;
    test_object[1] = 2;
    test_object[2] = -10;
    test_object[3] = 100;

    BOOST_CHECK_EQUAL(test_object[0], 1);
    BOOST_CHECK_EQUAL(test_object[1], 2);
    BOOST_CHECK_EQUAL(test_object[2], -10);
    BOOST_CHECK_EQUAL(test_object[3], 100);
}

void foo(const BlockOf<int> &block) {
    BOOST_CHECK_EQUAL(block[0], 1);
    BOOST_CHECK_EQUAL(block[1], 2);
    BOOST_CHECK_EQUAL(block[2], -10);
    BOOST_CHECK_EQUAL(block[3], 100);
}

BOOST_AUTO_TEST_CASE(const_indexing)
{
    BlockOf<int> test_object(4);
    test_object[0] = 1;
    test_object[1] = 2;
    test_object[2] = -10;
    test_object[3] = 100;

    foo(test_object);
}

BOOST_AUTO_TEST_CASE(cheap_swapping) {
    BlockOf<int> test_object(4);
    BOOST_CHECK_EQUAL(test_object.size(), 4);
    test_object[0] = 1;
    test_object[1] = 2;
    test_object[2] = -10;
    test_object[3] = 100;
    BOOST_CHECK_EQUAL(test_object[0], 1);
    BOOST_CHECK_EQUAL(test_object[1], 2);
    BOOST_CHECK_EQUAL(test_object[2], -10);
    BOOST_CHECK_EQUAL(test_object[3], 100);

    BlockOf<int> test_object2(2);
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

BOOST_AUTO_TEST_CASE(move_constructor) {
    BlockOf<int> test_object(4);
    BOOST_CHECK_EQUAL(test_object.size(), 4);
    test_object[0] = 1;
    test_object[1] = 2;
    test_object[2] = -10;
    test_object[3] = 100;
    BOOST_CHECK_EQUAL(test_object[0], 1);
    BOOST_CHECK_EQUAL(test_object[1], 2);
    BOOST_CHECK_EQUAL(test_object[2], -10);
    BOOST_CHECK_EQUAL(test_object[3], 100);

// -------------------------------------------------
//  BlockOf<int> test_object2(test_object); // <-- should not compile !!
    BlockOf<int> test_object2(std::move(test_object));
// -------------------------------------------------

    BOOST_CHECK_EQUAL(test_object2[1], 2);
    BOOST_CHECK_EQUAL(test_object2[2], -10);
    BOOST_CHECK_EQUAL(test_object2[3], 100);
}

BOOST_AUTO_TEST_CASE(move_assignment) {
    BlockOf<int> test_object(4);
    BOOST_CHECK_EQUAL(test_object.size(), 4);
    test_object[0] = 1;
    test_object[1] = 2;
    test_object[2] = -10;
    test_object[3] = 100;
    BOOST_CHECK_EQUAL(test_object[0], 1);
    BOOST_CHECK_EQUAL(test_object[1], 2);
    BOOST_CHECK_EQUAL(test_object[2], -10);
    BOOST_CHECK_EQUAL(test_object[3], 100);

    BlockOf<int> test_object2(2);
    BOOST_CHECK_EQUAL(test_object2.size(), 2);

// ------------------------------------------
//  test_object2 = test_object); // <-- should not compile !!
    test_object2 = std::move(test_object);
// ------------------------------------------

    BOOST_CHECK_EQUAL(test_object2.size(), 4);
    BOOST_CHECK_EQUAL(test_object2[0], 1);
    BOOST_CHECK_EQUAL(test_object2[1], 2);
    BOOST_CHECK_EQUAL(test_object2[2], -10);
    BOOST_CHECK_EQUAL(test_object2[3], 100);
}

BOOST_AUTO_TEST_CASE(from_list_construction) {

// ----------------------------------------
    BlockOf<int> test_object({7, 12, -1, 5});
// ----------------------------------------

    BOOST_CHECK_EQUAL(test_object.size(), 4);
    BOOST_CHECK_EQUAL(test_object[0], 7);
    BOOST_CHECK_EQUAL(test_object[1], 12);
    BOOST_CHECK_EQUAL(test_object[2], -1);
    BOOST_CHECK_EQUAL(test_object[3], 5);
}

BOOST_AUTO_TEST_CASE(zero_initialisation) {
    BlockOf<int> test_object(4);
    BOOST_CHECK_EQUAL(test_object.size(), 4);
    BOOST_CHECK_EQUAL(test_object[0], 0);
    BOOST_CHECK_EQUAL(test_object[1], 0);
    BOOST_CHECK_EQUAL(test_object[2], 0);
    BOOST_CHECK_EQUAL(test_object[3], 0);
}

BOOST_AUTO_TEST_CASE(some_more_types) {
    BlockOf<bool> test_object(2);
    BOOST_CHECK_EQUAL(test_object.size(), 2);
    BOOST_CHECK_EQUAL(test_object[0], false);
    BOOST_CHECK_EQUAL(test_object[1], false);
    test_object[1] = !test_object[0];
    BOOST_CHECK_EQUAL(test_object[1], true);

    BlockOf<double> test_object2({1.1, 2.2, 3.3});
    BOOST_CHECK_EQUAL(test_object2.size(), 3);
    BOOST_CHECK_CLOSE(test_object2[0], 1.1, 0.001);
    BOOST_CHECK_CLOSE(test_object2[1], 2.2, 0.001);
    BOOST_CHECK_CLOSE(test_object2[2], 3.3, 0.001);

    BlockOf<std::string> test_object3(3);
    BOOST_CHECK_EQUAL(test_object3.size(), 3);
    BOOST_CHECK(test_object3[0].empty());
    BOOST_CHECK(test_object3[1].empty());
    BOOST_CHECK(test_object3[2].empty());
    test_object3[2] = "hi!";
    BOOST_CHECK_EQUAL(test_object3[2], std::string("hi!"));
}

template<typename T>
void bar(T&& arg) {
    auto local_object(std::forward<T>(arg));
    BOOST_CHECK_EQUAL(local_object.size(), 2);
    BOOST_CHECK_EQUAL(local_object[0], true);
    BOOST_CHECK_EQUAL(local_object[1], false);
    local_object[1] = local_object[0];
    BOOST_CHECK_EQUAL(local_object[1], true);
}

BOOST_AUTO_TEST_CASE(perfect_forwarding) {
    BlockOf<bool> test_object({true, false});
    BOOST_CHECK_EQUAL(test_object.size(), 2);
    BOOST_CHECK_EQUAL(test_object[0], true);
    BOOST_CHECK_EQUAL(test_object[1], false);
#ifdef MAKING_COPY_IS_IMPLEMENTED
    bar(test_object);
    BOOST_CHECK_EQUAL(test_object.size(), 2);
    BOOST_CHECK_EQUAL(test_object[0], true);
    BOOST_CHECK_EQUAL(test_object[1], false);
#endif
    bar(std::move(test_object));
    BOOST_CHECK_EQUAL(test_object.size(), 0);
}

#include <algorithm>
#include <iostream>
#include <boost/lambda/lambda.hpp>

BOOST_AUTO_TEST_CASE(for_each_as_member) {
    BlockOf<int> test_object({1, 2, 3});
    BOOST_CHECK_EQUAL(test_object.size(), 3);

    int sum = 0;
    using boost::ref;
//  --------------------------------------------------
//  test_object.for_each([&sum](int e) { sum += e; });
    test_object.for_each(sum += boost::lambda::_1);
//  --------------------------------------------------
    BOOST_CHECK_EQUAL(sum, 6);

    using boost::lambda::_1;
    using boost::lambda::_2;
    std::sort(test_object.begin(), test_object.end(), _2 < _1);
    std::ostringstream os;
    test_object.for_each(os << _1 << ' ');

    BOOST_CHECK_EQUAL(os.str(), "3 2 1 ");

}

