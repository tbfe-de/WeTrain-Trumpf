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

BOOST_AUTO_TEST_CASE(move_ctor_is_noexcept) {
    BlockOf<int> test_object(2);
    BOOST_CHECK_EQUAL(noexcept(std::move(test_object)), true);
}

BOOST_AUTO_TEST_CASE(block_of_forwards_noexcept) {
    BOOST_CHECK_EQUAL(noexcept(int()), true);
    typedef BlockOf<int> B0;
    BOOST_CHECK_EQUAL(noexcept(B0(2)), true);
}

struct CtorMayThrow {
    CtorMayThrow() {}
};

BOOST_AUTO_TEST_CASE(block_of_forwards_ctor_may_throw) {
    BOOST_CHECK_EQUAL(noexcept(CtorMayThrow()), false);
    BOOST_CHECK_EQUAL(noexcept(new(nullptr) CtorMayThrow()), false);
    typedef BlockOf<CtorMayThrow> Blk;
    BOOST_CHECK_EQUAL(noexcept(Blk(2)), false);
    auto li = { CtorMayThrow(), CtorMayThrow() };
    BOOST_CHECK_EQUAL(noexcept(Blk(li)), true);
}

struct CtorNoThrow {
    CtorNoThrow() noexcept {}
};

BOOST_AUTO_TEST_CASE(block_of_forwards_ctor_no_throw) {
    BOOST_CHECK_EQUAL(noexcept(CtorNoThrow()), true);
    typedef BlockOf<CtorNoThrow> Blk;
    BOOST_CHECK_EQUAL(noexcept(Blk(2)), true);
    auto li = { CtorNoThrow(), CtorNoThrow() };
    BOOST_CHECK_EQUAL(noexcept(Blk(li)), true);
}

struct CopyMayThrow {
    CopyMayThrow() noexcept {}
    CopyMayThrow(const CopyMayThrow&) {}
};

BOOST_AUTO_TEST_CASE(block_of_forwards_copy_may_throw) {
    BOOST_CHECK_EQUAL(noexcept(CopyMayThrow()), true);
    BOOST_CHECK_EQUAL(noexcept(CopyMayThrow(std::declval<CopyMayThrow>())), false);
    typedef BlockOf<CopyMayThrow> Blk;
    BOOST_CHECK_EQUAL(noexcept(Blk(2)), true);
    auto li = { CopyMayThrow(), CopyMayThrow() };
    BOOST_CHECK_EQUAL(noexcept(Blk(li)), false);
}

struct DtorMayThrow {
    DtorMayThrow() noexcept {}
    ~DtorMayThrow() noexcept(false) {}
};

BOOST_AUTO_TEST_CASE(block_of_forwards_dtor_may_throw) {
    BOOST_CHECK_EQUAL(noexcept(new(nullptr) DtorMayThrow()), true);
    BOOST_CHECK_EQUAL(noexcept(DtorMayThrow()), false);
    typedef BlockOf<DtorMayThrow> Blk;
    BOOST_CHECK_EQUAL(noexcept(new(nullptr) Blk(2)), true);
    BOOST_CHECK_EQUAL(noexcept(Blk(2)), false);
    auto li = { DtorMayThrow(), DtorMayThrow() };
    BOOST_CHECK_EQUAL(noexcept(new(nullptr) Blk(li)), true);
    BOOST_CHECK_EQUAL(noexcept(Blk(li)), false);
}
