#include <ostream>
#include <cstdint>
#include <format>
#include <chrono>
#include <LogEntry.h>

namespace TemporalStreamLog
{
    enum class LogLevel : uint8_t;
    std::ostream& operator<<(std::ostream& os, const LogEntry& entry)
    {
        auto formattedTime = std::format(
            "{:%Y-%m-%d %H:%M:%S}",
            std::chrono::time_point_cast<std::chrono::seconds>(entry.timestamp)
        );
        os << "[" << formattedTime << "] "
            << logLevelToString(entry.logLevel)<< ": "
            << entry.message;
        return os;
    }
    const char* logLevelToString(LogLevel level){
        switch (level) {
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARN: return "WARN";
            case LogLevel::ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }
} // namespace TemporalStreamLog