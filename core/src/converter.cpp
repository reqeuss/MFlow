#include "mflow/converter.hpp"

#include <fstream>

namespace mflow {

bool MediaConverter::backend_available() {
    // The media engine is part of MFlow itself. No external backend is used.
    return true;
}

ConvertResult MediaConverter::convert(const ConvertOptions& options) {
    if (options.input.empty() || options.output.empty()) {
        return {false, 2, "Input and output are required.", 0};
    }

    if (!std::filesystem::is_regular_file(options.input)) {
        return {false, 1, "Input file does not exist or is not a regular file.", 0};
    }

    if (options.input == options.output) {
        return {false, 2, "Input and output must be different files.", 0};
    }

    if (!options.overwrite && std::filesystem::exists(options.output)) {
        return {false, 1, "Output already exists and --no-overwrite was specified.", 0};
    }

    if (!options.video_codec.empty() || !options.audio_codec.empty() || !options.scale.empty()) {
        return {false, 3,
                "The requested codec/scale operation is not implemented natively in v0.3.0. "
                "MFlow never delegates media work to an external executable.", 0};
    }

    std::ifstream input(options.input, std::ios::binary);
    if (!input) {
        return {false, 1, "Unable to open input file.", 0};
    }

    std::error_code ec;
    const auto parent = options.output.parent_path();
    if (!parent.empty()) {
        std::filesystem::create_directories(parent, ec);
        if (ec) {
            return {false, 1, "Unable to create output directory.", 0};
        }
    }

    std::ofstream output(options.output, std::ios::binary | std::ios::trunc);
    if (!output) {
        return {false, 1, "Unable to create output file.", 0};
    }

    constexpr std::size_t buffer_size = 1024 * 1024;
    std::vector<char> buffer(buffer_size);
    std::uintmax_t copied = 0;

    while (input) {
        input.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
        const auto count = input.gcount();
        if (count <= 0) break;
        output.write(buffer.data(), count);
        if (!output) {
            return {false, 1, "Write error while creating output.", copied};
        }
        copied += static_cast<std::uintmax_t>(count);
    }

    output.flush();
    if (!output) {
        return {false, 1, "Failed to finalize output file.", copied};
    }

    return {true, 0, "Native stream copy completed successfully.", copied};
}

} // namespace mflow
