#include <iostream>
#include <source_location>
#include <LogBuffer.h>
#include <thread>
void addLogs(TemporalStreamLog::LogBuffer& logBuffer) {
    for (int i = 0; i < 20; ++i) {
        logBuffer.addLog(TemporalStreamLog::LogEntry{
            .timestamp = std::chrono::high_resolution_clock::now(),
            .logLevel = TemporalStreamLog::LogLevel::INFO,
            .message = "Log message " + std::to_string(i)
        });
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
int main(){
    TemporalStreamLog::LogBuffer buffer(10);
    std::thread t1(addLogs, std::ref(buffer));
    std::thread t2(addLogs, std::ref(buffer));
    t1.join();
    t2.join();
    auto logs = buffer.drain();
    for (const auto& log : logs) {
        std::cout << "[" << log.timestamp.time_since_epoch().count() << "] "
                    << static_cast<int>(log.logLevel) << ": "
                    << log.message << std::endl;
    }
    return 0;
}