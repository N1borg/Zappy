cmake_minimum_required(VERSION 3.26)
project(zappy_server)

set(CMAKE_C_STANDARD 17)

set(CMAKE_C_FLAGS "-W -Wall -Wextra -Wpedantic -g")

include_directories(include)

set(SHARED_SRC
    src/main.c
    src/help.c
    src/parse_args.c
    src/destroy.c
    src/server_init.c
    src/connections.c
    src/listener.c
    src/manage_client.c
    src/manage_team.c
    src/handle_command.c
    src/basic_functions.c
    src/coordinates.c
    src/display_tile.c
    src/player_commands/broadcast.c
    src/player_commands/eject.c
    src/player_commands/fork.c
    src/player_commands/incantation.c
    src/player_commands/inventory.c
    src/player_commands/look.c
    src/player_commands/move.c
    src/player_commands/object_interaction.c
    src/player_commands/rotate.c
    src/player_commands/team_slots.c
    src/graphic_commands/msz.c
    src/graphic_commands/bct.c
    src/graphic_commands/mct.c
)

add_executable(zappy_server ${SHARED_SRC})
