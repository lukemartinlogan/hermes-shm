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
#include "queue.h"
#include "test_init.h"

/**
 * TEST DYNAMIC QUEUE
 * */

TEST_CASE("TestDynamicQueueInt") {
  auto *alloc = HSHM_DEFAULT_ALLOC;
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
  ProduceThenConsume<hipc::dynamic_queue<int>, int>(1, 1, 32, 32);
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
}

TEST_CASE("TestDynamicQueueString") {
  auto *alloc = HSHM_DEFAULT_ALLOC;
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
  ProduceThenConsume<hipc::dynamic_queue<hipc::string>, hipc::string>(1, 1, 32,
                                                                      32);
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
}

TEST_CASE("TestDynamicQueueIntMultiThreaded") {
  auto *alloc = HSHM_DEFAULT_ALLOC;
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
  ProduceAndConsume<hipc::dynamic_queue<int>, int>(8, 1, 8192, 32);
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
}

TEST_CASE("TestDynamicQueueStringMultiThreaded") {
  auto *alloc = HSHM_DEFAULT_ALLOC;
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
  ProduceAndConsume<hipc::dynamic_queue<hipc::string>, hipc::string>(8, 1, 8192,
                                                                     32);
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
}

/**
 * TEST MPSC QUEUE
 * */

TEST_CASE("TestMpscQueueInt") {
  auto *alloc = HSHM_DEFAULT_ALLOC;
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
  ProduceThenConsume<hipc::mpsc_queue<int>, int>(1, 1, 32, 32);
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
}

TEST_CASE("TestMpscQueueString") {
  auto *alloc = HSHM_DEFAULT_ALLOC;
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
  ProduceThenConsume<hipc::mpsc_queue<hipc::string>, hipc::string>(1, 1, 32,
                                                                   32);
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
}

TEST_CASE("TestMpscQueueIntMultiThreaded") {
  auto *alloc = HSHM_DEFAULT_ALLOC;
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
  ProduceAndConsume<hipc::mpsc_queue<int>, int>(8, 1, 8192, 32);
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
}

TEST_CASE("TestMpscQueueStringMultiThreaded") {
  auto *alloc = HSHM_DEFAULT_ALLOC;
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
  ProduceAndConsume<hipc::mpsc_queue<hipc::string>, hipc::string>(8, 1, 8192,
                                                                  32);
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
}

TEST_CASE("TestMpscQueuePeek") {
  auto *alloc = HSHM_DEFAULT_ALLOC;
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);

  auto q = alloc->NewObjLocal<hipc::mpsc_queue<int>>(HSHM_DEFAULT_MEM_CTX).ptr_;
  q->emplace(1);
  int *val;
  q->peek(val, 0);
  REQUIRE(*val == 1);
  hipc::pair<hshm::bitfield32_t, int> *val_pair;
  q->peek(val_pair, 0);
  REQUIRE(val_pair->GetSecond() == 1);
  alloc->DelObj(HSHM_DEFAULT_MEM_CTX, q);

  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
}

/**
 * MPSC Pointer Queue
 * */

TEST_CASE("TestMpscPtrQueueInt") {
  auto *alloc = HSHM_DEFAULT_ALLOC;
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
  ProduceThenConsume<hipc::mpsc_ptr_queue<int>, int>(1, 1, 32, 32);
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
}

TEST_CASE("TestMpscPtrQueueIntMultiThreaded") {
  auto *alloc = HSHM_DEFAULT_ALLOC;
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
  ProduceAndConsume<hipc::mpsc_ptr_queue<int>, int>(8, 1, 8192, 32);
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
}

TEST_CASE("TestMpscOffsetPointerQueueCompile") {
  auto *alloc = HSHM_DEFAULT_ALLOC;
  hipc::mpsc_ptr_queue<hipc::OffsetPointer> queue(alloc);
  hipc::OffsetPointer off_p;
  queue.emplace(hipc::OffsetPointer(5));
  queue.pop(off_p);
  REQUIRE(off_p == hipc::OffsetPointer(5));
}

TEST_CASE("TestMpscPointerQueueCompile") {
  auto *alloc = HSHM_DEFAULT_ALLOC;
  hipc::mpsc_ptr_queue<hipc::Pointer> queue(alloc);
  hipc::Pointer off_p;
  queue.emplace(hipc::Pointer(AllocatorId(5, 2), 1));
  queue.pop(off_p);
  REQUIRE(off_p == hipc::Pointer(AllocatorId(5, 2), 1));
}

/**
 * TEST SPSC QUEUE
 * */

TEST_CASE("TestSpscQueueInt") {
  auto *alloc = HSHM_DEFAULT_ALLOC;
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
  ProduceThenConsume<hipc::spsc_queue<int>, int>(1, 1, 32, 32);
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
}

TEST_CASE("TestSpscQueueString") {
  auto *alloc = HSHM_DEFAULT_ALLOC;
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
  ProduceThenConsume<hipc::spsc_queue<hipc::string>, hipc::string>(1, 1, 32,
                                                                   32);
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
}

TEST_CASE("TestSpscQueuePopBack") {
  auto *alloc = HSHM_DEFAULT_ALLOC;
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
  PAGE_DIVIDE("TEST") {
    hshm::spsc_queue<int> queue(alloc);
    queue.emplace(1);
    queue.emplace(2);
    queue.emplace(3);
    int val;
    queue.pop_back(val);
    REQUIRE(val == 3);
    queue.pop_back(val);
    REQUIRE(val == 2);
    queue.pop_back(val);
    REQUIRE(val == 1);
    REQUIRE(queue.pop_back(val).IsNull());
  }
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
}

TEST_CASE("TestSpscPtrQueuePopBack") {
  auto *alloc = HSHM_DEFAULT_ALLOC;
  PAGE_DIVIDE("TEST") {
    REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
    hshm::spsc_ptr_queue<void *> queue(alloc);
    queue.emplace((void *)1);
    queue.emplace((void *)2);
    queue.emplace((void *)3);
    void *val;
    queue.pop_back(val);
    REQUIRE(val == (void *)3);
    queue.pop_back(val);
    REQUIRE(val == (void *)2);
    queue.pop_back(val);
    REQUIRE(val == (void *)1);
    REQUIRE(queue.pop_back(val).IsNull());
  }
  REQUIRE(alloc->GetCurrentlyAllocatedSize() == 0);
}