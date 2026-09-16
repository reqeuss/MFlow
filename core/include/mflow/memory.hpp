#pragma once

#include <cstddef>
#include <memory>
#include <mutex>
#include <vector>

namespace mflow {

class BufferPool {
public:
    explicit BufferPool(std::size_t block_size = 1024 * 1024);
    std::shared_ptr<std::vector<std::byte>> acquire();
    std::size_t block_size() const noexcept;

private:
    std::size_t block_size_;
    std::mutex mutex_;
    std::vector<std::shared_ptr<std::vector<std::byte>>> free_;
};

} // namespace mflow
