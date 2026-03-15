cmake_minimum_required(VERSION 3.16.0)
project(ToDo VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

find_package(wxWidgets CONFIG REQUIRED COMPONENTS core base)
find_package(cxxopts CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

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
)

# Создаём исполняемый файл
add_executable(ToDo ${SOURCES} ${HEADERS})

target_link_libraries(ToDo PRIVATE
    wx::core
    wx::base
    cxxopts::cxxopts
    nlohmann_json::nlohmann_json
)

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