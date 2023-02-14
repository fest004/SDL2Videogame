
cmake_minimum_required(VERSION 3.10)

project(ZeldaGame)

# Add your source files here
set(SOURCES
    main.cpp
    ZeldaEng.cpp
    ZeldaEng.h
)

# Find required libraries
find_package(spdlog REQUIRED)
find_package(SDL2 REQUIRED)

# Build the Logger library
add_library(Logger SHARED
    Logger/Log.cpp
    Logger/Log.h
    Logger/logger.h
)

# Link the Logger library to the ZeldaGame executable
add_executable(ZeldaGame ${SOURCES})
target_link_libraries(ZeldaGame PRIVATE spdlog::spdlog SDL2::SDL2 Logger)
