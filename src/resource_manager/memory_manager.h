/*
 *   BSD LICENSE
 *   Copyright (c) 2021 Samsung Electronics Corporation
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MEMORY_MANAGER_H_
#define MEMORY_MANAGER_H_

#include <list>
#include <vector>

#include "buffer_pool.h"
#include "src/lib/singleton.h"
#include "src/cpu_affinity/affinity_manager.h"

namespace pos
{

class MemoryManager
{
public:
    MemoryManager(
        AffinityManager* affinityManager = AffinityManagerSingleton::Instance(),
        HugepageAllocator* hugepageAllocator = nullptr);
    BufferPool* CreateBufferPool(BufferInfo& info);
    void DeleteBufferPool(BufferPool* pool);

private:
    bool _CheckBufferPolicy(const BufferInfo& info);
    int _GetDefaultSocket(void);

    std::list<BufferPool*> bufferPools;

    AffinityManager* affinityManager;
    HugepageAllocator* hugepageAllocator;
};

using MemoryManagerSingleton = Singleton<MemoryManager>;

} // namespace pos

#endif // MEMORY_MANAGER_H_
