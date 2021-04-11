cmake_minimum_required(VERSION 3.19)
project(MonKeys C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(inc)

add_executable(MonKeys
        inc/client.hpp)
