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

	/// <summary> Get the code of the operation. </summary>
	/// <param name="op_code"> The operation code to analyze. </param>
	///<returns> The first 4 bits which represent the code. </returns>
	uint16_t get_op(uint16_t op_code);

	/// <summary> Get the code of the operation. </summary>
	/// <param name="op_code"> The operation code to analyze. </param>
	///<returns> The first 4 bits which represent the code. </returns>
	uint16_t get_data(uint16_t);

	/// <summary> Clear the display. </summary>
	void CLS();

	/// <summary> Return from a subroutine. </summary>
	void RET();

	/// <summary> Jump to address. </summary>
	/// <param name="address"> The address to jump to. </param>
	void JP_ADDR(uint16_t address);

	/// <summary> Call subroutine at address. </summary>
	/// <param name="address"> The address to make a call to. </param>
	void CALL_ADDR(uint16_t address);
};

#endif // !CHIP8_INSTRUCTIONS