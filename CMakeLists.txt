cmake_minimum_required(VERSION 3.16)

project(zGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(zGame src/main.cpp)

include(FetchContent)

if(EXISTS "${CMAKE_SOURCE_DIR}/vendor/raylib/CMakeLists.txt")
    add_subdirectory(vendor/raylib)
else()
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 6.0
    )

    FetchContent_MakeAvailable(raylib)
endif()

target_link_libraries(zGame PRIVATE raylib)

set_target_properties(zGame PROPERTIES SUFFIX ".html")

target_link_options(zGame PRIVATE
    "-sWASM=1"
    "-sALLOW_MEMORY_GROWTH=1"
)