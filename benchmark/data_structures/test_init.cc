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

#include "test_init.h"
#include "hermes_shm/data_structures/ipc/vector.h"
#include "hermes_shm/memory/allocator/stack_allocator.h"

void MainPretest() {
  // hermes shared memory
  std::string shm_url = "HermesBench";
  AllocatorId alloc_id(0, 1);
  auto mem_mngr = HERMES_MEMORY_MANAGER;
  mem_mngr->UnregisterAllocator(alloc_id);
  mem_mngr->UnregisterBackend(hipc::MemoryBackendId::Get(0));
  auto backend = mem_mngr->CreateBackend<hipc::PosixShmMmap>(
      hipc::MemoryBackendId::Get(0),
      mem_mngr->GetDefaultBackendSize(), shm_url);
  memset(backend->data_, 0, MEGABYTES(16));
  // TODO(llogan): back to good allocator
  mem_mngr->CreateAllocator<hipc::ScalablePageAllocator>(
      hipc::MemoryBackendId::Get(0), alloc_id, 0);


  // Boost shared memory
  BOOST_SEGMENT;
  BOOST_ALLOCATOR(char);
  BOOST_ALLOCATOR(size_t);
  BOOST_ALLOCATOR(std::string);
  BOOST_ALLOCATOR(bipc_string);
  BOOST_ALLOCATOR((std::pair<size_t, char>));
  BOOST_ALLOCATOR((std::pair<size_t, size_t>));
  BOOST_ALLOCATOR((std::pair<size_t, std::string>));
  BOOST_ALLOCATOR((std::pair<size_t, bipc_string>));
}

void MainPosttest() {
  bipc::shared_memory_object::remove("LabstorBoostBench");
}