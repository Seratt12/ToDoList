cmake_minimum_required(VERSION 3.16.0)
project(ToDo VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Собираем список исходников
set(SOURCES
    src/main.cpp
    src/stdafx.cpp
    src/todo/Task.cpp
    src/todo/FileStorageJSON.cpp
    src/todo/TaskManager.cpp
)

# Собираем список заголовков
set(HEADERS
    include/stdafx.h
    include/Task.h
    include/FileStorage.h
    include/TaskManager.h
    include/nlohmann/json.hpp
)

# Копировать папку data в build/
file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})

# Создаём исполняемый файл
add_executable(ToDo ${SOURCES} ${HEADERS})

target_include_directories(ToDo PRIVATE include)
target_precompile_headers(ToDo PRIVATE include/stdafx.h)

if(MSVC)
    target_compile_options(ToDo PRIVATE /W4 /permissive- /WX)
else()
    target_compile_options(ToDo PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
