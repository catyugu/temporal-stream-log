#pragma once
#include <map>
#include "LogEntry.h"
namespace TemporalStreamLog
{
    class LogFormatter
    {
    public:
        LogFormatter();
        // 为不同部分设置样式的方法
        void setTimestampStyle(const FormatStyle &style);
        void setMessageStyle(const FormatStyle &style);
        void setLevelStyle(LogLevel level, const FormatStyle &style);

        // 核心格式化方法
        std::string format(const LogEntry &entry) const;

    private:
        // 内部存储的样式配置
        FormatStyle timestamp_style_;
        FormatStyle message_style_;
        std::map<LogLevel, FormatStyle> level_styles_;

        // 一个私有的辅助方法，用于生成ANSI代码字符串
        std::string applyStyle(const std::string &text, const FormatStyle &style) const;
    };

    static LogFormatter defaultFormatter = LogFormatter();
} // namespace TemporalStreamLog