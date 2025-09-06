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
        os << formatter.format(entry);
        return os;
    }
    const char* logLevelToString(LogLevel level){
        switch (level) {
            case LogLevel::INFO: return "[INFO]";
            case LogLevel::WARN: return "[WARN]";
            case LogLevel::ERROR: return "[ERROR]";
            default: return "[UNKNOWN]";
        }
    }
    LogFormatter::LogFormatter(){
        this->setLevelStyle(
            LogLevel::INFO, 
            FormatStyle{
                .text_color = TextColor::GREEN, 
                .bold = true
            }
        );
        this->setLevelStyle(
            LogLevel::WARN, 
            FormatStyle{
                .text_color = TextColor::YELLOW, 
                .bold = true
            }
        );
        this->setLevelStyle(
            LogLevel::ERROR,
            FormatStyle{
                .text_color = TextColor::RED, 
                .bold = true
            }
        );
        this->setTimestampStyle(
            FormatStyle{
                .text_color = TextColor::CYAN
            }
        );
        this->setMessageStyle(
            FormatStyle{}
        );
    }
} // namespace TemporalStreamLog