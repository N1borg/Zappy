# Zappy

Welcome to **Zappy**, the 2nd end-year Epitech project! Zappy is a networked game featuring a server coded in C, a GUI client in C++, and AI clients written in Python. This project showcases a comprehensive blend of network programming, game development, and artificial intelligence.

Click [here](https://github.com/N1borg/Zappy/tree/main/docs) for the technical subjects.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Architecture](#architecture)

## Overview

Zappy is a multiplayer game where players compete in a virtual world. The project is divided into three main components:

1. **Server (C)**: Handles game logic, player interactions, and networking.
2. **GUI (C++)**: Provides a graphical interface for players to interact with the game.
3. **AI Clients (Python)**: Autonomous agents that play the game.

## Features

- **Multiplayer Support**: Host games with multiple players.
- **Real-time Communication**: Fast and efficient networking for seamless gameplay.
- **Graphical Interface**: Intuitive and interactive GUI for players.
- **AI Integration**: Intelligent AI clients to play against or with human players.
- **Cross-platform**: Runs on various operating systems.

## Installation
### Prerequisites

- **C Compiler**: `gcc` or any compatible C compiler.
- **C++ Compiler**: `g++` or any compatible C++ compiler.
- **Python**: Version 3.x.
- **CMake**: For building the project.
- **Make**: Build automation tool.
- **Raylib**: Required for the GUI.

### Installing raylib on Fedora

To install raylib on Fedora, follow these steps:

1. Install the required libraries:
   ```bash
   sudo dnf install alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel libatomic
   ```

2. Install the raylib development package:
   ```bash
   sudo dnf install raylib-devel
   ```

3. (Optional) To install only the runtime library:
   ```bash
   sudo dnf install raylib
   ```

### Clone the Repository

```bash
git clone https://github.com/EpitechPromo2027/B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck.git zappy
cd zappy
```

### Build all
```bash
make
```

### Build the Server only

```bash
make zappy_server
```

option description
-p port port number
-x width width of the world
-y height height of the world
-n name1 name2 . . . name of the team
-c clientsNb number of authorized clients per team
-f freq reciprocal of time unit for execution of actions

### Build the GUI only

```bash
make zappy_gui
```

### Build the AI Client only

``` bash
make zappy_ai
```

## Usage
### Starting the Server

To start the server, run the following command:

```bash
./zappy_server -p [port] -x [width] -y [height] -n [name1] [name2] [...] -c [clientsNb] -f [freq]
```

| Option | Description |
| ------------- | ------------- |
| -p [port] | port number |
| -x [width] | width of the world |
| -y [height] | height of the world |
| -n [name1] [name2] [...] | name of the team |
| -c [clientsNb] | number of authorized clients per team |
| -f [freq] | reciprocal of time unit for execution of actions |

### Connecting the GUI

To connect the GUI to the server, run the following command:

```bash
./zappy_gui -p [port] -h [machine]
```

| Option | Description |
| ------------- | ------------- |
| -p [port] | port number |
| -h [machine] | name of the machine |

### Running the AI

To start an AI client, run the following command:

```bash
./zappy_ai -p [port] -n [name] -h [machine]
```

| Option | Description |
| ------------- | ------------- |
| -p [port] | port number |
| -n [name] | name of the team |
| -h [machine] | name of the machine; localhost by default |

## Architecture
### Server

The server is the core of Zappy. It manages:

 - Player connections and interactions
 - Game state and logic
 - Communication with the GUI and AI clients

### GUI

The GUI provides a visual representation of the game. It is built using C++ and Raylib, offering:

 - Real-time game visualization
 - Player controls and interactions
 - Network communication with the server

### AI Clients

The AI clients are autonomous agents written in Python. They connect to the server and perform actions based on the game state. The AI logic can be customized and extended for different strategies.

Thank you for checking out Zappy! We hope you enjoy playing and developing it as much as we did creating it.