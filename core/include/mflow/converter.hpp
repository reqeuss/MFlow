#pragma once

#include <filesystem>
#include <string>
#include <vector>

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
};

class MediaConverter {
public:
    static bool backend_available();
    static ConvertResult convert(const ConvertOptions& options);
};

} // namespace mflow
