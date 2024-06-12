cmake_minimum_required(VERSION 3.26)
project(zappy_gui)

include(ExternalProject)

# Define the Raylib installation directory
set(RAYLIB_INSTALL_DIR ${CMAKE_BINARY_DIR}/raylib)

# Download and build Raylib
ExternalProject_Add(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0  # Replace with the desired version
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${RAYLIB_INSTALL_DIR}
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    TEST_COMMAND ""
    INSTALL_COMMAND make install
    LOG_DOWNLOAD ON   # Log the download process
    LOG_CONFIGURE ON  # Log the configure process
    LOG_BUILD ON      # Log the build process
    LOG_INSTALL ON    # Log the install process
)

# Add Raylib to the include path and link path
include_directories(${RAYLIB_INSTALL_DIR}/include)
link_directories(${RAYLIB_INSTALL_DIR}/lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -Wpedantic")

include_directories(include)

set(SHARED_SRC
    src/main.cpp
    src/help.cpp
    src/Parser.cpp
    src/Socket.cpp
    src/Window.cpp
    src/Camera.cpp
)

add_executable(zappy_gui ${SHARED_SRC})

# Ensure Raylib is built before your project
add_dependencies(zappy_gui raylib)

# Find the Raylib library files
find_library(RAYLIB_LIB NAMES raylib HINTS ${RAYLIB_INSTALL_DIR}/lib)

# Link Raylib
target_link_libraries(zappy_gui ${RAYLIB_LIB} m)
