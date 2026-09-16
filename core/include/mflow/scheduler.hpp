#pragma once

#include <cstddef>
#include <functional>

namespace mflow {

class Scheduler {
public:
    explicit Scheduler(std::size_t workers = 0);
    void parallel_for(std::size_t count, const std::function<void(std::size_t)>& fn);
    std::size_t workers() const noexcept;

private:
    std::size_t workers_;
};

} // namespace mflow
