cmake_minimum_required(VERSION 3.26)
project(zappy_server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -Wpedantic")

include_directories(include)

set(SHARED_SRC
    src/main.c
    src/help.c
    src/parse_args.c
    src/connections.c
    src/listener.c
    src/manage_client.c
)

add_executable(zappy_server ${SHARED_SRC})
