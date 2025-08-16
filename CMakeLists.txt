cmake_minimum_required(VERSION 3.16.0)
project(ToDo VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Собираем список исходников
set(SOURCES
    src/main.cpp
    src/stdafx.cpp
    src/Localization.cpp
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
    include/Localization.h
    include/nlohmann/json.hpp
    include/cxxopts/cxxopts.hpp
)

# Создаём исполняемый файл
add_executable(ToDo ${SOURCES} ${HEADERS})

# Абсолютный путь до папки data
set(DATA_DIR_PATH "${CMAKE_CURRENT_SOURCE_DIR}/data")

# Передаём в код как макрос
target_compile_definitions(ToDo PRIVATE
    DATA_DIR_PATH=\"${DATA_DIR_PATH}\"
)

target_include_directories(ToDo PRIVATE include)
target_precompile_headers(ToDo PRIVATE include/stdafx.h)

if(MSVC)
    target_compile_options(ToDo PRIVATE /W4 /permissive- /WX)
    target_compile_options(ToDo PRIVATE
        "$<$<CXX_COMPILER_ID:MSVC>:/utf-8;>")
else()
    target_compile_options(ToDo PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()