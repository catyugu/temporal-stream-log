#pragma once
#include <chrono>
#include <Definitions.h>
#include <string>
namespace TemporalStreamLog
{
    struct LogEntry
    {
        std::chrono::high_resolution_clock::time_point timestamp;
        LogLevel logLevel;
        std::string message;
    };
    std::ostream& operator<<(std::ostream& os, const LogEntry& entry);
    const char* logLevelToString(LogLevel level);
} // namespace TemporalStreamLog