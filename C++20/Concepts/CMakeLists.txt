cmake_minimum_required(VERSION 3.5)

project(Concepts LANGUAGES CXX)
#====================================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#====================================================================
# Ищим хидеры
file(GLOB_RECURSE BIN_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
)
#====================================================================
# Ищим сорцы
file(GLOB_RECURSE BIN_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
#====================================================================
# Формируем список подключаемых папок
set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/src     # Подключаем корневую папку исходников
    )
#====================================================================
# Создаём бинарь
add_executable(${PROJECT_NAME} ${BIN_HEADERS} ${BIN_SOURCES})
# Подключаем папки с хидерами
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
#====================================================================
