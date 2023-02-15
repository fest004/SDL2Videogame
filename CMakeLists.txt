
cmake_minimum_required(VERSION 3.10)

project(ZeldaGame)

# Set C++ standard to 11
set(CMAKE_CXX_STANDARD 11)

# Add your source files here
set(SOURCES
    src/main.cpp
    src/zeldaEng.cpp
    include/zeldaEng.h
)

# Find required libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(spdlog REQUIRED)

# Build the Logger library
add_library(Logger SHARED
    src/log.cpp
    include/log.h
    include/logger.h
)

# Link the Logger library to the ZeldaGame executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog Logger ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})




#And the path to my SDL2 and SDL2_image libraries are: "/usr/lib/x86_64-linux-gnu"
