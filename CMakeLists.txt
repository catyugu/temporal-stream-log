cmake_minimum_required(VERSION 3.28)
project(TemporalStreamLog)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
add_executable(server 
    src/main.cpp
    src/LogBuffer.cpp
    src/LogEntry.cpp
)
target_include_directories(server PUBLIC ${PROJECT_SOURCE_DIR}/include)