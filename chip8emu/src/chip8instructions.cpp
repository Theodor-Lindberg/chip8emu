#include <cstring>
#include "chip8.h"

OPCodes::OPCodes(Chip8 &c) : chip8(c) { 
		
}

OPCodes::~OPCodes() { }

void OPCodes::execute_instruction() {
	if (chip8.memory[0] == 1) {
		chip8.memory[0] = 3;
	}
}

void OPCodes::CLS() {
}