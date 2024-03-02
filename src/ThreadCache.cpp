#include "ThreadCache.h"
#include <cstdio>

namespace hcmp {

namespace {

const int INDEX_8B   = 3;
const int INDEX_16B  = 4;
const int INDEX_128B = 7;
const int INDEX_1KB  = 10;
const int INDEX_8KB  = 13;

const std::size_t BOUNDARY_8B   = 1 << 7;  // 128B
const std::size_t BOUNDARY_16B  = 1 << 10; // 1KB
const std::size_t BOUNDARY_128B = 1 << 13; // 8KB
const std::size_t BOUNDARY_1KB  = 1 << 16; // 64KB
const std::size_t BOUNDARY_8KB  = 1 << 18; // 256KB

const std::size_t PrevBoundary[5] = {
    0U, BOUNDARY_8B, BOUNDARY_16B, BOUNDARY_128B, BOUNDARY_1KB,
};

const int SizeIndex[5] = {
    INDEX_8B, INDEX_16B, INDEX_128B, INDEX_1KB, INDEX_8KB,
};

const std::size_t BucketIndexBegin[5] = { 0, 16, 72, 128, 184 };

inline std::size_t bucket_offset_(
        std::size_t size, int align_offset) {
    return ((size - 1) >> align_offset);
}

inline std::size_t single_block_size_index_(std::size_t size) {
    if (size <= BOUNDARY_8B) return 0U;
    if (size <= BOUNDARY_16B) return 1U;
    if (size <= BOUNDARY_128B) return 2U;
    if (size <= BOUNDARY_1KB) return 3U;
    if (size <= BOUNDARY_8KB) return 4U;
    else return -1U; // never
}

} // anonymous namespace

void* ThreadCache::alloc(std::size_t size) {
    const std::size_t bsz_index = single_block_size_index_(size);
    const std::size_t offset = bucket_offset_(
        size - PrevBoundary[bsz_index], SizeIndex[bsz_index]);
    const std::size_t freelists_index = BucketIndexBegin[bsz_index] + offset;
    const std::size_t block_size = (1 << SizeIndex[bsz_index]) * (offset + 1);
    return nullptr;
}

void ThreadCache::free(void* ptr, std::size_t size) {

}

} // namespace hcmp
