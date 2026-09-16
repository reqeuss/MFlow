#include "mflow/scheduler.hpp"
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

int main() {
    constexpr std::size_t task_count = 1'000'000;
    std::vector<std::uint64_t> data(task_count);
    mflow::Scheduler scheduler;
    const auto start = std::chrono::steady_clock::now();
    scheduler.parallel_for(task_count, [&](std::size_t index) {
        data[index] = static_cast<std::uint64_t>(index) * 2654435761ULL;
    });
    const auto end = std::chrono::steady_clock::now();
    const double seconds = std::chrono::duration<double>(end - start).count();
    std::uint64_t checksum = 0;
    for (const auto value : data) checksum ^= value;
    std::cout << "MFlow v0.1 benchmark\n"
              << "tasks=" << task_count << '\n'
              << "workers=" << scheduler.workers() << '\n'
              << "seconds=" << seconds << '\n'
              << "checksum=" << checksum << '\n';
}
