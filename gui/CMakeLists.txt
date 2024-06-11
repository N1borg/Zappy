cmake_minimum_required(VERSION 3.26)
project(zappy_gui)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -Wpedantic -lraylib -lm")

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
