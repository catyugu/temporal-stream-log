#include <ostream>
#include <cstdint>
#include <format>
#include <chrono>
#include <LogEntry.h>
#include <LogFormatter.h>

namespace TemporalStreamLog
{
    enum class LogLevel : uint8_t;
    std::ostream& operator<<(std::ostream& os, const LogEntry& entry)
    {
        LogFormatter formatter;
        if (entry.logLevel == LogLevel::INFO) {
            formatter.setLevelStyle(LogLevel::INFO, FormatStyle{.text_color = 32}); // 绿色
        } else if (entry.logLevel == LogLevel::WARN) {
            formatter.setLevelStyle(LogLevel::WARN, FormatStyle{.text_color = 33, .bold = true}); // 黄色加粗
        } else if (entry.logLevel == LogLevel::ERROR) {
            formatter.setLevelStyle(LogLevel::ERROR, FormatStyle{.text_color = 31, .bold = true}); // 红色加粗
        }
        formatter.setTimestampStyle(FormatStyle{.text_color = 36}); // 青色
        formatter.setMessageStyle(FormatStyle{}); // 默认样式
        os << formatter.format(entry);
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