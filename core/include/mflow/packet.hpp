#pragma once

#include "mflow/timestamp.hpp"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

namespace mflow {

enum class PacketFlags : std::uint32_t {
    None = 0,
    Keyframe = 1u << 0,
    Discontinuity = 1u << 1,
    EndOfStream = 1u << 2
};

constexpr PacketFlags operator|(PacketFlags a, PacketFlags b) noexcept {
    return static_cast<PacketFlags>(static_cast<std::uint32_t>(a) | static_cast<std::uint32_t>(b));
}

constexpr bool has_flag(PacketFlags value, PacketFlags flag) noexcept {
    return (static_cast<std::uint32_t>(value) & static_cast<std::uint32_t>(flag)) != 0;
}

struct Packet {
    std::shared_ptr<std::vector<std::byte>> buffer;
    std::size_t size{0};
    std::uint32_t stream_id{0};
    Timestamp pts{};
    Timestamp dts{};
    Timestamp duration{};
    PacketFlags flags{PacketFlags::None};
    std::uint64_t sequence{0};

    const std::byte* data() const noexcept {
        return buffer && size <= buffer->size() ? buffer->data() : nullptr;
    }
};

} // namespace mflow
