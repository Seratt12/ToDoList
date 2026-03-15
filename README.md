## To-do list

Написан на C++ и использует CMake для сборки проекта.
Обычный планировщик задач. Консольный интерфейс.

Для установки зависимостей используется vcpkg
Из сторонних библиотек сейчас используется:

1. [nlohmann/json](https://github.com/nlohmann/json)
2. [cxxopts](https://github.com/jarro2783/cxxopts)
3. [wxWidgets](https://github.com/wxWidgets/wxWidgets)

## Собрать проект и запустить:

Из папки build: cmake .. && cmake --build .
