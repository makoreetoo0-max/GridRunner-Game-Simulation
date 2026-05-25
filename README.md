GridRunner is a two-dimensional turn-based survival game written in C++. 
The player navigates a randomly generated grid world, managing limited energy while avoiding obstacles and traps,
collecting energy pickups, and racing to reach the goal before running out of moves.
The game world is built procedurally from command-line arguments — grid size, starting energy,
number of obstacles, traps, and pickups are all configurable. 
The player spawns at a random position in the bottom row and must reach a goal placed randomly in the top row,
moving one step at a time (W/A/S/D). Every move costs energy; traps cost extra; pickups restore it.
Features

Procedurally generated grid with randomised placement of all entities
Energy management system with pickups and traps
Immovable obstacle collision detection
Victory and defeat conditions
Modular architecture using a libGame module and NavigatorSpace namespace
Configurable via command-line arguments
