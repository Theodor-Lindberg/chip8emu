#include "chip8.h"
#include <cstring>

OPCodes::OPCodes(Chip8& cpu) : chip8(cpu) { }

OPCodes::~OPCodes() { }

bool OPCodes::execute(uint16_t& op_code) {
	switch (get_op(op_code))
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
		JP_ADDR(get_data(op_code));
		break;
	case 0x2000:						// 2NNN
		CALL_ADDR(get_data(op_code));
		break;
	default:
		return false;
	}
	return true;
}

uint16_t OPCodes::get_op(uint16_t op_code) {
	return op_code & 0xF000;
}

uint16_t OPCodes::get_data(uint16_t op_code) {
	return op_code & 0x0FFF;
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