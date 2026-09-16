#include "mflow/media.hpp"

#include <array>
#include <fstream>

namespace mflow {
namespace {
bool starts_with(const std::array<unsigned char, 16>& b, std::initializer_list<unsigned char> bytes) {
    if (bytes.size() > b.size()) return false;
    std::size_t i = 0;
    for (auto value : bytes) if (b[i++] != value) return false;
    return true;
}
}

std::optional<MediaInfo> MediaProbe::probe(const std::filesystem::path& path) {
    if (!std::filesystem::is_regular_file(path)) return std::nullopt;
    std::ifstream input(path, std::ios::binary);
    if (!input) return std::nullopt;

    std::array<unsigned char, 16> header{};
    input.read(reinterpret_cast<char*>(header.data()), static_cast<std::streamsize>(header.size()));
    const auto bytes_read = static_cast<std::size_t>(input.gcount());

    MediaInfo info;
    info.size_bytes = std::filesystem::file_size(path);

    if (bytes_read >= 12 && header[4] == 'f' && header[5] == 't' && header[6] == 'y' && header[7] == 'p') {
        info.kind = MediaKind::Mp4;
        info.description = "ISO Base Media / MP4 family";
    } else if (bytes_read >= 4 && starts_with(header, {0x1A, 0x45, 0xDF, 0xA3})) {
        info.kind = MediaKind::Matroska;
        info.description = "Matroska / WebM family";
    } else if (bytes_read >= 12 && starts_with(header, {'R','I','F','F'}) && header[8] == 'W' && header[9] == 'A' && header[10] == 'V' && header[11] == 'E') {
        info.kind = MediaKind::Wav;
        info.description = "RIFF/WAVE audio";
    } else if (bytes_read >= 3 && starts_with(header, {'I','D','3'})) {
        info.kind = MediaKind::Mp3;
        info.description = "MP3 with ID3 metadata";
    } else if (bytes_read >= 4 && starts_with(header, {'O','g','g','S'})) {
        info.kind = MediaKind::Ogg;
        info.description = "Ogg container";
    }
    return info;
}

const char* MediaProbe::kind_name(MediaKind kind) {
    switch (kind) {
        case MediaKind::Mp4: return "mp4";
        case MediaKind::Matroska: return "matroska";
        case MediaKind::Wav: return "wav";
        case MediaKind::Mp3: return "mp3";
        case MediaKind::Ogg: return "ogg";
        default: return "unknown";
    }
}
} // namespace mflow
