#include <iostream>
#include "SDL.h"
#include "chip8.h"

int main(int argc, char *argv[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL could not be initialized! SDL Error: " << SDL_GetError() << std::endl;
	}

	return EXIT_SUCCESS;
}