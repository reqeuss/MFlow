#include "mflow/pipeline.hpp"
#include <iostream>
#include <vector>

int main() {
    mflow::Pipeline pipeline;
    pipeline.add_stage("decode", [](mflow::Packet&) {});
    pipeline.add_stage("filter", [](mflow::Packet&) {});
    pipeline.add_stage("encode", [](mflow::Packet&) {});
    std::vector<mflow::Packet> packets(8);
    pipeline.run(packets);
    std::cout << "Pipeline contains " << pipeline.stage_count() << " stages.\n";
}
