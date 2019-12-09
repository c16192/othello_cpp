# Othello Game in C++
Developed by Shu Ishida as a one-week project for AIMS CDT C++ programming (December 2019)

## Introduction to Othello

Othello, also known as [Reversi](https://en.wikipedia.org/wiki/Reversi), is a two-player board game played on a 8 x 8 gridded board. 
There are 64 identical game pieces called disks, which are white on one side and black on the other. 
Players take turns placing disks on the board with their assigned color facing up. 
During a play, any disks of the opponent's color that are in a straight line and bounded by the disk just placed and another disk of the current player's color are turned over to the current player's color.
The object of the game is to have the majority of disks turned to display your color when the last playable empty square is filled. 

## Setup
The following instruction works if you are on Ubuntu (tested on Ubuntu 18.04). 

1. Install `cmake` 
2. Clone this repository: `git clone https://github.com/c16192/othello_cpp.git`
4. Compile the code using CMake. This could be done by run the following lines in the terminal:
   ```
   cd othello_cpp   # moving into root directory
   mkdir build      # making a directory called "build"
   cd build         # moving into the "build" directory
   cmake ..         # create cmake files following `CMakeLists.txt` in the parent directory
   cmake --build .  # build and save binary in current directory
   ```
5. Run the programme: `./othello`
