#include "mflow/system.hpp"
#include <algorithm>
#include <thread>

namespace mflow {
SystemInfo system_info() {
    SystemInfo info;
    info.hardware_threads = std::max<std::size_t>(1, std::thread::hardware_concurrency());
    info.recommended_workers = info.hardware_threads > 2 ? info.hardware_threads - 2 : 1;
#if defined(_WIN32)
    info.platform = "windows";
#elif defined(__linux__)
    info.platform = "linux";
#elif defined(__APPLE__)
    info.platform = "macos";
#else
    info.platform = "unknown";
#endif
#if defined(__x86_64__) || defined(_M_X64)
    info.architecture = "x86_64";
#elif defined(__aarch64__) || defined(_M_ARM64)
    info.architecture = "arm64";
#elif defined(__i386__) || defined(_M_IX86)
    info.architecture = "x86";
#else
    info.architecture = "unknown";
#endif
    return info;
}
} // namespace mflow
