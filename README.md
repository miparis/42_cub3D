
# 🚀 Cub3D: Un Motor de Juego 3D al Estilo Wolfenstein 3D

This project implements a basic 3D game engine using the MiniLibX library, inspired by the classic Wolfenstein 3D. The goal is to render a 3D environment from a 2D map, allowing the player to explore a labyrinth with textures and colors.

## ✨ Features
* **Fast Raycasting Engine:** Real-time 3D perspective rendering from a 2D map.

* **Dynamic Player Movement:** Smooth movement (forward, backward, strafing) and rotation.

* **Collision Detection:** Prevents the player from moving through walls.

* **Textured Walls:** Walls are rendered with distinct textures based on their orientation.

* **Solid Color Floor & Ceiling:** Basic environmental elements for depth.

* **Robust Error Handling:** Comprehensive validation for map and configuration files.

  ![Screenshot of a comment on a GitHub issue showing an image, added in the Markdown, of an Octocat smiling and raising a tentacle.](https://myoctocat.com/assets/images/base-octocat.svg)

## 📦 Structure

**cub3d/**
├── includes/               
│   ├── cub3d.h
│   │── libft/              
│   │   ├── libft.a
│   │   ├── Makefile
│   │   └── ...
│   ├── mlx/                
│       ├── libmlx.a
│       └── ...
├── src/
│   ├── parse/            # Parsing of the .cub file & the configurations
│   ├── graphics/         # Initialization of textures, window, and structures
│   ├── raycasting/       # DDA for ray calculation, rendering and motion updating      
│   └── main.c
│
├── maps/
│   └── test.cub
│
├── textures/
│   └── *.xmp
│
├── Makefile

👉👉 Check out the full project guide in [cub3D](https://pages.github.com/).
