#pragma once

#include <evening.hpp>

#include <cstdint>

extern evening::Channel events;

enum class ObjectType {
    None,
    Tree,
    Human,
};

using Id = uint64_t;

namespace event {

struct Create {
    Id id = 0;
    ObjectType type = ObjectType::None;
    float x = 0.f;
    float y = 0.f;
    float radius = 0.f;
};

} // namespace event
