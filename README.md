# chip8emu

This is an emulator for [CHIP-8][chip8] written in C++ with the C library [SDL][sdl] for graphics.

*CHIP-8 is an interpreted programming language, developed by Joseph Weisbecker. 
It was initially used on the COSMAC VIP and Telmac 1800 8-bit microcomputers in the mid-1970s. 
CHIP-8 programs are run on a CHIP-8 virtual machine.*

## Implementation
Since there are various implementations of the CHIP-8 please read my [Wiki documentation][wikimanual] for the details.

## Developement environment
I'm using Visual Studio as developement environment on Windows 10, but in the future I maybe create a Makefile or CMake if I decide to make it cross-platform. 

## Showcase of Tetris game
![Tetris gameplay][tetris_gif]


## Remarks
Note that this project is still a work in progress so the clock frequency is still set in the source code and the file path is passed as an argument.

[chip8]:https://en.wikipedia.org/wiki/CHIP-8
[sdl]:https://www.libsdl.org/
[wikimanual]:https://github.com/Theodor-Lindberg/chip8emu/wiki/CHIP-8-Reference-Manual
[tetris_gif]:screenshots/tetris_gameplay.gif
