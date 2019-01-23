#ifndef CHIP_8
#define CHIP_8

#include "chip8instructions.hpp"

class Chip8 {
public:
	Chip8();
	~Chip8();

	/// <summary> Reset the cpu to a clean state. </summary>
	void reset();

	/// <summary> Emulate one cycle on the cpu. </summary>
	void emulate_cycle();

	/// <summary> Load a ROM into main memory. </summary>
	/// <param name="p_rom"> Pointer to the rom. </param>
	/// <returns> If the function succeeds true is returned, otherwise false. </returns>
	bool load_rom(const uint8_t* const p_rom, const size_t &size);

	/// <summary> The flag is set if changes have been made to the display. </summary>
	bool draw_flag() const;

	/// <summary> Set the frequency of which the cpu will be running to get timers correct. </summary>
	/// <param name="frequency"> The frequency of the clock. </param>
	void set_clock_freq(uint16_t& frequency);

private:
	friend class OPCodes;
	OPCodes op_codes = OPCodes(*this);

	static constexpr size_t STACK_SIZE = 16;
	static constexpr size_t MEMORY_SIZE = 4096;
	static constexpr size_t GPDR_COUNT = 16;
	static constexpr size_t SCREEN_WIDTH = 64;
	static constexpr size_t SCREEN_HEIGHT = 32;
	static constexpr size_t ROM_START_ADDRESS = 0x200;
	static constexpr size_t MAX_ROM_SIZE = MEMORY_SIZE - ROM_START_ADDRESS;
	static constexpr size_t TIMER_FREQUENCY = 60;

	uint16_t I = 0;						// Index register
	uint16_t pc = ROM_START_ADDRESS;	// Program counter

	uint8_t sp = 0;						// Stack pointer
	uint16_t stack[STACK_SIZE] = {};

	uint8_t memory[MEMORY_SIZE] = {};	// Main memory
	uint8_t V[GPDR_COUNT] = {};			// General purpose data registers
	uint8_t gfx_buffer[SCREEN_WIDTH * SCREEN_HEIGHT] = {}; // Buffer to draw graphics to

	uint16_t clock_frequency = TIMER_FREQUENCY;
	uint16_t cpu_cycles = 0;
	uint8_t sound_timer = 0;
	uint8_t delay_timer = 0;

	bool _draw_flag;

	/// <summary> Load a font set into main memory. </summary>
	/// <param name="p_font"> Pointer to the font set. </param>
	/// <returns> If the function succeeds true is returned, otherwise false. </returns>
	bool load_font(const uint8_t* const p_font, const size_t &size);

	/// <summary> Fetch the current operation code. </summary>
	/// <returns> The current operation code. </returns>
	uint16_t fetch_opcode() const;
};

#endif // !CHIP_8