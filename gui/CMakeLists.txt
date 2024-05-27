cmake_minimum_required(VERSION 3.26)
project(zappy_gui)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -Wpedantic -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network")

include_directories(include)

set(SHARED_SRC
    src/main.cpp
    src/help.cpp
    src/Parser.cpp
    src/Socket.cpp
)

add_executable(zappy_gui ${SHARED_SRC})
