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

## Init

- The player init their life, random starting direction, and position
- Init a socket to connect to the server
- First actions will depend on the chosen strategy

## Characters interactions

- They occupy the 1 tile they are on
- They go through each other, can stand on the same tile
- They look in a cardinal direction
- They can't see another player's direction
-> all these informations are important for the *look()* command

## Survival

- Players start with 1260 tick of life
- They regain 126 units by eating food
- If their life hits 0, they inform the server of their death
--> keep count of the life-ticks in the client-side, meaning the python program for AI

## Commands

The commands are a string sent to the server using the socket.
Implement all these commands in a robust way:

### Forward

### Incantation

- starts when the player informs the server
- lasts 300 for ticks
- Needs the correct amount of players and ressources *at minimum* to be valid
- every player is informed of a

## Game win condition

There is two ways to win:

### Survival

being the last team alive is a valid strategy, but extremely difficult to put in place.

### Elevating the team

Being the first team to get 6 players to **elevation 8** is the main win condition.

--> adapt strategy to get to either of these goals.
