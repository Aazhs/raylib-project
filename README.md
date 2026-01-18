# Raylib Game - C++

A simple 2D platformer game built with raylib and C++.

## Features

- **Custom Coordinate System**: Uses a world coordinate system where (0,0) is at the center of the screen
- **Player Movement**: WASD controls with shift for sprint
- **Jump Mechanics**: Physics-based jumping with gravity
- **Resolution Independent**: Coordinate system scales automatically
a
## Project Structure

```
raylib_gamez/
├── main.cpp              # Main game loop
├── Player.hpp            # Player class header
├── Player.cpp            # Player implementation
├── CoordinateSystem.hpp  # Coordinate conversion header
├── CoordinateSystem.cpp  # Coordinate conversion implementation
├── run.sh                # Build and run script
└── README.md             # This file
```

## Controls

- **A/D**: Move left/right
- **Space**: Jump
- **Left Shift**: Sprint (hold while moving)
- **ESC**: Exit game

## Building and Running

### Prerequisites
- raylib library installed
- g++ compiler
- pkg-config

### Run
```bash
./run.sh
```

### Manual Compilation
```bash
g++ main.cpp Player.cpp CoordinateSystem.cpp -o game $(pkg-config --cflags --libs raylib)
./game
```

## Coordinate System

The game uses a custom coordinate system:
- **(0, 0)** is at the **center** of the screen
- **Positive X** goes right
- **Positive Y** goes up (inverted from screen coordinates)
- Resolution independent - change `SCREEN_WIDTH` and `SCREEN_HEIGHT` in main.cpp

## Configuration

Edit `main.cpp` to change:
- Screen resolution: `SCREEN_WIDTH` and `SCREEN_HEIGHT`
- FPS limit: `SetTargetFPS(120)`
- Fullscreen: Uncomment `ToggleFullscreen()`

Edit `Player.cpp` to adjust:
- Movement speed: `speed` variable
- Jump height: `velocityY` in jump logic
- Gravity: `gravity` variable
- Player size: `size` variable
