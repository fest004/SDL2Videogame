cmake_minimum_required(VERSION 3.25.1)

project(ZELDA)

# set(CMAKE_CXX_COMPILER "clang++")

add_executable(${PROJECT_NAME} main.cpp ZeldaEng.cpp Logger/Log.cpp)

find_package(SDL2 REQUIRED)

add_subdirectory(Logger)

target_link_libraries(${PROJECT_NAME} Logger SDL2)
