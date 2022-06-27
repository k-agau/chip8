cmake_minimum_required(VERSION 3.18)
project(chip8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror -Wextra -pedantic -pedantic-errors")

# Bring together the sub-libraries
include_directories("./include")
add_library(Core STATIC)
add_subdirectory("./src")

# Generate binaries in the bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Build GTest automated testing suite
# add_executable(testing)
# add_subdirectory(./tests)
# add_dependencies(testing gtest Core)
# target_link_libraries(testing gtest ${CMAKE_THREAD_LIBS_INIT})
# target_link_libraries(testing Core)

# Build application
add_executable(chip8 ./src/main.cpp)
add_dependencies(chip8 Core)
target_link_libraries(chip8 Core)