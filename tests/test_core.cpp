#include "mflow/converter.hpp"
#include "mflow/memory.hpp"
#include "mflow/media_context.hpp"
#include "mflow/packet_queue.hpp"
#include "mflow/pipeline.hpp"
#include "mflow/scheduler.hpp"
#include "mflow/system.hpp"
#include "mflow/timestamp.hpp"
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
    {
        assert(mflow::MediaConverter::backend_available());
    }
    {
        const auto ts = mflow::timestamp(90000, 1, 90000);
        assert(ts.value == 90000);
        assert(ts.seconds() == 1.0);

        mflow::Packet packet;
        packet.stream_id = 7;
        packet.pts = ts;
        packet.dts = ts;
        packet.flags = mflow::PacketFlags::Keyframe;
        assert(packet.stream_id == 7);
        assert(mflow::has_flag(packet.flags, mflow::PacketFlags::Keyframe));

        mflow::Stream video;
        video.id = 7;
        video.type = mflow::StreamType::Video;
        video.codec = "unknown";
        video.timebase_num = 1;
        video.timebase_den = 90000;
        assert(video.make_timestamp(90000).seconds() == 1.0);
        assert(std::string(mflow::stream_type_name(video.type)) == "video");

        mflow::MediaContext context;
        context.container = "native";
        context.streams.push_back(video);
        assert(context.find_stream(7) != nullptr);
        assert(context.find_stream(99) == nullptr);

        mflow::PacketQueue queue;
        queue.push(packet);
        assert(queue.size() == 1);
        const auto peeked = queue.peek();
        assert(peeked && peeked->stream_id == 7);
        const auto popped = queue.pop();
        assert(popped && popped->stream_id == 7);
        assert(queue.empty());
    }
    std::cout << "All MFlow tests passed.\n";
    return 0;
}
