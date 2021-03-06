#include "chip8.hpp"
#include "fontset.hpp"

Chip8::Chip8() {
	if (!load_font(font_set, sizeof(font_set))) {
		// TODO: Handle
	}
}

void Chip8::reset() {
	memset(static_cast<uint8_t*>(memory) + ROM_START_ADDRESS, 0, MAX_ROM_SIZE);
	memset(&stack, 0, sizeof(stack));
	memset(&V, 0, sizeof(V));
	memset(&gfx_buffer, false, sizeof(gfx_buffer));
	memset(&keypad_state, false, KEY_COUNT);

	pc = ROM_START_ADDRESS;
	I = 0;
	sp = 0;

	clock_frequency = TIMER_FREQUENCY;
	cpu_cycles = 0;
	sound_timer = 0;
	delay_timer = 0;

	waiting_for_keypress = false;
	draw_flag = false;
}

void Chip8::emulate_cycle() {
	update_timers();

	curr_op_code = fetch_opcode();
	execute_instruction(curr_op_code);
}

bool Chip8::load_rom(const uint8_t* const p_rom, const size_t& size) {
	if (size > MAX_ROM_SIZE)
		return false;

	memcpy(&memory[ROM_START_ADDRESS], p_rom, size);
	return true;
}

bool Chip8::get_draw_flag() const {
	return draw_flag;
}

void Chip8::set_clock_freq(const uint16_t frequency) {
	sound_timer %= frequency;
	delay_timer %= frequency;
	cpu_cycles %= frequency / TIMER_FREQUENCY;

	clock_frequency = frequency;
}

void Chip8::update_key(const uint8_t& key_index, const bool& state) {
	keypad_state[key_index] = state;
}

const bool* const Chip8::get_gfx_buffer() const {
	return gfx_buffer;
}

void Chip8::reset_draw_flag() {
	draw_flag = false;
}

bool Chip8::load_font(const uint8_t* const p_font, const size_t& size) {
	if (size > ROM_START_ADDRESS)
		return false;

	memcpy(memory, p_font, size);
	return true;
}

uint16_t Chip8::fetch_opcode() const {
	return (memory[pc] << 8) | memory[pc + 1]; // Merge two bytes
}

void Chip8::update_timers() {
	cpu_cycles++;
	if (cpu_cycles % static_cast<int>(((TIMER_FREQUENCY * TIMER_FREQUENCY)) / static_cast<float>(clock_frequency)) == 0) {
		if (sound_timer > 0)
			sound_timer--;
		if (delay_timer > 0)
			delay_timer--;
	}
}