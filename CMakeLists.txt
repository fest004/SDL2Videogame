
cmake_minimum_required(VERSION 3.10)

project(ZeldaGame)

# Add your source files here
set(SOURCES
    src/main.cpp
    src/zeldaEng.cpp
    include/zeldaEng.h
)

# Find required libraries
find_package(spdlog REQUIRED)
find_package(SDL2 REQUIRED)

# Build the Logger library
add_library(Logger SHARED
    src/logger/log.cpp
    include/logger/log.h
    include/logger/logger.h
)

# Link the Logger library to the ZeldaGame executable
add_executable(ZeldaGame ${SOURCES})
target_link_libraries(ZeldaGame PRIVATE spdlog::spdlog SDL2::SDL2 Logger)

# Create a separate directory for the executable file
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/Executables)

# Install the executable file to the build directory
install(TARGETS ZeldaGame DESTINATION ${EXECUTABLE_OUTPUT_PATH})

# Include directories for ZeldaEng.h and Log.h
target_include_directories(ZeldaGame PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Logger PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
