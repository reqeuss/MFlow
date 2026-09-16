#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace mflow {

struct Packet {
    std::shared_ptr<std::vector<std::byte>> buffer;
    std::size_t size{0};
    std::uint64_t sequence{0};
};

using Stage = std::function<void(Packet&)>;

class Pipeline {
public:
    void add_stage(std::string name, Stage stage);
    void run(std::vector<Packet>& packets);
    std::size_t stage_count() const noexcept;
    const std::vector<std::string>& stage_names() const noexcept;

private:
    std::vector<std::string> names_;
    std::vector<Stage> stages_;
};

} // namespace mflow
