cmake_minimum_required(VERSION 3.10)
project(StockTracker)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)

include_directories(include)

add_executable(stock_tracker
    src/main.cpp
    src/HttpClient.cpp
)

target_link_libraries(stock_tracker PRIVATE CURL::libcurl)