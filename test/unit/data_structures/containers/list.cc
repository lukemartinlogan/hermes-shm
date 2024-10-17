/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Distributed under BSD 3-Clause license.                                   *
 * Copyright by The HDF Group.                                               *
 * Copyright by the Illinois Institute of Technology.                        *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of Hermes. The full Hermes copyright notice, including  *
 * terms governing use, modification, and redistribution, is contained in    *
 * the COPYING file, which can be found at the top directory. If you do not  *
 * have access to the file, you may request a copy from help@hdfgroup.org.   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "basic_test.h"
#include "test_init.h"
#include "list.h"

// #include "hermes_shm/data_structures/containers/list.h"
#include "hermes_shm/data_structures/ipc/list.h"
#include "hermes_shm/data_structures/ipc/string.h"

template<typename T, typename ListT>
void ListTestRunner(ListTestSuite<T, ListT> &test) {
  test.EmplaceTest(15);
  test.ForwardIteratorTest();
  test.ConstForwardIteratorTest();
  test.CopyConstructorTest();
  test.CopyAssignmentTest();
  test.MoveConstructorTest();
  test.MoveAssignmentTest();
  test.EmplaceFrontTest();
  test.ModifyEntryCopyIntoTest();
  test.ModifyEntryMoveIntoTest();
  test.EraseTest();
}

template<typename T>
void HipcListTest() {
  Allocator *alloc = alloc_g;
  auto lp = hipc::make_uptr<hipc::list<T>>(alloc);
  ListTestSuite<T, hipc::list<T>> test(*lp, alloc);
  ListTestRunner(test);
}

//template<typename T>
//void HshmListTest() {
//  Allocator *alloc = alloc_g;
//  hshm::list<T> lp;
//  ListTestSuite<T, hipc::list<T>> test(lp, alloc);
//  ListTestRunner(test);
//}

/**
 * HIPC list tests
 * */

TEST_CASE("hipc::ListOfInt") {
  Allocator *alloc = alloc_g;
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
  HipcListTest<int>();
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
}

TEST_CASE("hipc::ListOfString") {
  Allocator *alloc = alloc_g;
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
  HipcListTest<hipc::string>();
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
}

TEST_CASE("hipc::ListOfStdString") {
  Allocator *alloc = alloc_g;
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
  HipcListTest<std::string>();
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
}

/**
 * HSHM list tests
 * */

//TEST_CASE("hshm::ListOfInt") {
//  Allocator *alloc = alloc_g;
//  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
//  HshmListTest<int>();
//  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
//}
//
//TEST_CASE("hshm::ListOfString") {
//  Allocator *alloc = alloc_g;
//  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
//  HshmListTest<hipc::string>();
//  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
//}
//
//TEST_CASE("hshm::ListOfStdString") {
//  Allocator *alloc = alloc_g;
//  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
//  HshmListTest<std::string>();
//  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
//}