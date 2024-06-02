cmake_minimum_required(VERSION 3.26)
project(zappy_server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -Wpedantic -g")

include_directories(include)

set(SHARED_SRC
    src/main.c
    src/help.c
    src/parse_args.c
    src/server_init.c
    src/connections.c
    src/listener.c
    src/manage_client.c
    src/handle_command.c
    src/basic_functions.c
    src/commands/broadcast.c
    src/commands/eject.c
    src/commands/fork.c
    src/commands/inventory.c
    src/commands/look.c
    src/commands/move.c
    src/commands/object_interaction.c
    src/commands/rotate.c

)

add_executable(zappy_server ${SHARED_SRC})
