#include "mflow/stream.hpp"

namespace mflow {

const char* stream_type_name(StreamType type) noexcept {
    switch (type) {
        case StreamType::Video: return "video";
        case StreamType::Audio: return "audio";
        case StreamType::Data: return "data";
        default: return "unknown";
    }
}

} // namespace mflow
