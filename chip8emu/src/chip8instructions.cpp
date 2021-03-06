#include "chip8.hpp"
#include "fontset.hpp"


bool Chip8::execute_instruction(const uint16_t& op_code) {
	switch (op_code & 0xF000)
	{
	case 0x0000:
		switch (op_code)
		{
		case 0x00E0: CLS(); return true;
		case 0x00EE: RET(); return true;
		default: 
			return false;
		}
	case 0x1000: JP_ADDR(op_code);			return true;	// 1NNN
	case 0x2000: CALL_ADDR(op_code);		return true;	// 2NNN
	case 0x3000: SE_VxByte(op_code);		return true;	// 3xkk
	case 0x4000: SNE_Vx_Byte(op_code);		return true;	// 4xkk
	case 0x5000: SE_Vx_Vy(op_code);			return true;	// 5xy0
	case 0x6000: LD_Vx_Byte(op_code);		return true;	// 6xkk
	case 0x7000: ADD_Vx_Byte(op_code);		return true;	// 7xkk
	case 0x8000:											// 8xyN
		switch (op_code & 0x000F)
		{
		case 0x0000: LD_Vx_Vy(op_code);		return true;	// 8xy0
		case 0x0001: OR_Vx_Vy(op_code);		return true;	// 8xy1
		case 0x0002: AND_Vx_Vy(op_code);	return true;	// 8xy2
		case 0x0003: XOR_Vx_Vy(op_code);	return true;	// 8xy3
		case 0x0004: ADD_Vx_Vy(op_code);	return true;	// 8xy4
		case 0x0005: SUB_Vx_Vy(op_code);	return true;	// 8xy5
		case 0x0006: SHR_Vx_Vy(op_code);	return true;	// 8xy6
		case 0x0007: SUBN_Vx_Vy(op_code);	return true;	// 8xy7
		case 0x000E: SHL_Vx_Vy(op_code);	return true;	// 8xyE
		default: 
			return false;
		}
	case 0x9000: SNE_Vx_Vy(op_code);		return true;	// 9xy0
	case 0xA000: LD_I_ADDR(op_code);		return true;	// ANNN
	case 0xB000: JP_V0_ADDR(op_code);		return true;	// BNNN
	case 0xC000: RND_Vx_Byte(op_code);		return true;	// Cxkk
	case 0xD000: DRW_Vx_Vy_Nibble(op_code);	return true;	// Dxyn
	case 0xE000:											// Ex
		switch (op_code & 0x00FF)
		{
		case 0x009E: SKP_Vx(op_code);	return true;		// Ex9E
		case 0x00A1: SKPN_Vx(op_code);	return true;		// ExA1
		default: 
			return false;
		}
	case 0xF000:											// Fx
		switch (op_code & 0x00FF)
		{
		case 0x0007: LD_Vx_DT(op_code);	return true;		// Fx07
		case 0x000A: LD_Vx_K(op_code);	return true;		// Fx0A
		case 0x0015: LD_DT_Vx(op_code);	return true;		// Fx15
		case 0x0018: LD_ST_Vx(op_code);	return true;		// Fx18
		case 0x001E: ADD_I_Vx(op_code);	return true;		// Fx1E
		case 0x0029: LD_F_Vx(op_code);	return true;		// Fx29
		case 0x0033: LD_B_Vx(op_code);	return true;		// Fx33
		case 0x0055: LD_I_Vx(op_code);	return true;		// Fx55
		case 0x0065: LD_Vx_I(op_code);	return true;		// Fx65
		default: 
			return false;
		}
	default: 
		return false;
	}
	return true;
}

void Chip8::CLS() {										// 0x00E0
	memset(gfx_buffer, false, sizeof(gfx_buffer));
	pc += 2;
}

void Chip8::RET() {										// 0x00EE
	sp--;
	pc = stack[sp];
	pc += 2;
}

void Chip8::JP_ADDR(const uint16_t& op_code) {			// 1NNN
	pc = op_code & 0x0FFF;
}

void Chip8::CALL_ADDR(const uint16_t& op_code) {		// 2NNN
	stack[sp] = pc;
	sp++;
	pc = op_code & 0x0FFF;
}

void Chip8::SE_VxByte(const uint16_t& op_code) {		// 3xkk
	if (V[(op_code & 0x0F00) >> 8] == (op_code & 0x00FF))
		pc += 4;
	else
		pc += 2;
}

void Chip8::SNE_Vx_Byte(const uint16_t& op_code) {		// 4xkk
	if (V[(op_code & 0x0F00) >> 8] != (op_code & 0x00FF))
		pc += 4;
	else
		pc += 2;
}

void Chip8::SE_Vx_Vy(const uint16_t& op_code) {			// 5xy0
	if (V[(op_code & 0x0F00) >> 8] == V[(op_code & 0x00F0) >> 4])
		pc += 4;
	else
		pc += 2;
}

void Chip8::LD_Vx_Byte(const uint16_t& op_code) {		// 6xkk
	V[(op_code & 0x0F00) >> 8] = (op_code & 0x00FF);
	pc += 2;
}

void Chip8::ADD_Vx_Byte(const uint16_t& op_code) {		// 7xkk
	V[(op_code & 0x0F00) >> 8] += (op_code & 0x00FF);
	pc += 2;
}

void Chip8::LD_Vx_Vy(const uint16_t& op_code) {			// 8xy0
	V[(op_code & 0x0F00) >> 8] = V[(op_code & 0x00F0) >> 4];
	pc += 2;
}

void Chip8::OR_Vx_Vy(const const uint16_t& op_code) {	// 8xy1
	V[(op_code & 0x0F00) >> 8] |= V[(op_code & 0x00F0) >> 4];
	pc += 2;
}

void Chip8::AND_Vx_Vy(const uint16_t& op_code) {		// 8xy2
	V[(op_code & 0x0F00) >> 8] &= V[(op_code & 0x00F0) >> 4];
	pc += 2;
}

void Chip8::XOR_Vx_Vy(const uint16_t& op_code) {		// 8xy3
	V[(op_code & 0x0F00) >> 8] ^= V[(op_code & 0x00F0) >> 4];
	pc += 2;
}

void Chip8::ADD_Vx_Vy(const uint16_t& op_code) {		// 8xy4
	uint8_t x = (op_code & 0x0F00) >> 8;
	uint8_t y = (op_code & 0x00F0) >> 4;
	V[(op_code & 0x0F00) >> 8] = (V[x] + V[y]) & 0x00FF;
	V[0xF] = V[x] + V[y] > 0xFF ? 1 : 0;
	pc += 2;
}

void Chip8::SUB_Vx_Vy(const uint16_t& op_code) {		// 8xy5
	uint8_t x = (op_code & 0x0F00) >> 8;
	uint8_t y = (op_code & 0x00F0) >> 4;
	V[x] -= V[y];
	V[0xF] = V[y] > V[y] ? 0 : 1;
	pc += 2;
}

void Chip8::SHR_Vx_Vy(const uint16_t& op_code) {		// 8xy6
	uint8_t x = (op_code & 0x0F00) >> 8;
	uint8_t y = (op_code & 0x00F0) >> 4;
	V[x] = V[y] >> 1;
	V[x] /= 2;
	V[0xF] = V[x] & 0x1;
	pc += 2;
}

void Chip8::SUBN_Vx_Vy(const uint16_t& op_code) {		// 8xy7
	uint8_t x = (op_code & 0x0F00) >> 8;
	uint8_t y = (op_code & 0x00F0) >> 4;
	V[x] = V[y] - V[x];
	V[0xF] = V[x] > V[y] ? 0 : 1;
	pc += 2;
}

void Chip8::SHL_Vx_Vy(const uint16_t& op_code) {		// 8xyE
	uint8_t x = (op_code & 0x0F00) >> 8;
	uint8_t y = (op_code & 0x00F0) >> 4;
	V[x] = V[y] << 1;
	V[x] *= 2;
	V[0xF] = (V[x] & 0x10) >> 4;
	pc += 2;
}

void Chip8::SNE_Vx_Vy(const uint16_t& op_code) {		// 9xy0
	if (V[(op_code & 0x0F00) >> 8] != V[(op_code & 0x00F0) >> 4])
		pc += 4;
	else
		pc += 2;
}

void Chip8::LD_I_ADDR(const uint16_t& op_code) {		// ANNN
	I = op_code & 0x0FFF;
	pc += 2;
}

void Chip8::JP_V0_ADDR(const uint16_t& op_code) {		// BNNN
	pc = V[(op_code & 0x0F00) >> 8] + op_code & 0x0FFF;
}

void Chip8::RND_Vx_Byte(const uint16_t& op_code) {		// Cxkk
	V[(op_code & 0x0F00) >> 8] = distr(rng_eng) & (op_code & 0x00FF);
	pc += 2;
}

void Chip8::DRW_Vx_Vy_Nibble(const uint16_t& op_code) {	// Dxyn
	uint8_t x_pos = V[(op_code & 0x0F00) >> 8];
	uint8_t y_pos = V[(op_code & 0x00F0) >> 4];

	// The height of the sprite.
	uint8_t height = op_code & 0x000F;

	V[0xF] = 0;

	for (int dy = 0; dy < height; dy++) {
		uint8_t pixels = memory[I + dy];
		for (int dx = 0; dx < SPRITE_WIDTH; dx++) {
			if (pixels & (0x80 >> dx)) {
				int pixel_index = x_pos + dx + (y_pos + dy) * SCREEN_WIDTH;
				V[0xF] |= (uint8_t)gfx_buffer[pixel_index];
				gfx_buffer[pixel_index] ^= 1;
			}
		}
	}

	pc += 2;
	draw_flag = true;
}

void Chip8::SKP_Vx(const uint16_t& op_code) {			// Ex9E
	if (keypad_state[V[(op_code & 0x0F00) >> 8]])
		pc += 4;
	else
		pc += 2;
}

void Chip8::SKPN_Vx(const uint16_t& op_code) {			// ExA1
	if (!keypad_state[V[(op_code & 0x0F00) >> 8]])
		pc += 4;
	else
		pc += 2;
}

void Chip8::LD_Vx_DT(const uint16_t& op_code) {			// Fx07
	V[(op_code & 0x0F00) >> 8] = delay_timer;
	pc += 2;
}

void Chip8::LD_Vx_K(const uint16_t& op_code) {			// Fx0A
	if (waiting_for_keypress)
		for (int i = 0; i < KEY_COUNT; i++)
			if (keypad_state[i]) {
				V[(op_code & 0x0F00) >> 8] = i;
				waiting_for_keypress = false;
				pc += 2;
				return;
			}
	waiting_for_keypress = true;
}

void Chip8::LD_DT_Vx(const uint16_t& op_code) {			// Fx15
	delay_timer = V[(op_code & 0x0F00) >> 8];
	pc += 2;
}

void Chip8::LD_ST_Vx(const uint16_t& op_code) {			// Fx18
	sound_timer = V[(op_code & 0x0F00) >> 8];
	pc += 2;
}

void Chip8::ADD_I_Vx(const uint16_t& op_code) {			// Fx1E
	I += V[(op_code & 0x0F00) >> 8];
	V[0xF] = I >= MEMORY_SIZE;
	pc += 2;
}

void Chip8::LD_F_Vx(const uint16_t& op_code) {			// Fx29
	I = V[(op_code & 0x0F00) >> 8] * font_size;
	pc += 2;
}

void Chip8::LD_B_Vx(const uint16_t& op_code) {			// Fx33
	uint8_t Vx = V[(op_code & 0x0F00) >> 8];
	memory[I] = Vx / 100;
	memory[I + 1] = (Vx / 10) % 10;
	memory[I + 2] = Vx % 10;
	pc += 2;
}

void Chip8::LD_I_Vx(const uint16_t& op_code) {			// Fx55
	memcpy(&memory[I], V, ((op_code & 0x0F00) >> 8) + 1);
	pc += 2;
}

void Chip8::LD_Vx_I(const uint16_t& op_code) {			// Fx65
	memcpy(V, &memory[I], ((op_code & 0x0F00) >> 8) + 1);
	pc += 2;
}