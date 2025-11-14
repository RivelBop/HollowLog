# Later versions of CMake invoked on CML will act as if they were CMake 3.23
cmake_minimum_required(VERSION 3.23)

# What follows this command is a part of the HollowLog project
# Perform checks to ensure the environment is suitable for building software
project(HollowLog)

# Set language to C++17
set(CMAKE_CXX_STANDARD 17)

# This creates a "virtual" target
# No .cpp files are listed because it's header-only
add_library(HollowLog INTERFACE)

# Tell the library where its headers are
target_include_directories(HollowLog
    INTERFACE ${PROJECT_SOURCE_DIR}/include
)
