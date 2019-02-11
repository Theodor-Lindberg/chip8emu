#ifndef CHIP_8
#define CHIP_8

#include <random>

class Chip8 {
public:
	Chip8();
	~Chip8() = default;

	/// <summary> Reset the cpu to a clean state. </summary>
	void reset();

	/// <summary> Emulate one cycle on the cpu. </summary>
	void emulate_cycle();

	/// <summary> Load a ROM into main memory. </summary>
	/// <param name="p_rom"> Pointer to the rom. </param>
	/// <returns> If the function succeeds true is returned, otherwise false. </returns>
	bool load_rom(const uint8_t* const p_rom, const size_t &size);

	/// <summary> The flag is set if changes have been made to the display. </summary>
	bool get_draw_flag() const;

	/// <summary> Set the frequency of which the cpu will be running to get timers correct. </summary>
	/// <param name="frequency"> The frequency of the clock. </param>
	void set_clock_freq(const uint16_t frequency);

	/// <summary> Update the state of a key on the keypad. </summary>
	/// <param name="key_index"> The index of the key. </param>
	/// <param name="state"> The state of the key, true for pressed and false for released. </param>
	void update_key(const uint8_t& key_index, const bool& state);

	/// <summary> Reset the draw flag. </summary>
	void reset_draw_flag();

	/// <summary> Return a pointer to the graphics buffer. </summary>
	const bool* const get_gfx_buffer() const;

	static constexpr size_t SCREEN_WIDTH = 64;
	static constexpr size_t SCREEN_HEIGHT = 32;

private:
	static constexpr size_t STACK_SIZE = 16;
	static constexpr size_t MEMORY_SIZE = 4096;
	static constexpr size_t GPDR_COUNT = 16;
	static constexpr size_t ROM_START_ADDRESS = 0x200;
	static constexpr size_t MAX_ROM_SIZE = MEMORY_SIZE - ROM_START_ADDRESS;
	static constexpr size_t TIMER_FREQUENCY = 60;
	static constexpr size_t KEY_COUNT = 16;
	static constexpr size_t SPRITE_WIDTH = 8;

	uint16_t I = 0;						// Index register
	uint16_t pc = ROM_START_ADDRESS;	// Program counter
	uint16_t curr_op_code = 0;

	uint8_t sp = 0;						// Stack pointer
	uint16_t stack[STACK_SIZE] = {};

	uint8_t memory[MEMORY_SIZE] = {};	// Main memory
	uint8_t V[GPDR_COUNT] = {};			// General purpose data registers
	bool gfx_buffer[SCREEN_WIDTH * SCREEN_HEIGHT] = {}; // Buffer to draw graphics to

	uint16_t clock_frequency = TIMER_FREQUENCY;
	uint16_t cpu_cycles = 0;
	uint8_t sound_timer = 0;
	uint8_t delay_timer = 0;

	std::mt19937 rng_eng{ std::random_device()() };
	std::uniform_int_distribution<uint16_t> distr{ 0, 0xFF };

	bool keypad_state[KEY_COUNT] = {};	// The current state of the keypad where true is pressed and false is released.

	bool waiting_for_keypress = false;

	bool draw_flag = true;

	/// <summary> Load a font set into main memory. </summary>
	/// <param name="p_font"> Pointer to the font set. </param>
	/// <returns> If the function succeeds true is returned, otherwise false. </returns>
	bool load_font(const uint8_t* const p_font, const size_t &size);

	/// <summary> Fetch the new operation code. </summary>
	uint16_t fetch_opcode();

	/// <summary> Update the sound and delay timer. </summary>
	void update_timers();

	// The following functions are implemented in 'chip8instructions.cpp'.

	/// <summary> Execute instruction based on operation code </summary>
	/// <remarks> A switch is used instead of a map or array of function pointers
	/// so that the compiler can optimize it into a faster lookup table. </remarks>
	/// <param name="op_code"> The code of the instruction </param>
	/// <returns> If the function succeeds true is returned, otherwise false. </returns>
	bool execute_instruction(uint16_t& op_code);

	#include "chip8instructions.hpp"
};

#endif // !CHIP_8