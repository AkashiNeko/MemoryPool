#pragma once

#ifndef HCMP_THREAD_CACHE_H
#define HCMP_THREAD_CACHE_H

#include <cstdint>
#include "FreeList.h"



namespace hcmp {

class ThreadCache {
    FreeList freelists_[208] {};

public:
    void* alloc(std::size_t size);
    void free(void* ptr, std::size_t size);

}; // class ThreadCache

} // namespace hcmp

#endif // HCMP_THREAD_CACHE_H
