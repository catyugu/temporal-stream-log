#pragma once
#include <cstdint>
#include <chrono>
namespace TemporalStreamLog
{
    enum class LogLevel : uint8_t {
        INFO,
        WARN,
        ERROR
    };
} // namespace TemporalStreamLog