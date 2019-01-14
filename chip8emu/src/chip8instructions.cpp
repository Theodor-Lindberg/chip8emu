#include "chip8.hpp"
#include <cstring>

OPCodes::OPCodes(Chip8& cpu) : chip8(cpu) { }

OPCodes::~OPCodes() { }

bool OPCodes::execute(uint16_t& op_code) {
	switch (op_code & 0xF000)
	{
	case 0x0000:
		switch (op_code)
		{
		case 0x00E0:
			CLS();
			break;
		case 0x00EE:
			RET();
			break;
		default:
			return false;
		}
	case 0x1000:						// 1NNN
		JP_ADDR(op_code & 0x0FFF);
		break;
	case 0x2000:						// 2NNN
		CALL_ADDR(op_code & 0x0FFF);
		break;
	case 0x3000:						// 3xkk
		SE_VxByte(op_code);
		break;
	case 0x4000:						// 4xkk
		SNE_Vx_Byte(op_code);
		break;
	case 0x5000:

	default:
		return false;
	}
	return true;
}

void OPCodes::CLS() {
	std::memset(&chip8.gfx_buffer, 0, sizeof(chip8.gfx_buffer));
	chip8.pc += 2;
}

void OPCodes::RET() {
	chip8.sp--;
	chip8.pc = chip8.stack[chip8.sp];
	chip8.pc += 2;
}

void OPCodes::JP_ADDR(uint16_t address) {
	chip8.pc = address;
	chip8._draw_flag = true;
}

void OPCodes::CALL_ADDR(uint16_t address) {
	chip8.sp++;
	chip8.stack[chip8.sp] = chip8.pc;
	chip8.pc = address;
}

void OPCodes::SE_VxByte(uint16_t& op_code) {
	if (chip8.V[(op_code & 0x0F00) >> 8] == (op_code & 0x00FF))
		chip8.pc += 4;
	else
		chip8.pc += 2;
}

void OPCodes::SNE_Vx_Byte(uint16_t& op_code) {
	if (chip8.V[(op_code & 0x0F00) >> 8] != (op_code & 0x00FF))
		chip8.pc += 4;
	else
		chip8.pc += 2;
}

void OPCodes::SE_Vx_Vy(uint16_t& op_code) {
	if (chip8.V[(op_code & 0x0F00) >> 8] == chip8.V[(op_code & 0x00F0) >> 8])
		chip8.pc += 4;
	else
		chip8.pc += 2;
}