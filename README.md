# RPG_GAMES

**RPG_GAMES** is an attempt to create a game using SFML and C++.

## Project Description

This project is a basic RPG game structure using the SFML library for graphics, window input, and system tasks. The game includes:
- Character control
- Chunk generation and rendering
- Inventory management
- Chat system
- Debug mode

## Project Structure

- **coding/**: Source code of the project
  - `main.cpp`: Main file with the game loop and core functionality
  - `Chunk.cpp`, `Chunk.hpp`: Definitions and implementations for chunks
  - `Debug.cpp`, `Debug.hpp`: Debugging tools
  - `DecorationSet.cpp`, `DecorationSet.hpp`: Decorations for the game
  - `Globals.cpp`, `Globals.hpp`: Global variables and functions
  - `Inventory.cpp`, `Inventory.hpp`: Inventory management
  - `MyCamera.cpp`, `MyCamera.hpp`: Camera control
  - `my_resource.cpp`, `my_resource.hpp`: Resource management
  - `my_string.cpp`, `my_string.hpp`: String utilities
  - `my_time.cpp`, `my_time.hpp`: Time utilities
  - `PerlinNoise.cpp`, `PerlinNoise.hpp`: Perlin noise generation
  - `Player.cpp`, `Player.hpp`: Player definition and control
  - `TileSet.cpp`, `TileSet.hpp`: Tile management
- **resource/**: Resources for the game
  - `fonts/`: Fonts
  - `img/`: Images (tiles, sprites, etc.)
- **Makefile**: Build script for the project
- **resource.rc**: Resource file for Windows
- **README.md**: This file

## Tutorial install SFML (mingw) to VSCODE

Video: https://youtu.be/jKbWBcVPLWQ?si=V_tRKK-mcBykcHBP

## Building and Running

1. Make sure you have the necessary dependencies installed, including SFML.
2. Clone the repository and navigate to the project directory:
   ```sh
   git clone <URL>
   cd RPG_GAMES
   ```
3. Run the `make` command to build the project:
   ```sh
   make
   ```
4. Run the compiled executable:
   ```sh
   ./main.exe
   ```

## Makefile Information

- `all`: Default target. Performs compilation and linking.
- `compile`: Compiles source files.
- `link`: Links object files and resources.
- `clean`: Cleans intermediate files and the executable.
- `run`: Builds and runs the executable.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Screenshots

![image](https://github.com/user-attachments/assets/2e352df1-4c00-4327-b34e-89e49b034170)
