cmake_minimum_required(VERSION 3.14)
project(SearchEngineTests)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключение GTest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# Предотвращаем перезапись переменных компилятора
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Подключение nlohmann_json
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

# Создание тестового исполняемого файла
add_executable(${PROJECT_NAME}
        ../tests/sample_tests.cpp
        ../src/ConverterJSON.cpp
        ../src/InvertedIndex.cpp
        ../src/SearchServer.cpp
)

# Настройка include-путей
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Линковка библиотек
target_link_libraries(${PROJECT_NAME}
        nlohmann_json::nlohmann_json
        GTest::gtest_main
        GTest::gmock_main
)

# Включаем тестирование
enable_testing()

# Отладочная информация
message(STATUS "Project include path: ${INCLUDE_DIR}")
message(STATUS "Nlohmann include path: ${NLOHMANN_DIR}")
message(STATUS "GTest include path: ${GTEST_DIR}")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../config.json
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../resources
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})