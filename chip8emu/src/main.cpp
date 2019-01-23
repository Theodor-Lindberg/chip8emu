#include "chip8.hpp"
#include "window.h"
#include <iostream>

void poll_events(Window& window) {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		window.poll_events(event);
	}
}

int main(int argc, char *argv[]) {
	Window window("CHIP8 Emulator", 800, 600);

	while (!window.is_closed()) {
		poll_events(window);
		window.clear();
	}

	return EXIT_SUCCESS;
}