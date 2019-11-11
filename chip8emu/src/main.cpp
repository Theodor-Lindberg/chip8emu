#include "chip8.hpp"
#include "chip8display.hpp"
#include "chip8input.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include "filehelper.hpp"

void poll_events(Window& window, Chip8Input& keypad) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		window.handle_event(event);
		keypad.handle_events(event);
	}
}

int main(int argc, char *argv[]) {
	Window window("CHIP8 Emulator", Chip8::SCREEN_WIDTH * 10, Chip8::SCREEN_HEIGHT * 10);
	Chip8 chip8;
	Chip8Input keypad(chip8);
	Chip8Display display(window, chip8, SDL_Point{0, 0});

	if (!FileHelper::load_binaries(argv[1], chip8)) {
		std::cout << "Error: could not load the binaries to the emulator" << std::endl;
		std::getchar();
		return -1;
	}

	int freq = 84;
	int target_us = 1000000 / 84;
	chip8.set_clock_freq(freq * 10);

	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	int delta = 0;

	while (window.is_open()) {
		if (chip8.get_draw_flag()) {
			display.render();
			chip8.reset_draw_flag();
			window.clear();
		}
		
		poll_events(window, keypad);

		end = std::chrono::high_resolution_clock::now();
		delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

		if (delta < target_us)
			std::this_thread::sleep_for(std::chrono::microseconds(target_us - delta));

		for (int i = 0; i < 10; i++)
			chip8.emulate_cycle();

		start = std::chrono::high_resolution_clock::now();

	}

	return EXIT_SUCCESS;
}