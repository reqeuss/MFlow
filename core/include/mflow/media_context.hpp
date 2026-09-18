#pragma once

#include "mflow/packet_queue.hpp"
#include "mflow/stream.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace mflow {

struct MediaContext {
    std::string container;
    std::uint64_t duration_units{0};
    std::vector<Stream> streams;
    PacketQueue packets;

    Stream* find_stream(std::uint32_t id) noexcept {
        for (auto& stream : streams) {
            if (stream.id == id) return &stream;
        }
        return nullptr;
    }

    const Stream* find_stream(std::uint32_t id) const noexcept {
        for (const auto& stream : streams) {
            if (stream.id == id) return &stream;
        }
        return nullptr;
    }
};

} // namespace mflow
