#include "mflow/scheduler.hpp"
#include <algorithm>
#include <atomic>
#include <thread>
#include <vector>

namespace mflow {
Scheduler::Scheduler(std::size_t workers) {
    workers_ = workers == 0 ? std::max<std::size_t>(1, std::thread::hardware_concurrency()) : workers;
}
void Scheduler::parallel_for(std::size_t count, const std::function<void(std::size_t)>& fn) {
    if (count == 0) return;
    const auto thread_count = std::min(workers_, count);
    std::atomic<std::size_t> next{0};
    std::vector<std::thread> threads;
    threads.reserve(thread_count);
    for (std::size_t i = 0; i < thread_count; ++i) {
        threads.emplace_back([&]() {
            while (true) {
                const auto index = next.fetch_add(1, std::memory_order_relaxed);
                if (index >= count) break;
                fn(index);
            }
        });
    }
    for (auto& thread : threads) thread.join();
}
std::size_t Scheduler::workers() const noexcept { return workers_; }
} // namespace mflow
