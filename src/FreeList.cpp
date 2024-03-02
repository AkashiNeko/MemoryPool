#include "FreeList.h"

namespace hcmp {

bool FreeList::empty() noexcept {
    return head_ == nullptr;
}

void FreeList::push(void* block) noexcept {
    *reinterpret_cast<void**>(block) = head_;
    head_ = block;
}

void* FreeList::pop() noexcept {
    if (head_) {
        void* result = head_;
        head_ = *reinterpret_cast<void**>(head_);
        return result;
    } else {
        return nullptr;
    }
}

} // namespace hcmp
