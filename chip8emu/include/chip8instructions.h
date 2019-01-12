#ifndef CHIP8_INSTRUCTIONS
#define CHIP8_INSTRUCTIONS

class Chip8;

class OPCodes {
public:
	OPCodes(Chip8 &c);
	~OPCodes();
	void execute_instruction();
private:
	Chip8& chip8;
	void CLS();
};

#endif // !CHIP8_INSTRUCTIONS