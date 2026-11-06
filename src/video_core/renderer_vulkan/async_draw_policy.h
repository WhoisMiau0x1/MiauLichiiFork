// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <cstddef>
#include <cstdlib>

#include "common/common_types.h"

namespace Vulkan {

inline bool CanDiscardPendingDraw(bool native, bool depth_enabled, u32 index_count,
                                  u32 vertex_count) {
    static const bool allow_async_discard = [] {
        const char* val = std::getenv("EDEN_NX2_ASYNC_DISCARD");
        return val != nullptr && val[0] == '1';
    }();
    if (allow_async_discard) {
        return true;
    }
    if (native) {
        return false;
    }
    // Preserve the legacy async-shader heuristic.
    return depth_enabled || (index_count > 6 && vertex_count > 6);
}

constexpr bool DefersShaderEmission(bool enabled, bool native, size_t pending, size_t capacity) {
    return enabled && native && pending < capacity;
}

} // namespace Vulkan
