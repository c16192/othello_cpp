# Othello Game in C++
Developed by Shu Ishida as a one-week project for AIMS CDT C++ programming (December 2019)

## Introduction to Othello

Othello, also known as [Reversi](https://en.wikipedia.org/wiki/Reversi), is a two-player board game played on a 8 x 8 gridded board. 
There are 64 identical game pieces called disks, which are white on one side and black on the other. 
Players take turns placing disks on the board with their assigned color facing up. 
During a play, any disks of the opponent's color that are in a straight line and bounded by the disk just placed and another disk of the current player's color are turned over to the current player's color.
The object of the game is to have the majority of disks turned to display your color when the last playable empty square is filled. 

## About the project
This is an implementation of the board game Othello in C++. You can play human against human, human against computer, or computer against computer. 
The computer agent has a basic Deep Q Network implementation (although currently it does not save and load the model, so it behaves like a random bot without training).

The human vs human implementation does not depend on any external libraries. The DQN agent is implemented using [LibTorch](https://pytorch.org/cppdocs/),
an C++ API of PyTorch. 

## Setup
The following instruction works if you are on Ubuntu (tested on Ubuntu 18.04). If you are on Windows, you might run into issues when compiling the DQN implementation that depends on LibTorch.
If you still want to try out the human against human implementation, please check out the `libtorch_not_required` branch, which should compile.

1. Install LibTorch. Go to the [PyTorch website] and select the LibTorch C++ distribution without CUDA, and download the `zip` file. 
Extract your zipfile to, for example, `/home/username/mylib/cpp`. Now you should have a directory called `/home/username/mylib/cpp/libtorch`, under which there will be subdirectories called `lib`, `bin`, `include` and `share`.
For more information, please refer to the [installation instructions](https://pytorch.org/cppdocs/installing.html).

2. Install `cmake` 
3. Clone this repository: `git clone https://github.com/c16192/othello_cpp.git`
4. Create a 'build' subdirectory in the root directory.
   ```
   cd othello_cpp   # moving into root directory
   mkdir build      # making a directory called "build"
   cd build         # moving into the "build" directory
   ```
5. Compile the code using CMake. Set the environment variable "CMAKE_PREFIX_PATH" as follows to let CMake know of where your libtorch library is.
   ```
   cmake -DCMAKE_PREFIX_PATH="/home/username/mylib/cpp/libtorch" ..     # create cmake files following `CMakeLists.txt` in the parent directory. Don't forget the two dots ".."
   cmake --build .                                                      # build and save binary in current directory
   ```
6. Run the programme: `./othello`

