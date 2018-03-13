Graphics Assignment 1
=====================

Pacman Killer 2D game in OpenGL 3.

Akshat Maheshwari - 20161024
=======================

### Basic Info
- Player has a total of 3 lives
- Player scores points if kills enemy balls
- Enemy balls killed only when player jumps on enemies from above
- Player's path gets deflected towards the magnet when it comes in the surrounding of the magnet
- Player dies if it falls on porcupine, and is regenerated for 3 lives
- Porcupine remains intact when the player dies
- Player loses also life when it off the ground
- Once the player loses all the 3 lives, the game ends autoatically

### Controls
- a : move left
- d : move right
- space : move up
- mouse scroll : zoom in and zoom out
- Arrow-left (->) : pan left
- Arrow-right (->) : pan right
- Arrow-up (^) : pan up
- Arrow-down (v) : pan down

*Note: The action buttons work on key press, not on key release*

### Scoring
- Killing every red ball makes the player gain 10 points
- Killing every slate-blue ball makes the player gain 5 points
- Touching the porcupine will make the player lose life and deducts 50 points

### Run the Game

```
  // cd to the project folder
  cd path/to/project

  // Make a folder named build and cd into it
  mkdir build
  cd build

  // Run cmake
  cmake ..

  // Make the project
  make

  // Run the program
  ./graphics_asgn1
```

License
-------
The MIT License

Copyright &copy; 2018 Akshat Maheshwari 
