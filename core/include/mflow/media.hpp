#pragma once

#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>

namespace mflow {

enum class MediaKind { Unknown, Mp4, Matroska, Wav, Mp3, Ogg };

struct MediaInfo {
    MediaKind kind{MediaKind::Unknown};
    std::uintmax_t size_bytes{0};
    std::string description{"Unknown"};
};

class MediaProbe {
public:
    static std::optional<MediaInfo> probe(const std::filesystem::path& path);
    static const char* kind_name(MediaKind kind);
};

} // namespace mflow
