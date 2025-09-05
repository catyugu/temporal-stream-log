#pragma once
#include <cstdint>
#include <chrono>
#include <optional>
namespace TemporalStreamLog
{
    enum class LogLevel : uint8_t {
        INFO,
        WARN,
        ERROR
    };
    struct FormatStyle {
        std::optional<int> text_color;
        std::optional<int> background_color;
        bool bold = false;
        bool italic = false;
    };
} // namespace TemporalStreamLog