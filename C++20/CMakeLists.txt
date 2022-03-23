cmake_minimum_required(VERSION 3.5)

project(C++20 LANGUAGES CXX)
#====================================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#====================================================================
add_subdirectory(Concepts)  # Собираем концепты
add_subdirectory(Modules)   # Собираем модули
