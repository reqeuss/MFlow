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

namespace { void usage() { std::cout << "MFlow " << MFLOW_VERSION_STRING << "\n\nUsage:\n  mflow version\n  mflow info\n  mflow probe <file>\n  mflow pipeline-demo\n  mflow benchmark\n"; } }

int main(int argc, char** argv) {
    if (argc < 2) { usage(); return 0; }
    const std::string command = argv[1];
    if (command == "version") { std::cout << "MFlow " << MFLOW_VERSION_STRING << '\n'; return 0; }
    if (command == "info") {
        const auto info = mflow::system_info();
        std::cout << "MFlow " << MFLOW_VERSION_STRING << '\n'
                  << "Platform: " << info.platform << '\n'
                  << "Architecture: " << info.architecture << '\n'
                  << "Hardware threads: " << info.hardware_threads << '\n'
                  << "Recommended workers: " << info.recommended_workers << '\n';
        return 0;
    }
    if (command == "probe") {
        if (argc < 3) { std::cerr << "Missing file.\n"; return 2; }
        const auto result = mflow::MediaProbe::probe(argv[2]);
        if (!result) { std::cerr << "Unable to read file.\n"; return 1; }
        std::cout << "Type: " << mflow::MediaProbe::kind_name(result->kind) << '\n'
                  << "Description: " << result->description << '\n'
                  << "Size: " << result->size_bytes << " bytes\n";
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
