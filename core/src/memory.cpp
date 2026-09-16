#include "mflow/memory.hpp"

namespace mflow {

BufferPool::BufferPool(std::size_t block_size) : block_size_(block_size) {}

std::shared_ptr<std::vector<std::byte>> BufferPool::acquire() {
    std::lock_guard lock(mutex_);
    if (!free_.empty()) {
        auto buffer = free_.back();
        free_.pop_back();
        return buffer;
    }
    return std::make_shared<std::vector<std::byte>>(block_size_);
}

std::size_t BufferPool::block_size() const noexcept { return block_size_; }

} // namespace mflow
