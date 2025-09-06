#include <LogFormatter.h>
namespace TemporalStreamLog{
    void LogFormatter::setTimestampStyle(const FormatStyle &style) {
        timestamp_style_ = style;
    }
    void LogFormatter::setMessageStyle(const FormatStyle &style) {
        message_style_ = style;
    }
    void LogFormatter::setLevelStyle(LogLevel level, const FormatStyle &style) {
        level_styles_[level] = style;
    }

    std::string LogFormatter::format(const LogEntry &entry) const {
        // 格式化时间戳
        auto timestamp_str = std::format(
            "[{:%Y-%m-%d %H:%M:%S}]",
            std::chrono::time_point_cast<std::chrono::seconds>(entry.timestamp)
        ); 

        // 获取日志级别字符串
        std::string level_str = logLevelToString(entry.logLevel);

        // 应用样式
        std::string styled_timestamp = applyStyle(timestamp_str, timestamp_style_);
        FormatStyle level_style = level_styles_.count(entry.logLevel) ? level_styles_.at(entry.logLevel) : FormatStyle{};
        std::string styled_level = applyStyle(level_str, level_style);
        std::string styled_message = applyStyle(entry.message, message_style_);

        // 组合最终字符串
        return styled_timestamp + " " +  styled_level + " " + styled_message;
    }

    std::string LogFormatter::applyStyle(const std::string &text, const FormatStyle &style) const {
        std::string ansi_code = "\033[";
        bool first = true;

        if (style.text_color) {
            ansi_code += std::to_string(static_cast<int>(*style.text_color));
            first = false;
        }
        if (style.background_color) {
            if (!first) ansi_code += ";";
            ansi_code += std::to_string(static_cast<int>(*style.background_color));
            first = false;
        }
        if (style.bold) {
            if (!first) ansi_code += ";";
            ansi_code += "1";
            first = false;
        }
        if (style.italic) {
            if (!first) ansi_code += ";";
            ansi_code += "3";
            first = false;
        }
        if (first) {
            return text; // 没有样式，直接返回原文本
        }
        ansi_code += "m";

        return ansi_code + text + "\033[0m"; // 结尾重置样式
    }
}