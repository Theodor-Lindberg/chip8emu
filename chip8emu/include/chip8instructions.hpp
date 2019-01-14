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

	/// <summary> Clear the display. </summary>
	void CLS();

	/// <summary> Return from a subroutine. </summary>
	void RET();

	/// <summary> Jump to address. </summary>
	/// <param name="address"> The address to jump to. </param>
	void JP_ADDR(uint16_t address);

	/// <summary> Call subroutine at address. </summary>
	/// <param name="adress"> The address of the subroutine. </param>
	void CALL_ADDR(uint16_t address);

	/// <summary> Skip next instruction if Vx equals the last byte. </summary>
	/// <param name="adress"> The whole operation code. </param>
	void SE_VxByte(uint16_t& op_code);

	/// <summary> Skip next instruction if Vx does not equal the last byte. </summary>
	/// <param name="adress"> The operation code. </param>
	void SNE_Vx_Byte(uint16_t& op_code);

	/// <summary> Skip next instruction if Vx equals Vy. </summary>
	/// <param name="adress"> The operation code. </param>
	void SE_Vx_Vy(uint16_t& op_code);
};

#endif // !CHIP8_INSTRUCTIONS