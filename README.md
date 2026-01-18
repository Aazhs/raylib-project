
# Raylib Platformer (C++)

A simple 2D platformer game built with [raylib](https://www.raylib.com/) and C++.

a
## Features

- **Player Movement**: WASD or arrow keys, with Shift for sprint
- **Jump Mechanics**: Physics-based jumping with gravity
- **Idle/Run Animation**: Sprite-based animation for player
- **Resolution Independent**: Scales to any window size

## Project Structure

```
raylib-project/
├── main.cpp              # Main game loop
├── Player.hpp            # Player class header
├── Player.cpp            # Player implementation
├── run.sh                # Build and run script
├── player_sprites/       # Player sprite sheets (idle, run, attack, hurt)
├── background.png        # Background image
├── image.png             # Additional background or assets
├── credits.md            # Asset credits
└── README.md             # This file
```


## Controls

- **A/D** or **Left/Right**: Move left/right
- **Space** or **Up**: Jump
- **Left Shift**: Sprint (hold while moving)
- **ESC**: Exit game



## Building and Running

### Prerequisites
- [raylib](https://www.raylib.com/) installed ([installation guide](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux))
- g++ compiler (or MinGW on Windows)
- pkg-config (Linux/macOS)

### On macOS/Linux

#### Run with Script
```bash
./run.sh
```

#### Manual Compilation
```bash
g++ main.cpp Player.cpp -o game $(pkg-config --cflags --libs raylib)
./game
```

### On Windows

#### Prerequisites
- [raylib Windows installation guide](https://github.com/raysan5/raylib/wiki/Working-for-Windows)
- [MinGW-w64](http://mingw-w64.org/doku.php) or similar GCC toolchain

#### Compile and Run (Command Prompt or PowerShell)
```sh
g++ main.cpp Player.cpp -o game.exe -I<raylib_include_path> -L<raylib_lib_path> -lraylib -lopengl32 -lgdi32 -lwinmm
game.exe
```
Replace `<raylib_include_path>` and `<raylib_lib_path>` with your actual raylib include and lib directories.

If you installed raylib via MSYS2, you may use `pkg-config` as on Linux:
```sh
g++ main.cpp Player.cpp -o game.exe $(pkg-config --cflags --libs raylib)
game.exe
```


## Configuration

Edit `main.cpp` to change:
- Screen resolution: `SCREEN_WIDTH` and `SCREEN_HEIGHT`
- FPS limit: `SetTargetFPS(144)`
- Fullscreen: Toggle `ToggleFullscreen()`

Edit `Player.cpp` to adjust:
- Movement speed: `speed` variable
- Jump height: `velocityY` in jump logic
- Gravity: `gravity` variable
- Player size: `size` variable

## Assets & Credits

See [credits.md](credits.md) for sprite and background attributions.
