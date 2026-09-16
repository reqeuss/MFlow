#include "mflow/memory.hpp"
#include "mflow/pipeline.hpp"
#include "mflow/scheduler.hpp"
#include "mflow/system.hpp"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

int main() {
    {
        mflow::Pipeline pipeline;
        pipeline.add_stage("increment", [](mflow::Packet& packet) { ++packet.sequence; });
        std::vector<mflow::Packet> packets(10);
        pipeline.run(packets);
        for (const auto& packet : packets) assert(packet.sequence == 1);
        assert(pipeline.stage_count() == 1);
    }
    {
        mflow::BufferPool pool(4096);
        auto buffer = pool.acquire();
        assert(buffer);
        assert(buffer->size() == 4096);
    }
    {
        mflow::Scheduler scheduler(4);
        std::vector<std::uint64_t> values(1000);
        scheduler.parallel_for(values.size(), [&](std::size_t index) {
            values[index] = static_cast<std::uint64_t>(index) * static_cast<std::uint64_t>(index);
        });
        assert(values[123] == 15129);
    }
    {
        const auto info = mflow::system_info();
        assert(info.hardware_threads >= 1);
        assert(info.recommended_workers >= 1);
    }
    std::cout << "All MFlow tests passed.\n";
    return 0;
}
