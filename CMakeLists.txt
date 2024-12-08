# Minimum CMake version required
cmake_minimum_required(VERSION 3.31)

# Project name and version
project(MyCppProject VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(include)

# Find external library (nlohmann_json from vcpkg)
find_package(nlohmann_json 3.2.0 REQUIRED)

# Add the executable (list all source files)
add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE nlohmann_json::nlohmann_json)