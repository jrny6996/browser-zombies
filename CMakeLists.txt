cmake_minimum_required(VERSION 3.16)

project(zGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(zGame src/main.cpp)

include(FetchContent)

# raylib
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

# raygui (header-only)
if(EXISTS "${CMAKE_SOURCE_DIR}/vendor/raygui/src/raygui.h")
    target_include_directories(zGame PRIVATE
        "${CMAKE_SOURCE_DIR}/vendor/raygui/src"
    )
else()
    FetchContent_Declare(
        raygui
        GIT_REPOSITORY https://github.com/raysan5/raygui.git
        GIT_TAG 5.0
    )
    FetchContent_MakeAvailable(raygui)

    target_include_directories(zGame PRIVATE
        "${raygui_SOURCE_DIR}/src"
    )
endif()

target_link_libraries(zGame PRIVATE raylib)

set_target_properties(zGame PROPERTIES SUFFIX ".html")

target_link_options(zGame PRIVATE
    "-sWASM=1"
    "-sALLOW_MEMORY_GROWTH=1"
    "--shell-file"
    "../web/html/game.html"
)