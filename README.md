# Agent Based Modeling (ABM) Simulation

A real-time agent-based modeling simulation built on the **Kinetica Game Engine**, featuring autonomous agents (zombies and survivors) navigating a procedurally generated environment with dynamic AI behaviors.

![Version](https://img.shields.io/badge/version-0.1-blue)
![Platform](https://img.shields.io/badge/platform-macOS-lightgrey)
![OpenGL](https://img.shields.io/badge/OpenGL-2.1-green)

---

## Table of Contents

- [Features](#features)
- [Screenshots](#screenshots)
- [Requirements](#requirements)
- [Installation](#installation)
- [Building](#building)
- [Running](#running)
- [Controls](#controls)
- [Project Structure](#project-structure)
- [Configuration](#configuration)
- [Technical Details](#technical-details)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)
- [License](#license)
- [Credits](#credits)

---

## Features

### Agent-Based Simulation
- **Autonomous Agents**: Zombies and survivors with independent AI decision-making
- **Dynamic Behaviors**: Multiple AI modes for different agent responses
- **Pathfinding**: Agents navigate around obstacles and through the environment
- **Alarm System**: Trigger alerts that modify agent behavior patterns
- **Population Management**: Automatic spawning with configurable limits

### Rendering & Graphics
- **OpenGL 2.1 Compatibility**: Fixed-function pipeline for broad hardware support
- **Texture Mapping**: Sprite-based rendering with mipmapping
- **Alpha Blending**: Proper transparency for overlays and effects
- **2D Orthographic Projection**: Top-down view optimized for strategy gameplay
- **HighDPI Support**: Crisp rendering on Retina displays

### Game Engine Features
- **Dashboard Overlay**: In-game menu system with ESC key
- **Frame Rate Management**: Adaptive game speed based on performance
- **Screenshot Capture**: Save PNG screenshots during gameplay
- **Settings System**: INI-based configuration
- **Audio Support**: SDL2_mixer integration for sound effects and music

---

## Screenshots

*Start the simulation to see the agents in action!*

---

## Requirements

### System Requirements
- **OS**: macOS 11.3 or later (optimized for Apple Silicon M-series)
- **Graphics**: OpenGL 2.1 compatible GPU
- **Memory**: 512 MB RAM minimum
- **Storage**: 50 MB free space

### Build Dependencies
- **Meson** (0.55+): Build system
- **Ninja**: Build backend
- **SDL2**: Window management and input
- **SDL2_image**: Texture loading (PNG support)
- **SDL2_mixer**: Audio playback
- **OpenGL**: Graphics rendering (system framework)
- **C++ Compiler**: Clang or GCC with C++11 support

---

## Installation

### Install Dependencies (macOS with Homebrew)

```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install build tools
brew install meson ninja

# Install SDL2 libraries
brew install sdl2 sdl2_image sdl2_mixer
```

### Clone the Repository

```bash
git clone <repository-url>
cd ABM_code
```

---

## Building

### Configure the Build

```bash
meson setup build
```

### Compile

```bash
meson compile -C build
```

### Clean Build (if needed)

```bash
rm -rf build
meson setup build
meson compile -C build
```

---

## Running

### Launch the Simulation

```bash
./build/ABM
```

### Command Line Options

The application currently runs with default settings. Configuration is managed through `settings.ini`.

---

## Controls

### Main Menu
- **W / Up Arrow**: Navigate menu up
- **S / Down Arrow**: Navigate menu down
- **Space / Enter**: Select menu item

### In-Game
- **Arrow Keys**: Move player character
- **S**: Trigger alarm (changes agent behavior)
- **A**: Deactivate alarm
- **1-4**: Switch AI mode
- **Z / X**: Adjust camera zoom
- **ESC**: Open pause menu

### Pause Menu (ESC)
- **Resume**: Return to simulation
- **Screenshot**: Capture current frame to PNG
- **Exit**: Quit application

---

## 📁 Project Structure

```
ABM_code/
├── build/                      # Build output directory
├── Media/                      # Game assets
│   ├── spritesheettexture.png # Main sprite atlas
│   ├── dashboard.png          # UI elements
│   ├── borderdarknesstexture.png
│   ├── borderbloodtexture.png
│   ├── cloudshadowtexture.png
│   ├── tilebrighttexture.png
│   └── tiledarktexture.png
├── source/                    # Source code
│   ├── main.cpp              # Entry point
│   ├── generic/              # Engine core
│   │   ├── initvideo.h       # OpenGL/SDL initialization
│   │   ├── input.h           # Input handling
│   │   ├── 3dfunctions.h     # Camera and rendering
│   │   ├── dashboard/        # UI system
│   │   └── opengl/           # OpenGL utilities
│   └── projectspecific/      # Game logic
│       ├── play.h            # Main game loop
│       ├── drawworld.h       # World rendering
│       ├── menuandhud.h      # Menu system
│       ├── entities/         # Agent definitions
│       └── textures.h        # Texture management
├── meson.build               # Build configuration
├── settings.ini              # Runtime settings
└── README.md                 # This file
```

---

## Configuration

### settings.ini

```ini
screenw             = 1280 ;  # Window width
screenh             = 720  ;  # Window height
screenbpp           = 32   ;  # Color depth
fullscreen          = 0    ;  # 0=windowed, 1=fullscreen
showcursor          = 1    ;  # 0=hide, 1=show
antialiasing        = 0    ;  # 0=off, 1=on (MSAA 4x)
mipmapping          = 1    ;  # 0=off, 1=on
```

### Modifying Settings
1. Edit `settings.ini` with a text editor
2. Save changes
3. Restart the application

---

## Technical Details

### Architecture

#### Rendering Pipeline
1. **Initialization**: SDL2 window + OpenGL 2.1 context
2. **Asset Loading**: Textures loaded via SDL2_image, converted to RGBA32
3. **Main Loop**: 
   - Event processing (SDL_PumpEvents)
   - Input update
   - Game logic (projectloop)
   - Dashboard overlay (dashloop)
   - Buffer swap (SDL_GL_SwapWindow)

#### Camera System
- **2D Orthographic**: `glOrtho` for top-down view
- **Aspect Ratio Correction**: Horizontal scaling based on `screena`
- **Dynamic Zoom**: Adjustable `camz` parameter

#### Agent AI
- **State Machine**: Behavior modes (1-4)
- **Target Acquisition**: Proximity-based detection
- **Collision Avoidance**: Wall and object detection
- **Spawning Logic**: Grid-based placement with collision checks

### Performance Considerations
- **Frame Rate Target**: 60 FPS
- **Adaptive Speed**: Game logic scales with actual frame rate
- **VSync**: Enabled by default (`SDL_GL_SetSwapInterval(1)`)
- **Texture Optimization**: Mipmapping for distant objects

### Coordinate Systems
- **Window Points**: Logical coordinates for input/UI (e.g., 1280x720)
- **Drawable Pixels**: Physical framebuffer (2x on Retina displays)
- **World Space**: Game units (tiles, agent positions)
- **Screen Space**: Normalized coordinates for rendering

---

## Troubleshooting

### Build Issues

**Problem**: `meson: command not found`
```bash
# Solution: Install meson
brew install meson
```

**Problem**: SDL2 libraries not found
```bash
# Solution: Install SDL2 dependencies
brew install sdl2 sdl2_image sdl2_mixer
```

**Problem**: Linking errors with OpenGL
```bash
# Solution: Ensure you're using system OpenGL framework
# Check meson.build has: dependencies : [sdl2_dep, sdl2_image_dep, sdl2_mixer_dep, opengl_dep]
```

### Runtime Issues

**Problem**: Black screen on launch
- **Solution**: Ensure all textures exist in `Media/` directory
- Check console output for "Failed to load texture" messages

**Problem**: Menu text too large/small
- **Solution**: Adjust window resolution in `settings.ini`
- Recommended: 1280x720 or 1920x1080

**Problem**: Performance issues
- **Solution**: Disable antialiasing in `settings.ini`
- Reduce agent population limits in `source/projectspecific/play.h`

**Problem**: Crash on ESC menu
- **Solution**: Ensure `Media/dashboard.png` exists and is valid

### Graphics Issues

**Problem**: Textures appear corrupted
- **Solution**: Verify PNG files are RGBA format
- Rebuild with `rm -rf build && meson setup build && meson compile -C build`

**Problem**: Aspect ratio incorrect
- **Solution**: Check `screena` calculation in `initvideo.h`
- Ensure window size matches aspect ratio (16:9 recommended)

---

## Contributing

Contributions are welcome! Please follow these guidelines:

1. **Fork** the repository
2. **Create** a feature branch (`git checkout -b feature/amazing-feature`)
3. **Commit** your changes (`git commit -m 'Add amazing feature'`)
4. **Push** to the branch (`git push origin feature/amazing-feature`)
5. **Open** a Pull Request

### Code Style
- Use tabs for indentation
- Follow existing naming conventions
- Comment complex logic
- Test on macOS before submitting

---

## License

This project is built on the **Kinetica Game Engine** by Ahmad Byagowi.

*License details to be added*

---

### Libraries & Tools
- **SDL2**: Simple DirectMedia Layer (window/input/audio)
- **OpenGL**: Graphics rendering
- **LodePNG**: PNG encoding for screenshots
- **Meson**: Build system
- **Homebrew**: Package management (macOS)

### Special Thanks
- SDL community for excellent documentation
- OpenGL community for legacy compatibility support

---

## Contact & Support

For questions, issues, or suggestions:
- **Issues**: Use the GitHub issue tracker
- **Discussions**: GitHub Discussions tab

---

## Roadmap

### Planned Features
- [ ] Network multiplayer support
- [ ] Additional agent types
- [ ] Advanced pathfinding (A*)
- [ ] Save/load simulation states
- [ ] Statistics and analytics dashboard
- [ ] Configurable world generation
- [ ] Mod support

### Known Issues
- Deprecated OpenGL/GLU function warnings (cosmetic, no impact)
- Screenshot feature requires manual file management

---

**Last Updated**: December 2025  
**Version**: 0.1  
**Status**: Active Development

---

*Built with using the Kinetica Game Engine*


## License

This project is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License (CC BY-NC 4.0).

You are free to:

Share — copy and redistribute the material in any medium or format
Adapt — remix, transform, and build upon the material
Under the following terms:

Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made.
NonCommercial — You may not use the material for commercial purposes.
For full details, see: https://creativecommons.org/licenses/by-nc/4.0/

As the project creator, I reserve the right to use this material commercially or under any other terms.
