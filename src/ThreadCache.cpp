#include "ThreadCache.h"
#include <utility>
#include <cstdio>
namespace hcmp {

namespace {

const int MOVE_8B   = 3;  // 1 << 3  (8)
const int MOVE_16B  = 4;  // 1 << 4  (16)
const int MOVE_128B = 7;  // 1 << 7  (128)
const int MOVE_1KB  = 10; // 1 << 10 (1K)
const int MOVE_8KB  = 13; // 1 << 13 (8K)

const int Moves[5] = {
    MOVE_8B, MOVE_16B, MOVE_128B, MOVE_1KB, MOVE_8KB,
};

const std::size_t BOUNDARY_8B   = 1 << 7;  // 128B
const std::size_t BOUNDARY_16B  = 1 << 10; // 1KB
const std::size_t BOUNDARY_128B = 1 << 13; // 8KB
const std::size_t BOUNDARY_1KB  = 1 << 16; // 64KB
const std::size_t BOUNDARY_8KB  = 1 << 18; // 256KB

const std::size_t PrevBoundarys[5] = {
    0U,            // (0,8B]
    BOUNDARY_8B,   // (8B,16B]
    BOUNDARY_16B,  // (16B,128B]
    BOUNDARY_128B, // (128B,1KB]
    BOUNDARY_1KB,  // (1KB,8KB]
};

const std::size_t BucketIndexBegins[5] = {
    0,    // [0,16)
    16,   // [16,72)
    72,   // [72,128)
    128,  // [128,184)
    184,  // [184,208)
};

inline std::size_t single_block_size_index_(std::size_t size) {
    if (size <= BOUNDARY_8B)   return 0U;
    if (size <= BOUNDARY_16B)  return 1U;
    if (size <= BOUNDARY_128B) return 2U;
    if (size <= BOUNDARY_1KB)  return 3U;
    if (size <= BOUNDARY_8KB)  return 4U;
    else return -1U; // never
}

inline std::pair<std::size_t, std::size_t> get_index_with_block_size_(
        std::size_t size) {
    const std::size_t bsz_index = single_block_size_index_(size),
    offset = (size - PrevBoundarys[bsz_index] - 1) >> Moves[bsz_index];
    return { BucketIndexBegins[bsz_index] + offset,
        (1 << Moves[bsz_index]) * (offset + 1) + PrevBoundarys[bsz_index] };
}

} // anonymous namespace

void* ThreadCache::alloc(std::size_t size) {
    auto [index, block_size] = get_index_with_block_size_(size);
    void* free_block = freelists_[index].pop();
    if (free_block) return free_block;
    // free_block == nullptr
    // TODO: get memory from central cache
    return nullptr;
}

void ThreadCache::free(void* ptr, std::size_t size) {

}

} // namespace hcmp
