cmake_minimum_required(VERSION 3.27)
project("SearchEngine_exe" VERSION 1.0)

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

# Создаем основную библиотеку из исходников
add_executable (${PROJECT_NAME}
                                                    main.cpp
        ../include/converterjson.h                  ConverterJSON.cpp
        ../include/invertedindex.h                  InvertedIndex.cpp
        ../include/searchserver.h                   SearchServer.cpp
)

# Публичные include-пути (для других целей)
target_include_directories(${PROJECT_NAME} PRIVATE ../include)

# Линковка библиотек (если нужны в src)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../config.json
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../resources
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})