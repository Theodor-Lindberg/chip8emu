#include <iostream>
#include "SDL.h"
#include "chip8.hpp"

int main(int argc, char *argv[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL could not be initialized! SDL Error: " << SDL_GetError() << std::endl;
	}

	Chip8 chip8 = Chip8();
	return EXIT_SUCCESS;
}