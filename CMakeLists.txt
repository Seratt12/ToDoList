cmake_minimum_required(VERSION 3.16.0)
project(ToDo VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ToDo
    src/main.cpp
    src/stdafx.cpp
    src/todo/Task.cpp
)

target_include_directories(ToDo PRIVATE include)
target_precompile_headers(ToDo PRIVATE include/stdafx.h)

if(MSVC)
    target_compile_options(ToDo PRIVATE /W4 /permissive- /WX)
else()
    target_compile_options(ToDo PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()