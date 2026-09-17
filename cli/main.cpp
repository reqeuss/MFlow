#include "mflow/converter.hpp"
#include "mflow/media.hpp"
#include "mflow/pipeline.hpp"
#include "mflow/scheduler.hpp"
#include "mflow/system.hpp"
#include "mflow/version.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace {
void usage() {
    std::cout << "MFlow " << MFLOW_VERSION_STRING << "\n\nUsage:\n"
              << "  mflow version\n"
              << "  mflow info\n"
              << "  mflow probe <file>\n"
              << "  mflow convert <input> <output> [options]\n"
              << "  mflow pipeline-demo\n"
              << "  mflow benchmark\n\n"
              << "Native convert options:\n"
              << "  --no-overwrite         Refuse to replace output\n\n"
              << "Codec and scaling options are reserved for future native implementations.\n";
}

bool take_value(int& index, int argc, char** argv, std::string& value) {
    if (index + 1 >= argc) return false;
    value = argv[++index];
    return true;
}
} // namespace

int main(int argc, char** argv) {
    if (argc < 2) {
        usage();
        return 0;
    }

    const std::string command = argv[1];

    if (command == "version") {
        std::cout << "MFlow " << MFLOW_VERSION_STRING << '\n';
        return 0;
    }

    if (command == "info") {
        const auto info = mflow::system_info();
        std::cout << "MFlow " << MFLOW_VERSION_STRING << '\n'
                  << "Platform: " << info.platform << '\n'
                  << "Architecture: " << info.architecture << '\n'
                  << "Hardware threads: " << info.hardware_threads << '\n'
                  << "Recommended workers: " << info.recommended_workers << '\n'
                  << "Media engine: native\n"
                  << "External media executables: none\n";
        return 0;
    }

    if (command == "probe") {
        if (argc < 3) {
            std::cerr << "Missing file.\n";
            return 2;
        }
        const auto result = mflow::MediaProbe::probe(argv[2]);
        if (!result) {
            std::cerr << "Unable to read file.\n";
            return 1;
        }
        std::cout << "Type: " << mflow::MediaProbe::kind_name(result->kind) << '\n'
                  << "Description: " << result->description << '\n'
                  << "Size: " << result->size_bytes << " bytes\n";
        return 0;
    }

    if (command == "convert") {
        if (argc < 4) {
            std::cerr << "Usage: mflow convert <input> <output> [--no-overwrite]\n";
            return 2;
        }

        mflow::ConvertOptions options;
        options.input = argv[2];
        options.output = argv[3];

        for (int i = 4; i < argc; ++i) {
            const std::string arg = argv[i];
            if (arg == "--no-overwrite") {
                options.overwrite = false;
            } else if (arg == "--video-codec") {
                if (!take_value(i, argc, argv, options.video_codec)) return 2;
            } else if (arg == "--audio-codec") {
                if (!take_value(i, argc, argv, options.audio_codec)) return 2;
            } else if (arg == "--scale") {
                if (!take_value(i, argc, argv, options.scale)) return 2;
            } else {
                std::cerr << "Unknown option: " << arg << '\n';
                return 2;
            }
        }

        std::cout << "MFlow native media operation\n"
                  << "Input:  " << options.input.string() << '\n'
                  << "Output: " << options.output.string() << '\n';

        const auto result = mflow::MediaConverter::convert(options);
        if (!result.success) {
            std::cerr << "Error: " << result.message << '\n';
            return result.exit_code == -1 ? 1 : result.exit_code;
        }

        std::cout << result.message << '\n'
                  << "Bytes copied: " << result.bytes_copied << '\n';
        return 0;
    }

    if (command == "pipeline-demo") {
        mflow::Pipeline pipeline;
        pipeline.add_stage("source", [](mflow::Packet&) {});
        pipeline.add_stage("transform", [](mflow::Packet& packet) { ++packet.sequence; });
        pipeline.add_stage("sink", [](mflow::Packet&) {});
        std::vector<mflow::Packet> packets(4);
        pipeline.run(packets);
        std::cout << "Pipeline stages: " << pipeline.stage_count() << '\n';
        for (const auto& name : pipeline.stage_names()) std::cout << "  -> " << name << '\n';
        std::cout << "Processed packets: " << packets.size() << '\n';
        return 0;
    }

    if (command == "benchmark") {
        constexpr std::size_t task_count = 200000;
        mflow::Scheduler scheduler;
        std::vector<std::uint64_t> values(task_count);
        const auto start = std::chrono::steady_clock::now();
        scheduler.parallel_for(task_count, [&](std::size_t index) {
            values[index] = static_cast<std::uint64_t>(index ^ (index >> 3));
        });
        const auto end = std::chrono::steady_clock::now();
        const double milliseconds = std::chrono::duration<double, std::milli>(end - start).count();
        std::uint64_t checksum = 0;
        for (const auto value : values) checksum ^= value;
        std::cout << "MFlow scheduler benchmark\nWorkers: " << scheduler.workers()
                  << "\nTasks: " << task_count << "\nTime: " << milliseconds
                  << " ms\nChecksum: " << checksum << '\n';
        return 0;
    }

    usage();
    return 1;
}
