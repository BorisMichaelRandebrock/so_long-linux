<!-- # 42 so_long

Welcome to my so_long project!  
This project is part of the 42 curriculum, aimed at creating a simple 2D game application using the MiniLibX library. The goal is to develop a small game that demonstrates basic graphics programming concepts.

## Table of Contents

<img align="right" src="https://github.com/BorisMichaelRandebrock/so_long_bonus/assets/98555508/96e3b835-0b1e-4511-8ebe-a78016c3d746"
     alt="so_long with boo.ber"  width="670" height="200">

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Game Controls](#game-controls)
- [Examples](#examples)
- [Contributing](#contributing)

## Introduction

The project is a simple 2D game developed using the MiniLibX library. The player controls a character that can move around a map, collect items, and reach an exit to complete the level. This project helps students understand graphics programming and event handling.

## Features

- 2D graphics rendering using MiniLibX
- Player movement and collision detection
- Collectible items
- Game map with walls and an exit
- Basic event handling (keyboard input)

## Installation

To install and compile the So Long project, follow these steps:

1. Clone the repository:

   ```sh
   git clone https://github.com/BorisMichaelRandebrock/so_long_bonus.git
   cd so_long
   ```

2. Compile the project:

   ```sh
   make
   ```

3. Run the game:
   ```sh
   ./so_long maps/boo.ber
   ```

## Usage

Once you have compiled and run the game, you can start playing by using the keyboard to control the character. The objective is to collect all items and reach the exit.

## Game Controls

- `W` or `Up Arrow`: Move up
- `A` or `Left Arrow`: Move left
- `S` or `Down Arrow`: Move down
- `D` or `Right Arrow`: Move right
- `ESC`: Exit the game

## Examples

Here are a few examples of how to use the So Long project:

```sh
# Run the game with a specific map
./so_long maps/boo.ber

# Run the game with another map
./solong maps/map1.ber
./solong maps/map2.ber
or any other map you can find here or create...
```

## Contributing

Contributions are welcome! If you would like to contribute to this project, please fork the repository and create a pull request with your changes. Make sure to follow the coding standards and include relevant tests with your contributions.

1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Commit your changes.
4. Push to your branch.
5. Create a pull request.

<img width="1345" alt="Captura de pantalla 2024-06-14 a las 22 45 23" src="https://github.com/BorisMichaelRandebrock/so_long_bonus/assets/98555508/96e3b835-0b1e-4511-8ebe-a78016c3d746">
 -->

# 🐬 so_long — A 2D Adventure with Bats, Teleporters & Multi-Level Progression

> *"And thanks for all the fish!"*

A top-down 2D puzzle game built with **MiniLibX** as part of the 42 School curriculum. Guide your character through increasingly complex maps, collect all coins, avoid deadly bats, and escape before it’s too late!

---

## 🎮 Features

### ✅ **Mandatory**
- Move with **WASD** or **arrow keys**
- Collect all **`C`** (coins) before reaching the exit **`E`**
- Walls **`1`** are impassable
- Movement counter displayed in terminal

### 🌟 **Bonus Features**
- **On-screen movement counter** (no need to check terminal!)
- **Animated bat enemies** that:
  - Fly freely across the map
  - Randomly change direction
  - Kill the player on contact
- **Bidirectional teleportation**:
  - Step on any **`T`** tile to instantly warp to another **`T`** tile
  - Teleporters are **consumed on landing**, not departure
  - Supports **2+ warp points** — warp from 1→2, then 3→1, etc.
- **Game over screen** with black background and red text
- **Win screen** with green centered message

### 🎯 **Multi-Level Mode** (`multi-level-play` branch)
- Start the game with: `./so_long`
- Play through **10 progressively harder levels**
- Automatic level progression upon victory
- Final victory screen after completing all levels (I could not manage to see that one.. )   
   

this branch is presently having leaks and is not compliant to norminette - but it is fun to try...


---

## 📁 Map Format (`.ber`)

Maps use these characters:
- `1` — Wall (impassable)
- `F` — false Wall (Player cleans tile by passing.., bats can fly over and reveal secret passage)
- `0` — Empty space
- `P` — Player start position
- `C` — Collectible coin
- `E` — Exit (must collect all coins first)
- `B` — Bat spawn point (bonus)
- `T` — Warp (Teleporter) tile (bidirectional, random destination between available warp points - be aware of bat presence at possible destinations!!!)

**Example:**
```
11111111
1P0T00C1
10B00001
100000E1
11111111
```

---

## 🛠️ Compilation

### Standard (Mandatory + Bonus)
```bash
make
./so_long maps/map_of_your_choosing.ber
```

### Multi-Level Mode
```bash
git checkout multi-level-play
make
./so_long  # No map argument needed — plays all 10 levels automatically
```

### Bonus Rule (as required by subject)
```bash
make bonus && ./so_long
```

---

## 🎮 Controls

| Key | Action |
|-----|--------|
| **W / ↑** | Move up |
| **A / ←** | Move left |
| **S / ↓** | Move down |
| **D / →** | Move right |
| **ESC** | Quit game |
| **Window Close (X)** | Quit game |

---

## 📜 Subject Compliance

- ✅ **Norminette compliant** (25 lines max per function, no forbidden functions)
- ✅ **No memory leaks** (Valgrind clean)
- ✅ **All heap memory properly freed**
- ✅ **No undefined behavior or crashes**
- ✅ **Bonus features in separate files** (`bonus.c`, `bonus_bis.c`, etc.)
- ✅ **Uses only allowed functions**: MiniLibX, libft, ft_printf, standard C

---

## 🧪 Testing

Tested on **Ubuntu 22.04** with **MiniLibX Linux** version from 42 School repository.

---

## 🎨 Assets

- Custom **32x32 pixel art** for player, enemies, and teleporters
- Smooth **5-frame bat animation**
- Clean, readable UI with on-screen counter

---

## 🚀 Enjoy the Game!

Dodge bats, warp through dimensions, and conquer all 10 levels!  
*Good luck — and watch out for those bats!* 🦇