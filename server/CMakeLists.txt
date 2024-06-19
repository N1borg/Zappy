cmake_minimum_required(VERSION 3.26)
project(zappy_server)

set(CMAKE_C_STANDARD 17)

set(CMAKE_C_FLAGS "-W -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wformat-security -I ./include/ -g")

include_directories(include)

set(SHARED_SRC
    src/main.c
    src/help.c
    src/parse_args.c
    src/destroy.c
    src/server_init.c
    src/connections.c
    src/init_listener.c
    src/generate_resources.c
    src/manage_client.c
    src/manage_team.c
    src/handle_command.c
    src/basic_functions.c
    src/coordinates.c
    src/display_tile.c
    src/add_egg.c
    src/remove_egg.c
    src/command_queue.c
    src/player_commands/success_response.c
    src/player_commands/broadcast.c
    src/player_commands/eject.c
    src/player_commands/fork.c
    src/player_commands/incantation.c
    src/player_commands/inventory.c
    src/player_commands/look.c
    src/player_commands/look_buffer_len.c
    src/player_commands/move.c
    src/player_commands/set_object.c
    src/player_commands/take_object.c
    src/player_commands/rotate.c
    src/player_commands/team_slots.c
    src/graphic_commands/bct.c
    src/graphic_commands/ebo.c
    src/graphic_commands/edi.c
    src/graphic_commands/enw.c
    src/graphic_commands/mct.c
    src/graphic_commands/msz.c
    src/graphic_commands/pbc.c
    src/graphic_commands/pdi.c
    src/graphic_commands/pdr.c
    src/graphic_commands/pex.c
    src/graphic_commands/pfk.c
    src/graphic_commands/pgt.c
    src/graphic_commands/pic.c
    src/graphic_commands/pie.c
    src/graphic_commands/pin.c
    src/graphic_commands/plv.c
    src/graphic_commands/pnw.c
    src/graphic_commands/ppo.c
    src/graphic_commands/sbp.c
    src/graphic_commands/seg.c
    src/graphic_commands/sgt.c
    src/graphic_commands/smg.c
    src/graphic_commands/sst.c
    src/graphic_commands/suc.c
    src/graphic_commands/tna.c
)

add_executable(zappy_server ${SHARED_SRC})
