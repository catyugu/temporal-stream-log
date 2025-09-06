#pragma once
#include <string>
#include <vector>
#include <LogEntry.h>
#include <LogFormatter.h>
#include <fstream>
#include <filesystem>
namespace TemporalStreamLog
{
    class LogWriter{
    public: 
        LogWriter(const std::string log_directory = "./logs");
        ~LogWriter();
        void write(const std::vector<LogEntry>& logs, LogFormatter& formatter=defaultFormatter);
    private:
        std::filesystem::path log_directory_;
    };
} // namespace TemporalStreamLog
