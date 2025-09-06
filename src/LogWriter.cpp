#include <LogWriter.h>

#include <filesystem>
namespace TemporalStreamLog{
    LogWriter::LogWriter(const std::string log_directory){
        std::filesystem::create_directories(log_directory);
        log_directory_ = std::move(log_directory);
    }
    LogWriter::~LogWriter(){
        log_directory_.clear();
    }
    void LogWriter::write(const std::vector<LogEntry>& logs, LogFormatter& formatter){
        if (logs.empty()) {
            return;
        }
        auto now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(now);
        std::tm tm_now;
        localtime_r(&time_t_now, &tm_now);
        char filename[100];
        strftime(filename, sizeof(filename), "log_%Y%m%d_%H.txt", &tm_now);
        auto file_path = log_directory_ / filename;
        std::ofstream ofs(file_path, std::ios::app);
        if (!ofs.is_open()) {
            throw std::runtime_error("Failed to open log file: " + file_path.string());
        }
        for (const auto& log : logs) {
            ofs << formatter.format(log);
        }
        ofs.close();
    }

}