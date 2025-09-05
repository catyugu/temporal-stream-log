#pragma once
#include <Definitions.h>
#include <LogEntry.h>
#include <deque>
#include <mutex>
namespace TemporalStreamLog
{
    class LogBuffer{
    public:
        LogBuffer(size_t capacity): capacity_(capacity) {}
        ~LogBuffer() = default;

        void addLog(LogEntry entry);

        std::vector<LogEntry> drain();
    private:
        size_t capacity_;
        std::deque<LogEntry> buffer_;
        std::mutex mutex_;
    };

    
} // namespace TemporalStreamLog
