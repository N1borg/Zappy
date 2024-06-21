cmake_minimum_required(VERSION 3.26)
project(zappy_gui)

# Try to find an existing installation of Raylib
find_package(raylib QUIET)

if (NOT raylib_FOUND)
    message(STATUS "Raylib not found, downloading and building Raylib from source.")

    include(ExternalProject)

    # Define the Raylib installation directory
    set(RAYLIB_INSTALL_DIR ${CMAKE_BINARY_DIR}/raylib)

    # Download and build Raylib
    ExternalProject_Add(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${RAYLIB_INSTALL_DIR}
        UPDATE_COMMAND ""
        PATCH_COMMAND ""
        TEST_COMMAND ""
        INSTALL_COMMAND make install
        LOG_DOWNLOAD ON
        LOG_CONFIGURE ON
        LOG_BUILD ON
        LOG_INSTALL ON
    )

    # Add Raylib to the include path and link path
    include_directories(${RAYLIB_INSTALL_DIR}/include)
    link_directories(${RAYLIB_INSTALL_DIR}/lib)

    # Specify the path to the Raylib library explicitly
    set(RAYLIB_LIB ${RAYLIB_INSTALL_DIR}/lib/libraylib.a)
else()
    message(STATUS "Raylib found: ${raylib_DIR}")

    # Add Raylib to the include path and link path
    include_directories(${raylib_INCLUDE_DIRS})
    link_directories(${raylib_LIBRARY_DIRS})

    # Use the found Raylib library
    set(RAYLIB_LIB ${raylib_LIBRARIES})
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wformat-security -I ./include/")

include_directories(include)

set(SHARED_SRC
    src/Main.cpp
    src/Help.cpp
    src/Socket.cpp
    src/Window.cpp
    src/Map.cpp
    src/AModel.cpp
    src/Player.cpp
    src/Parser/ParseArguments.cpp
    src/Parser/ParseCommands.cpp
    src/Collectables/Egg.cpp
    src/Collectables/Food.cpp
    src/Collectables/Linemate.cpp
    src/Collectables/Deraumere.cpp
    src/Collectables/Sibur.cpp
    src/Collectables/Mendiane.cpp
    src/Collectables/Phiras.cpp
    src/Collectables/Thystame.cpp
    src/Island.cpp
    src/Commands/Commands.cpp
)

add_executable(zappy_gui ${SHARED_SRC})

# Link Raylib
target_link_libraries(zappy_gui ${RAYLIB_LIB} GL m pthread dl rt X11)

# Ensure Raylib is built before your project
if (NOT raylib_FOUND)
    add_dependencies(zappy_gui raylib)
endif()
