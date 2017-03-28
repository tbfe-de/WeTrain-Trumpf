#include "BlockOf.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>

#include <string>

BOOST_AUTO_TEST_CASE(creation) {
    BlockOf<int> test_object(4);

    BOOST_CHECK(test_object.size() == 4);
}

BOOST_AUTO_TEST_CASE(indexing) {
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

BOOST_AUTO_TEST_CASE(const_indexing) {
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

// ---------------------------------------------------
    BlockOf<int> test_object2(std::move(test_object));
// ---------------------------------------------------

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

// ---------------------------------------
    test_object2 = std::move(test_object);
// ---------------------------------------

    BOOST_CHECK_EQUAL(test_object2.size(), 4);
    BOOST_CHECK_EQUAL(test_object2[0], 1);
    BOOST_CHECK_EQUAL(test_object2[1], 2);
    BOOST_CHECK_EQUAL(test_object2[2], -10);
    BOOST_CHECK_EQUAL(test_object2[3], 100);
}

BOOST_AUTO_TEST_CASE(from_list_construction) {

// ------------------------------------------
    BlockOf<int> test_object({7, 12, -1, 5});
// ------------------------------------------

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

struct NoDefaultButCopyCtor {
    static int instance_count;
    int v;
    NoDefaultButCopyCtor() = delete;
    NoDefaultButCopyCtor(int v_) : v(v_) { ++instance_count; }
    NoDefaultButCopyCtor(const NoDefaultButCopyCtor& init) : v(init.v) { ++instance_count; }
    NoDefaultButCopyCtor(NoDefaultButCopyCtor&&) = delete;
    NoDefaultButCopyCtor& operator=(const NoDefaultButCopyCtor& rhs) { v = rhs.v; ++instance_count; }
    NoDefaultButCopyCtor& operator=(NoDefaultButCopyCtor&) = delete;
    ~NoDefaultButCopyCtor() { --instance_count; }
};
int NoDefaultButCopyCtor::instance_count = 0;

BOOST_AUTO_TEST_CASE(no_default_ctor_class) {
    BOOST_CHECK_EQUAL(NoDefaultButCopyCtor::instance_count, 0);
    {
//     ------------------------------------------------------
//      BlockOf<NoDefaultButCopyCtor> test_object(3); // should not compile
        BlockOf<NoDefaultButCopyCtor> test_object({3, 2, 1});
//     ------------------------------------------------------
        BOOST_CHECK_EQUAL(test_object[0].v, 3);
        BOOST_CHECK_EQUAL(test_object[1].v, 2);
        BOOST_CHECK_EQUAL(test_object[2].v, 1);
        BOOST_CHECK_EQUAL(NoDefaultButCopyCtor::instance_count, 3);
    }
    BOOST_CHECK_EQUAL(NoDefaultButCopyCtor::instance_count, 0);
}

