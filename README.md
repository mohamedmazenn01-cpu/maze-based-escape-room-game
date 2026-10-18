# Maze-Based Escape Room Game

A console-based escape room game written in C++. The player explores a small maze, collects a brass key, and unlocks the dungeon door to escape.

## Features

- Directional movement between interconnected rooms
- Singly linked list for the player's inventory
- Pointer-based room network with north, south, east, and west connections
- Locked-room logic with a required key
- Dynamic memory allocation and cleanup
- Clear command-line gameplay loop

## Data Structures

- `ItemNode`: a node in the inventory linked list
- `Inventory`: manages collected items using a singly linked list
- `Room`: represents each room and stores pointers to connected rooms
- `std::vector<Room*>`: tracks dynamically allocated rooms for cleanup

## How to Build

You need a C++ compiler with C++17 support.

### Linux or macOS

```bash
g++ -std=c++17 main.cpp -o escape-room
./escape-room
```

### Windows

```powershell
g++ -std=c++17 main.cpp -o escape-room.exe
.\escape-room.exe
```

## Commands

| Command | Action |
| --- | --- |
| `north` | Move north |
| `south` | Move south |
| `east` | Move east |
| `west` | Move west |
| `pick` | Collect the item in the current room |
| `exit` | End the game |

## Objective

1. Start in the Foyer.
2. Travel east to the Armory.
3. Pick up the Brass Key.
4. Return to the Foyer and move north to the Library.
5. Move east and use the key to unlock the Dungeon Door.

## Project Structure

```text
maze-based-escape-room-game/
├── main.cpp
└── README.md
```

## Skills Demonstrated

C++, data structures, linked lists, pointers, dynamic memory, graph-style navigation, object-oriented programming, and resource cleanup.
