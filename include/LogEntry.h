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
} // namespace TemporalStreamLog