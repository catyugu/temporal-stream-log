#include <iostream>
#include <source_location>
#include <LogBuffer.h>
#include <LogFormatter.h>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>



void printLogs(TemporalStreamLog::LogBuffer& logBuffer) {
    while(1){
        auto logs = logBuffer.drain();
        for (const auto& log : logs) {
            std::cout << log;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
void listenSocket(TemporalStreamLog::LogBuffer& logBuffer){
    char buffer[1024];
    auto socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd == -1) {
        throw std::runtime_error("Failed to create socket");
    }
    sockaddr_in server_addr{
        .sin_family=AF_INET,
        .sin_port=htons(8888),
        .sin_addr=INADDR_ANY,
        .sin_zero=0
    };
    if (bind(socket_fd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        close(socket_fd);
        throw std::runtime_error("Failed to bind socket");
    }
    while (true) {
        ssize_t recv_len = recvfrom(socket_fd, buffer, sizeof(buffer) - 1, 0, nullptr, nullptr);
        if (recv_len == -1) {
            std::cerr << "Failed to receive data" << std::endl;
            break;
        }
        std::string message(buffer, recv_len);
        auto now = std::chrono::high_resolution_clock::now();
        auto logLevel = TemporalStreamLog::LogLevel::INFO;
        TemporalStreamLog::LogEntry logEntry{
            .timestamp=now,
            .logLevel=logLevel,
            .message=message
        };
        logBuffer.addLog(logEntry);
    }

    close(socket_fd);
}

int main(){
    TemporalStreamLog::LogBuffer logBuffer(10);
    std::jthread t1(printLogs, std::ref(logBuffer));
    std::jthread t2(listenSocket, std::ref(logBuffer));
    t1.join();
    t2.join();

    return 0;
}