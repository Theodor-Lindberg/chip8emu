#include <cstring>
#include "chip8.h"
#include "fontset.h"

Chip8::Chip8() {
	reset();
	if (!load_font(font_set, sizeof(font_set))) {
		// TODO: Handle
	}
}

Chip8::~Chip8() { }

bool Chip8::load_font(const uint8_t* p_font, const size_t &size) {
	if (size > ROM_START_ADDRESS) {
		return false;
	}

	std::memcpy(memory, p_font, size);
	return true;
}

void Chip8::reset() {
	std::memset((uint8_t*)memory + ROM_START_ADDRESS, 0, MAX_ROM_SIZE);
	std::memset(&stack, 0, STACK_SIZE);
	std::memset(&V, 0, GPDR_COUNT);
	std::memset(&gfx_buffer, 0, sizeof(gfx_buffer));
	pc = ROM_START_ADDRESS;
	I = 0;
}

void Chip8::emulate_cycle() {

}

bool Chip8::load_rom(const uint8_t* p_rom, const size_t &size) {
	if (size > MAX_ROM_SIZE) {
		return false;
	}

	std::memcpy(memory, p_rom, size);
	return true;
}