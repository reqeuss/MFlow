#pragma once

#include <cstdint>

namespace mflow {

struct Timestamp {
    std::int64_t value{0};
    std::int32_t timebase_num{1};
    std::int32_t timebase_den{1};

    constexpr double seconds() const noexcept {
        return timebase_den == 0 ? 0.0
                                 : static_cast<double>(value) * static_cast<double>(timebase_num) /
                                       static_cast<double>(timebase_den);
    }
};

constexpr Timestamp timestamp(std::int64_t value, std::int32_t num = 1, std::int32_t den = 1) noexcept {
    return {value, num, den};
}

} // namespace mflow
