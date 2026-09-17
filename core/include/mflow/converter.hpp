#pragma once

#include <filesystem>
#include <string>

namespace mflow {

struct ConvertOptions {
    std::filesystem::path input;
    std::filesystem::path output;
    std::string video_codec;
    std::string audio_codec;
    std::string scale;
    bool overwrite{true};
};

struct ConvertResult {
    bool success{false};
    int exit_code{-1};
    std::string message;
    std::uintmax_t bytes_copied{0};
};

class MediaConverter {
public:
    // Returns true when the built-in native media engine is available.
    static bool backend_available();

    // v0.3 supports native stream/file copying only. Codec and scaling
    // requests are rejected until their native implementations land.
    static ConvertResult convert(const ConvertOptions& options);
};

} // namespace mflow
