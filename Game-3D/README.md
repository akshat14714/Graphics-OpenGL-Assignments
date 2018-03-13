Graphics Assignment 1
=====================

Legend of Zelda 3D game in OpenGL 3.

Akshat Maheshwari - 20161024
=======================

### Basic Info
- Player has a total of 100 health
- Player scores 10 points if kills enemy monsters
- Player scores 100 points if it kills monster boss
- Player scores 1 point for each coin it collects
- Enemy monsters killed when canon fired on them
- Monster boss killed when hit with 3 canon shots
- Player's path gets deflected when sudden wind comes
- Player dies if it collides with monster boss
- Player also loses health when it collides with rocks or the enemy monsters
- Once the player loses all the health, the game ends autoatically

### Controls
- Arrow-left (->) : move left
- Arrow-right (->) : move left
- Arrow-up (^) : move left
- Arrow-down (v) : move left
- F : Fire canon ball
- C : Change camera view
- space : Jump

*Note: The action buttons work on key press, not on key release*

### Scoring
- Killing every monster enemy makes the player gain 10 points
- Killing the monster Boss makes the player gain 100 points
- Collecting the coins makes the player gain 1 point per coin

### Objects
- Player : Boat
- Gray Color Objects : Rocks
- Green Cuboids : Boosters ( Increase the speed momentarily when collected )
- Yellow Cuboids : Barrels
- Purple Cuboids : Enemy Monsters
- Lime Color Object : Monster Boss
- Gray Color boxes : Gifts ( Provide health )

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
