# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
## New features  added to the game
1. Add Game Start User interface
2. Can Choose Game Difficulty (Easy ,Medium,Hard)
3. Bonus Food Appear and increases score by +2 
4. Save Player Name and Score and show them on Demand from the user interface

## Information about each rubric point addressed.
 **Compiling and Testing (All Rubric Points REQUIRED) -> DONE**
 
**Loops, Functions, I/O  -> DONE**
	The project demonstrates an understanding of C++ functions and control structures. **(GameManager.cpp)**
	The project reads data from a file and process the data, or the program writes data to a file. **(GameUser.cpp, GUS_ReadUsersHistory())**
	The project accepts user input and processes the input. **(GameManager.cpp , getPressedKey())**
	The project uses data structures and immutable variables.** (GameUser.h, Line 30)**

**Object Oriented Programming -> DONE**
	One or more classes are added to the project with appropriate access specifiers for class members.. **(GameManager.cpp)**
	Class constructors utilize member initialization lists**. (game.cpp)**
	Overloaded functions allow the same function to operate on different parameters**.(GameUser.h)**

**Memory Management -> DONE**
	The project makes use of references in function declarations.. **(renderer.cpp,Render)**
	The project uses destructors appropriately.**(renderer.cpp)**
	The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.

**Concurrency  -> DONE**
	The project uses multithreading. **(renderer.cpp,Game.cpp)**
	A condition variable is used in the project.**(renderer.cpp,Game.cpp)**
	A mutex or lock is used in the project.**(enderer.cpp,Game.cpp)**

	