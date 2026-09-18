#pragma once

#include "mflow/packet.hpp"

#include <cstddef>
#include <deque>
#include <mutex>
#include <optional>
#include <utility>

namespace mflow {

class PacketQueue {
public:
    void push(Packet packet) {
        std::lock_guard lock(mutex_);
        queue_.push_back(std::move(packet));
    }

    std::optional<Packet> pop() {
        std::lock_guard lock(mutex_);
        if (queue_.empty()) return std::nullopt;
        Packet packet = std::move(queue_.front());
        queue_.pop_front();
        return packet;
    }

    std::optional<Packet> peek() const {
        std::lock_guard lock(mutex_);
        if (queue_.empty()) return std::nullopt;
        return queue_.front();
    }

    std::size_t size() const {
        std::lock_guard lock(mutex_);
        return queue_.size();
    }

    bool empty() const {
        std::lock_guard lock(mutex_);
        return queue_.empty();
    }

    void clear() {
        std::lock_guard lock(mutex_);
        queue_.clear();
    }

private:
    mutable std::mutex mutex_;
    std::deque<Packet> queue_;
};

} // namespace mflow
