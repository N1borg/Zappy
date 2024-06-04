# Server

## Init

### Map

- use args **width** & **height**
-> gen circular map

### Ressources

7 ressources and density = constant defined in doc
-> density * width * height = nbr of ressources
--> spread evenly on map
--> minimum 1 of each on floor
---> gen ressources on tiles evenly

### Spawns

randomly chosen on any tile of the map
number defined by arg **clientNB**
Open a new socket for every spawn, ready to connect to any player process trying to access the game

I recommand using a double array of structures to define the tiles positions as well as their content

## Time

- Time is defined by the arg **freq**
- units of time last for *1 / freq*, meaning freq of 1 make one tick last 1 second
- Default value is 100

A clock should be put in place according to the frequency, using the time library.
When a player hasn't queued any command for the server, the player should be ignored and the game must go on.

## Player Commands

The following commands have to be implemented for players:

### Forward

- move the player up a tile
- cannot fail
- return "ok"

### Right (7 ticks)

- change the player direction clockwise (N -> E -> S -> W)
- cannot fail
- return "ok"

### Left (7 ticks)

- change the player direction counterclockwise (N -> W -> S -> E)
- cannot fail
- return "ok"

### Look (7 ticks)

- check the player's level
- cannot fail
- check in the direction for objects, in a a cone of height [player_level], with lines of size [1 + 2 * height]
-> example for a level 2 look in north direction:
4 5 6 7 8
  1 2 3
    0
- returns a list between of comma-separated tiles, containing space-separated objects, in any order
- The player itself counts as a valid entity and will always be on the first tile
-> [tile0,tile1,tile2,...]
--> example for a level 2 look: [player,,,food player,deraumere thystame,]

### Inventory (1 tick)

- returns the player's inventory, already saved on the server-side
-> format: [linemate n,deraumere n,sibur n,mendiane n,phiras n,thystame n] with n the nbr of objects


### Broadcast text (7 ticks)

### Fork (42 ticks)

### Eject (7 ticks)

### Death (not a command name)

### Take object (7 ticks)

### Set object (7 ticks)

### Incantation (300 ticks)

- starts when the player informs the server
- Needs the correct amount of players and ressources *at minimum* to be valid
- perform a check as soon as the command is received
-> OK: return "Elevation underway\nCurrent level: {player_level}"
-> KO: return "/ko"
- perform a check after 300 units (not sure if this is server-side)
-> OK: return "Level up"
-> KO: return "/ko"
- inform all clients that the process started with coordinates (unsure)

# GUI

# AI

The AI is free to put into place in any way, but should at least follow the game rules.
The strategy is yet to be defined, and not a priority.
The first focus for AI is to communicate with the server.
The second focus is to use the commands to get a basic decision tree.
The last focus is to make a decision tree to optimize strategy and winning chances.

### Short overview

AI do:
- Occupy 1 tile (several AI can occupy the same tile)
- Look in a cardinal direction (can't be seen by other AI)
- Move
- Turn left or right
- Look for and collect stones
- Eject other players (push a tile away in the direction of viewing)
- Feed themselves (consume stones)
- Have a FOV (Field Of Vision) which depends on their level
- Have an inventory
- Broadcast messages
- Create eggs (new sockets for new AI on the same team)
- Initialize incantation

## Connection
1. Client(AI) opens a socket on server's port
2. Server and client communicate the following way:<br>
<ins>server</ins>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<ins>client</ins><br>
    **WELCOME**\n **-->**<br>
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
   **<-- TEAM-NAME**\n<br>
    **CLIENT-NUM**\n **-->**<br>
    **X Y**\n **-->**

When **a player connects**:

- select a random egg (socket) from available ones on the same team
- start a new player with a random direction

[//]: # (## Init)

[//]: # ()
[//]: # (- The player init their life, random starting direction, and position)

[//]: # (- Init a socket to connect to the server)

[//]: # (- First actions will depend on the chosen strategy)

[//]: # (## Characters interactions)

[//]: # ()
[//]: # (- They occupy the 1 tile they are on)

[//]: # (- They go through each other, can stand on the same tile)

[//]: # (- They look in a cardinal direction)

[//]: # (- They can't see another player's direction)

[//]: # (-> all these informations are important for the *look&#40;&#41;* command)

## Survival

- Players start with 1260 tick (seconds) or 10 units of life
- They regain 126 units by eating food
- If their life hits 0, they are dead (server informs them of their death)
- Life ticks are counted in client (AI)

## Commands

The commands are a string sent to the server using the socket. The server sends a response as well.

| **Command**    | **Time limit** |                   **Response**                    | **Action**                      |
|:--------------:|:--------------:|:-------------------------------------------------:|:-------------------------------:|
| Forward        | 7/f            |                        ok                         | move 1 tile forward             |
| Right          | 7/f            |                        ok                         | turn 90° right                  |
| Left           | 7/f            |                        ok                         | turn 90° left                   |
| Look           | 7/f            |                [tile1, tile2, ...]                | look around                     |
| Inventory      | 1/f            |            [linemate n, sibur n, ...]             | inventory                       |
| Broadcast text | 7/f            |                        ok                         | broadcast a message             |
| Connect_nbr    | -              |                       value                       | num of unused team spots        |
| Fork           | 42/f           |                        ok                         | create an egg (socket)          |
| Eject          | 7/f            |                       ok/ko                       | push other players on same tile |
| -              | -              |                       dead                        | dead                            |
| Take object    | 7/f            |                       ok/ko                       | take object                     |
| Set object     | 7/f            |                       ok/ko                       | set down object                 |
| Incantation    | 300/f          | Elevation underway:\n<br>Current level: k\n<br>/ko | start incantation ritual        |


### Inventory

An example of an inventory:<br>
<i>[food 345, sibur 3, phiras 5, ... deraumere 0]</i>
### Eject
- Push other player 1 case forward (in the <b>pusher's</b> perspective, not the pushed)
- If there are any eggs on a tile where a player calls Eject, eggs get destroyed

### Incantation

A level upgrade called by client (AI).

Short facts:
- Starts when a player informs the server
- Lasts for 300 ticks
- Every player is frozen during the procedure (can't do any other actions)
- Needs the correct amount of players and ressources *at minimum* to be valid
- Verification of the conditions for incantation is done at the beginning and at the end of it
- If incantation is successful, stones are removed frm the ground

Table of elements needed to proceed with the ritual:

| elevation | nb players | linemate | deraumere | sibur | mendiane | phiras | thystame |
|:---------:|:----------:|:--------:|:---------:|:-----:|:--------:|:------:|:--------:|
| 1->2      | 1          | 1        | 0         | 0     | 0        | 0      | 0        |
| 2->3      | 2          | 1        | 1         | 1     | 0        | 0      | 0        |
| 3->4      | 2          | 2        | 0         | 1     | 0        | 2      | 0        |
| 4->5      | 4          | 1        | 1         | 2     | 0        | 1      | 0        |
| 5->6      | 4          | 1        | 2         | 1     | 3        | 0      | 0        |
| 6->7      | 6          | 1        | 2         | 3     | 0        | 1      | 0        |
| 7->8      | 6          | 2        | 2         | 2     | 2        | 2      | 1        |


## Game win condition--> keep count of the life-ticks in the client-side, meaning the python program for AI

There is two ways to win:
- A member of the team reaches level 8
- No other teams are left

### Survival

being the last team alive is a valid strategy, but extremely difficult to put in place.

### Elevating the team

Being the first team to get 6 players to **elevation 8** is the main win condition.

--> adapt strategy to get to either of these goals.
