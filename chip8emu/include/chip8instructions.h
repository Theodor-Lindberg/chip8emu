#ifndef CHIP8_INSTRUCTIONS
#define CHIP8_INSTRUCTIONS

#include <cstdint>

class Chip8;

class OPCodes {
public:
	OPCodes(Chip8& cpu);
	~OPCodes();

	/// <summary> Execute instruction based on operation code </summary>
	/// <remarks> A switch is used instead a map or array of function pointers
	/// so that the compiler can optimize it into a faster lookup table. </remarks>
	/// <param name="op_code"> The code of the instruction </param>
	/// <returns> If the function succeeds true is returned, otherwise false. </returns>
	bool execute(uint16_t& op_code);

private:
	Chip8& chip8;

	///<summary> Clear the display. </summary>
	void CLS();

	///<summary> Return from a subroutine. </summary>
	void RET();
};

#endif // !CHIP8_INSTRUCTIONS