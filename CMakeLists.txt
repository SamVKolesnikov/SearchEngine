cmake_minimum_required(VERSION 3.27)
project("SearchEngine" VERSION 1.0)

# Настройка стандарта C++ для всего проекта
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включение поддиректорий
add_subdirectory(src)
add_subdirectory(tests)