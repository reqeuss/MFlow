#pragma once

#include "mflow/timestamp.hpp"

#include <cstdint>
#include <string>

namespace mflow {

enum class StreamType { Unknown, Video, Audio, Data };

struct Stream {
    std::uint32_t id{0};
    StreamType type{StreamType::Unknown};
    std::string codec;
    std::int32_t timebase_num{1};
    std::int32_t timebase_den{1};
    std::uint32_t width{0};
    std::uint32_t height{0};
    std::uint32_t sample_rate{0};
    std::uint16_t channels{0};

    Timestamp make_timestamp(std::int64_t value) const noexcept {
        return {value, timebase_num, timebase_den};
    }
};

const char* stream_type_name(StreamType type) noexcept;

} // namespace mflow
