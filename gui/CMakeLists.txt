cmake_minimum_required(VERSION 3.26)
project(zappy_gui)

# Set C++ standard and compile flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wformat-security")

# Add include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Source files
set(SHARED_SRC
    src/Main.cpp
    src/Help.cpp
    src/Socket.cpp
    src/Window.cpp
    src/Map.cpp
    src/AModel.cpp
    src/Player.cpp
    src/Island.cpp
    src/Grass.cpp
    src/Team.cpp
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
    src/Commands/Commands.cpp
)

# Function to fetch Raylib 5.0
function(fetch_raylib)
    message(STATUS "Downloading and building Raylib 5.0 from source.")
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
    )
    FetchContent_GetProperties(raylib)
    if(NOT raylib_POPULATED)
        FetchContent_Populate(raylib)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endfunction()

# Find or fetch Raylib 5.0
find_package(raylib 5.0 QUIET)
if (NOT raylib_FOUND)
    fetch_raylib()
    set(raylib_LIBRARIES raylib)
endif()

# Add the executable and link libraries
add_executable(zappy_gui ${SHARED_SRC})
target_link_libraries(zappy_gui ${raylib_LIBRARIES} GL m pthread dl rt X11)

# Ensure Raylib is built before your project
if (NOT raylib_FOUND)
    add_dependencies(zappy_gui raylib)
endif()
