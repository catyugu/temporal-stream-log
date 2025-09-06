#include <iostream>
#include <source_location>
#include <LogBuffer.h>
#include <LogFormatter.h>
#include <LogWriter.h>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>



void printLogs(TemporalStreamLog::LogBuffer& logBuffer) {
    TemporalStreamLog::LogWriter logWriter;
    while(1){
        auto logs = logBuffer.drain();
        for (const auto& log : logs) {
            std::cout << log;
        }
        if (!logs.empty()){
            logWriter.write(logs);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
void listenUDP(TemporalStreamLog::LogBuffer& logBuffer){
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
        auto now = std::chrono::system_clock::now();
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
void listenTCP(TemporalStreamLog::LogBuffer& logBuffer){
    char buffer[1024];
    auto socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        throw std::runtime_error("Failed to create socket");
    }
    sockaddr_in server_addr{
        .sin_family=AF_INET,
        .sin_port=htons(9999),
        .sin_addr=INADDR_ANY,
        .sin_zero=0
    };
    if (bind(socket_fd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        close(socket_fd);
        throw std::runtime_error("Failed to bind socket");
    }
    if (listen(socket_fd, 5) == -1) {
        close(socket_fd);
        throw std::runtime_error("Failed to listen on socket");
    }
    while (true) {
        auto client_fd = accept(socket_fd, nullptr, nullptr);
        if (client_fd == -1) {
            std::cerr << "Failed to accept connection" << std::endl;
            continue;
        }
        while (true) {
            ssize_t recv_len = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
            if (recv_len == -1) {
                std::cerr << "Failed to receive data" << std::endl;
                close(client_fd);
                break;
            }
            std::string message(buffer, recv_len);
            auto now = std::chrono::system_clock::now();
            auto logLevel = TemporalStreamLog::LogLevel::INFO;
            TemporalStreamLog::LogEntry logEntry{
                .timestamp=now,
                .logLevel=logLevel,
                .message=message
            };
            logBuffer.addLog(logEntry);
            send(client_fd, "OK\n", 3, 0);
        }
    }
    close(socket_fd);
}
int main(){
    TemporalStreamLog::LogBuffer logBuffer(10);
    std::jthread t1(printLogs, std::ref(logBuffer));
    std::jthread t2(listenUDP, std::ref(logBuffer));
    std::jthread t3(listenTCP, std::ref(logBuffer));
    t1.join();
    t2.join();
    t3.join();

    return 0;
}