#include "chip8.hpp"
#include "chip8input.hpp"
#include "window.hpp"
#include <iostream>

void poll_events(Window& window, Chip8Input& keypad) {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		window.handle_event(event);
		keypad.handle_events(event);
	}
}

int main(int argc, char *argv[]) {
	Window window("CHIP8 Emulator", 800, 600);
	Chip8 chip8 = Chip8();
	Chip8Input keypad(chip8);

	while (!window.is_closed()) {
		poll_events(window, keypad);
		window.clear();
	}

	return EXIT_SUCCESS;
}