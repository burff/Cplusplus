cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_FLAGS "-std=c++11 -O0 ${SSE_FLAGS} -msse4")
set (CMAKE_EXPORT_COMPILE_COMMANDS on)
project(TCP_IP VERSION 0.1.0 LANGUAGES C CXX)

include_directories(queue)
aux_source_directory(queue SRC_LIST)

add_executable(close_unlive close_unlive.cpp ${SRC_LIST})