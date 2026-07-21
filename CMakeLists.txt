cmake_minimum_required(VERSION 3.16)

project(zGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(zGame src/main.cpp)

set_target_properties(zGame PROPERTIES SUFFIX ".html")

target_link_options(zGame PRIVATE
    "-sWASM=1"
    "-sALLOW_MEMORY_GROWTH=1"
)