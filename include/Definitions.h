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
    enum class TextColor : uint8_t {
        BLACK=30,
        RED=31,
        GREEN=32,
        YELLOW=33,
        BLUE=34,
        MAGENTA=35,
        CYAN=36,
        WHITE=37
    };
    enum class BackgroundColor : uint8_t {
        BLACK=40,
        RED=41,
        GREEN=42,
        YELLOW=43,
        BLUE=44,
        MAGENTA=45,
        CYAN=46,
        WHITE=49
    };
    struct FormatStyle {
        std::optional<TextColor> text_color=TextColor::BLACK;
        std::optional<BackgroundColor> background_color=BackgroundColor::WHITE;
        bool bold = false;
        bool italic = false;
    };
    
} // namespace TemporalStreamLog