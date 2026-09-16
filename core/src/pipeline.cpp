#include "mflow/pipeline.hpp"
#include <utility>

namespace mflow {
void Pipeline::add_stage(std::string name, Stage stage) {
    names_.push_back(std::move(name));
    stages_.push_back(std::move(stage));
}
void Pipeline::run(std::vector<Packet>& packets) {
    for (auto& stage : stages_) for (auto& packet : packets) stage(packet);
}
std::size_t Pipeline::stage_count() const noexcept { return stages_.size(); }
const std::vector<std::string>& Pipeline::stage_names() const noexcept { return names_; }
} // namespace mflow
