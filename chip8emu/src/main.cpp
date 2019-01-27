#include "chip8.hpp"
#include "chip8display.hpp"
#include "chip8input.hpp"
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
	Chip8Display display = Chip8Display(window, chip8, SDL_Point{50, 50});

	while (!window.is_closed()) {
		if (chip8.get_draw_flag()) {
			display.render();
			chip8.reset_draw_flag();
			window.clear();
		}

		poll_events(window, keypad);
	}

	return EXIT_SUCCESS;
}