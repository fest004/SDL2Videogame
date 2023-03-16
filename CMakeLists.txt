
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

# Include GLM headers
include_directories(libs/glm)

# Find required libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(spdlog REQUIRED)

# Link directories
link_directories(${CMAKE_SOURCE_DIR}/libs)

# Build the Logger library
add_library(Logger SHARED
    src/log.cpp
    include/log.h
    include/logger.h
)

# Link the Logger library to the ZeldaGame executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image spdlog::spdlog Logger ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} Box2D)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# Set the path to the Box2D library
link_directories(${CMAKE_SOURCE_DIR}/libs)

# Build the Box2D library
add_library(Box2D STATIC IMPORTED)
set_target_properties(Box2D PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/box2d/libbox2d.a)

# Link the Box2D library to the ZeldaGame executable
target_link_libraries(${PROJECT_NAME} PRIVATE Box2D)






#
# cmake_minimum_required(VERSION 3.10)
#
# project(ZeldaGame)
#
# # Set C++ standard to 11
# set(CMAKE_CXX_STANDARD 11)
#
# # Add your source files here
# set(SOURCES
#     src/main.cpp
#     src/zeldaEng.cpp
#     include/zeldaEng.h
# )
#
# # Find required libraries
# find_package(SDL2 REQUIRED)
# find_package(SDL2_image REQUIRED)
# find_package(spdlog REQUIRED)
# find_package(glm REQUIRED)
#
# # Link directories
# link_directories(${CMAKE_SOURCE_DIR}/libs)
#
# # Build the Logger library
# add_library(Logger SHARED
#     src/log.cpp
#     include/log.h
#     include/logger.h
# )
#
# # Link the Logger library to the ZeldaGame executable
# add_executable(${PROJECT_NAME} ${SOURCES})
# target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image)
# target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog Logger ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} Box2D)
# target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
#
# # Set the path to the Box2D library
# link_directories(${CMAKE_SOURCE_DIR}/libs)
#
# # Build the Box2D library
# add_library(Box2D STATIC IMPORTED)
# set_target_properties(Box2D PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/libbox2d.a)
#
# # Link the Box2D library to the ZeldaGame executable
# target_link_libraries(${PROJECT_NAME} PRIVATE Box2D)
#





