#include <LogBuffer.h>
namespace TemporalStreamLog
{
    void LogBuffer::addLog(LogEntry entry)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (buffer_.size() >= capacity_)
        {
            buffer_.pop_front();
        }
        buffer_.push_back(entry);
    }

    std::vector<LogEntry> LogBuffer::drain()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto logs = std::vector<LogEntry>(buffer_.size());
        std::move(buffer_.begin(), buffer_.end(), logs.begin());
        buffer_.clear();
        return logs;
    }
} // namespace TemporalStreamLog