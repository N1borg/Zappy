cmake_minimum_required(VERSION 3.26)
project(zappy_gui)

# Set C++ standard and compile flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wformat-security -Wunused-function")

# Add include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Source files
set(SHARED_SRC
    src/Main.cpp
    src/Socket.cpp
    src/Window.cpp
    src/Map.cpp
    src/Team.cpp
    src/Models/AModel.cpp
    src/Models/Player.cpp
    src/Models/Island.cpp
    src/Models/Grass.cpp
    src/Models/Collectables/Egg.cpp
    src/Models/Collectables/Food.cpp
    src/Models/Collectables/Linemate.cpp
    src/Models/Collectables/Deraumere.cpp
    src/Models/Collectables/Sibur.cpp
    src/Models/Collectables/Mendiane.cpp
    src/Models/Collectables/Phiras.cpp
    src/Models/Collectables/Thystame.cpp
    src/Parser/ParseArguments.cpp
    src/Parser/ParseCommands.cpp
    src/Commands/Commands.cpp
)

find_package(raylib QUIET)
if (NOT raylib_FOUND)
    message(STATUS "Raylib not found, downloading and building Raylib from source.")
    include(ExternalProject)
    ExternalProject_Add(raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        PREFIX ${CMAKE_BINARY_DIR}/raylib
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/raylib/install
        BUILD_COMMAND ${CMAKE_COMMAND} --build . > /dev/null 2>&1
        INSTALL_COMMAND ${CMAKE_COMMAND} --install . > /dev/null 2>&1
        LOG_DOWNLOAD ON
    )
    set(raylib_LIBRARIES ${CMAKE_BINARY_DIR}/raylib/install/lib/libraylib.a)
    include_directories(${CMAKE_BINARY_DIR}/raylib/install/include)
    link_directories(${CMAKE_BINARY_DIR}/raylib/install/lib)
endif()

# Add the executable and link libraries
add_executable(zappy_gui ${SHARED_SRC})
target_link_libraries(zappy_gui ${raylib_LIBRARIES} GL m pthread dl rt X11)

# Ensure Raylib is built before your project
if (NOT raylib_FOUND)
    add_dependencies(zappy_gui raylib)
endif()
