#pragma once

#ifndef HCMP_FREE_LIST_H
#define HCMP_FREE_LIST_H

#include <new>

namespace hcmp {

class FreeList {
    void* head_ = nullptr;

public:
    bool empty() noexcept;
    void push(void* block) noexcept;
    void* pop() noexcept;

}; // class FreeList

} // namespace hcmp

#endif // HCMP_FREE_LIST_H