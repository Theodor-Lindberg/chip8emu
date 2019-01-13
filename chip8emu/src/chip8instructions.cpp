#include "chip8.h"
#include <cstring>

OPCodes::OPCodes(Chip8& cpu) : chip8(cpu) { }

OPCodes::~OPCodes() { }

bool OPCodes::execute(uint16_t& op_code) {
	switch (op_code)
	{
	case 0x00E0:
		CLS();
	case 0x00EE:
		RET();
	default:
		return false;
	}
	return true;
}

void OPCodes::CLS() {
	std::memset(&chip8.gfx_buffer, 0, sizeof(chip8.gfx_buffer));
}

void OPCodes::RET() {

}