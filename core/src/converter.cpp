#include "mflow/converter.hpp"

#include <cstdlib>
#include <sstream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

namespace mflow {
namespace {

std::string quote_argument(const std::filesystem::path& path) {
    const std::string value = path.string();
    std::string quoted = "\"";
    for (const char ch : value) {
        if (ch == '"') quoted += '\\';
        quoted += ch;
    }
    quoted += "\"";
    return quoted;
}

std::string quote_value(const std::string& value) {
    std::string quoted = "\"";
    for (const char ch : value) {
        if (ch == '"') quoted += '\\';
        quoted += ch;
    }
    quoted += "\"";
    return quoted;
}

} // namespace

bool MediaConverter::backend_available() {
#ifdef _WIN32
    return std::system("where ffmpeg >nul 2>nul") == 0;
#else
    return std::system("command -v ffmpeg >/dev/null 2>&1") == 0;
#endif
}

ConvertResult MediaConverter::convert(const ConvertOptions& options) {
    if (options.input.empty() || options.output.empty()) {
        return {false, -1, "Input and output are required."};
    }

    if (!std::filesystem::exists(options.input)) {
        return {false, -1, "Input file does not exist: " + options.input.string()};
    }

    if (!backend_available()) {
        return {false, -1, "No media conversion backend found. Install ffmpeg and make it available on PATH."};
    }

    std::ostringstream command;
    command << "ffmpeg ";
    command << (options.overwrite ? "-y " : "-n ");
    command << "-hide_banner -loglevel error ";
    command << "-i " << quote_argument(options.input) << ' ';

    if (!options.video_codec.empty()) {
        command << "-c:v " << quote_value(options.video_codec) << ' ';
    }
    if (!options.audio_codec.empty()) {
        command << "-c:a " << quote_value(options.audio_codec) << ' ';
    }
    if (!options.scale.empty()) {
        command << "-vf " << quote_value("scale=" + options.scale) << ' ';
    }

    command << quote_argument(options.output);

    const int exit_code = std::system(command.str().c_str());
    if (exit_code != 0) {
        return {false, exit_code, "Conversion backend returned a non-zero exit code."};
    }

    if (!std::filesystem::exists(options.output)) {
        return {false, exit_code, "Conversion reported success but the output file was not created."};
    }

    return {true, exit_code, "Conversion completed successfully."};
}

} // namespace mflow
