cmake_minimum_required(VERSION 3.12)
project(pong)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories
include_directories(include/)

# Source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Find SFML
find_package(SFML COMPONENTS graphics window system REQUIRED)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES} src/main.cpp)

# Link against SFML
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

# Install executable
install(TARGETS ${PROJECT_NAME} DESTINATION bin)