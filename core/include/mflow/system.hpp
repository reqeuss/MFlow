#pragma once

#include <cstddef>
#include <string>

namespace mflow {

struct SystemInfo {
    std::string platform;
    std::string architecture;
    std::size_t hardware_threads{1};
    std::size_t recommended_workers{1};
};

SystemInfo system_info();

} // namespace mflow
