cmake_minimum_required(VERSION 3.10)
project(StockTracker)

add_executable(stock_tracker main.cpp)

target_link_libraries(stock_tracker PRIVATE wininet)