cmake_minimum_required(VERSION 3.10)
project(MiniGit)

set(CMAKE_CXX_STANDARD 17)

include_directories(include third_party)

add_executable(MiniGit 
    src/main.cpp 
    third_party/sqlite3.c
)

find_package(Threads REQUIRED)
target_link_libraries(MiniGit Threads::Threads)

if(UNIX AND NOT APPLE)
    target_link_libraries(MiniGit dl)
endif()