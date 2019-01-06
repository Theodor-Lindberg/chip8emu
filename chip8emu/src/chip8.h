#include <cstdint>

#ifndef _CHIP_8
#define _CHIP_8

class Chip8 {
private:
	// Define constants
	static const uint16_t STACK_SIZE = 16;
	static const uint16_t MEMORY_SIZE = 4096;
	static const uint16_t GPDR_COUNT = 16;
	static const uint16_t SCREEN_WIDTH = 64;
	static const uint16_t SCREEN_HEIGHT = 32;
	static const uint8_t  PRGM_START_ADDRESS = 0x200;

	uint16_t sp;					// Stack pointer
	uint16_t stack[STACK_SIZE];		// Stack

	uint16_t I;						// Index register
	uint16_t pc;					// Program counter

	uint8_t memory[MEMORY_SIZE];	// Main memory
	uint8_t V[GPDR_COUNT];			// General purpose data registers
	uint8_t gfx_buffer[SCREEN_WIDTH * SCREEN_HEIGHT]; // Buffer to draw graphics to

	void reset();

public:
	Chip8();
	~Chip8();
	void init();
	bool load_rom(const uint8_t * rom);
	void emulate_cycle();
};

#endif // !_CHIP_8