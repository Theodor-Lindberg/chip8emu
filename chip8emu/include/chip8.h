#include <cstdint>

#ifndef CHIP_8
#define CHIP_8

class Chip8 {
private:
	// Define constants
	static constexpr uint16_t STACK_SIZE = 16;
	static constexpr uint16_t MEMORY_SIZE = 4096;
	static constexpr uint16_t GPDR_COUNT = 16;
	static constexpr uint16_t SCREEN_WIDTH = 64;
	static constexpr uint16_t SCREEN_HEIGHT = 32;
	static constexpr uint8_t  PRGM_START_ADDRESS = 0x200;

	uint16_t sp;					// Stack pointer
	uint16_t stack[STACK_SIZE];

	uint16_t I;						// Index register
	uint16_t pc;					// Program counter

	uint8_t memory[MEMORY_SIZE];	// Main memory
	uint8_t V[GPDR_COUNT];			// General purpose data registers
	uint8_t gfx_buffer[SCREEN_WIDTH * SCREEN_HEIGHT]; // Buffer to draw graphics to

public:
	Chip8();
	~Chip8();

	/// <summary> Reset the cpu to a clean state. </summary>
	void reset();

	/// <summary> Load a ROM into main memory. </summary>
	/// <param name="rom"> Reference to the rom. </param>
	/// <returns> If the functions succeds true is returned, otherwise false. </returns>
	bool load_rom(const uint8_t &rom);

	/// <summary> Emulate one cycle on the cpu. </summary>
	void emulate_cycle();
};

#endif // !CHIP_8