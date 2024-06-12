# deepbird
An attempt to use reinforcement learning on flappybird

## Project Structure

The game itself is built ontop of a game engine which was coded from scratch using a mix of OpenGl and SDL. Further, development was done on Visual Studio 2022 but since this repo includes the header, lib, and dll files for the SDL and OpenGl libraries, any system with a C++ compiler should be able to compile the source code.

The main interface for the project is a tkinter GUI found in `tkinter_app.py`. From there you can play the game yourself, start training an AI to play the game (using one of the implemented algorithms), or watch a pre-trained AI play the game.

## Reinforcement Learning

All reinforcement learning algorithms used in this project can be found in Sutton and Barto's [book](http://incompleteideas.net/book/RLbook2020.pdf) on the matter.

Currently TD Sarsa and Policy Iteration have been implemented. More info can be found on my [blog](https://www.jamonalbus.com/articles/deepbird)
