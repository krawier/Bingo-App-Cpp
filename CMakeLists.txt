cmake_minimum_required(VERSION 3.20)
project(BingoApp)

set(CMAKE_CXX_STANDARD 17)


include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG master
)
FetchContent_MakeAvailable(raylib)


add_executable(BingoApp main.cpp
        main.cpp
        CBingoCell.cpp
        CBingoCell.h)
target_link_libraries(BingoApp PRIVATE raylib)