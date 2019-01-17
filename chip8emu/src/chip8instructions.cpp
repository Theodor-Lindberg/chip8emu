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
	case 0x5000:						// 5xy0
		SE_Vx_Vy(op_code);
		break;
	case 0x6000:						// 6xkk
		LD_Vx_Byte(op_code);
		break;
	case 0x7000:						// 7xkk
		ADD_Vx_Byte(op_code);
		break;
	case 0x8000:						// 8xyN
		switch (op_code & 0x000F)
		{
		case 0x0000:
			LD_Vx_Vy(op_code);
			break;
		case 0x0001:
			OR_Vx_Vy(op_code);
			break;
		case 0x0002:
			AND_Vx_Vy(op_code);
			break;
		case 0x0003:
			XOR_Vx_Vy(op_code);
			break;
		case 0x0004:
			ADD_Vx_Vy(op_code);
			break;
		case 0x0005:
			SUB_Vx_Vy(op_code);
			break;
		case 0x0006:
			SHR_Vx_Vy(op_code);
			break;
		case 0x0007:
			break;
		case 0x000E:
			break;
		default:
			return false;
		}
	case 0x9000:						// 9xy0
		break;
	case 0xA000:						// ANNN
		break;
	case 0xB000:						// BNNN
		break;
	case 0xC000:						// Cxkk
		break;
	case 0xD000:						// Dxyn
		break;
	case 0xE000:						// Ex
		switch (op_code & 0x00FF)
		{
		case 0x009E:
			break;
		case 0x00A1:
			break;
		default:
			return false;
		}
	case 0xF000:						// Fx
		switch (op_code & 0x00FF)
		{
		case 0x0007:
			break;
		case 0x000A:
			break;
		case 0x0015:
			break;
		case 0x0018:
			break;
		case 0x001E:
			break;
		case 0x0029:
			break;
		case 0x0033:
			break;
		case 0x0055:
			break;
		case 0x0065:
			break;
		default:
			return false;
		}
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
	if (chip8.V[(op_code & 0x0F00) >> 8] == chip8.V[(op_code & 0x00F0) >> 4])
		chip8.pc += 4;
	else
		chip8.pc += 2;
}

void OPCodes::LD_Vx_Byte(uint16_t& op_code) {
	chip8.V[(op_code & 0x0F00) >> 8] = (op_code & 0x00FF);
	chip8.pc += 2;
}

void OPCodes::ADD_Vx_Byte(uint16_t& op_code) {
	chip8.V[(op_code & 0x0F00) >> 8] += (op_code & 0x00FF);
	chip8.pc += 2;
}

void OPCodes::LD_Vx_Vy(uint16_t& op_code) {
	chip8.V[(op_code & 0x0F00) >> 8] = chip8.V[(op_code & 0x00F0) >> 4];
	chip8.pc += 2;
}

void OPCodes::OR_Vx_Vy(uint16_t& op_code) {
	chip8.V[(op_code & 0x0F00) >> 8] |= chip8.V[(op_code & 0x00F0) >> 4];
	chip8.pc += 2;
}

void OPCodes::AND_Vx_Vy(uint16_t& op_code) {
	chip8.V[(op_code & 0x0F00) >> 8] &= chip8.V[(op_code & 0x00F0) >> 4];
	chip8.pc += 2;
}

void OPCodes::XOR_Vx_Vy(uint16_t& op_code) {
	chip8.V[(op_code & 0x0F00) >> 8] ^= chip8.V[(op_code & 0x00F0) >> 4];
	chip8.pc += 2;
}

void OPCodes::ADD_Vx_Vy(uint16_t& op_code) {
	uint8_t x = (op_code & 0x0F00) >> 8;
	uint8_t y = (op_code & 0x00F0) >> 4;
	chip8.V[(op_code & 0x0F00) >> 8] = (chip8.V[x] + chip8.V[y]) & 0x00FF;
	chip8.V[0xF] = chip8.V[x] + chip8.V[y] > 0xFF ? 1 : 0;
	chip8.pc += 2;
}

void OPCodes::SUB_Vx_Vy(uint16_t& op_code) {
	uint8_t x = (op_code & 0x0F00) >> 8;
	uint8_t y = (op_code & 0x00F0) >> 4;
	chip8.V[x] -= chip8.V[y];
	chip8.V[0xF] = chip8.V[y] > chip8.V[y] ? 0 : 1;
	chip8.pc += 2;
}

void OPCodes::SHR_Vx_Vy(uint16_t& op_code) {
	uint8_t x = (op_code & 0x0F00) >> 8;
	uint8_t y = (op_code & 0x00F0) >> 4;
	chip8.V[x] = chip8.V[y] >> 1;
	chip8.V[0xF] = chip8.V[x] & 0x0F;
	chip8.pc += 2;
}

void OPCodes::SUBN_Vx_Vy(uint16_t& op_code) {
	uint8_t x = (op_code & 0x0F00) >> 8;
	uint8_t y = (op_code & 0x00F0) >> 4;
	chip8.V[x] = chip8.V[y] - chip8.V[x];
	chip8.V[0xF] = chip8.V[x] > chip8.V[y] ? 0 : 1;
	chip8.pc += 2;
}