#ifndef CHIP8_INSTRUCTIONS
#define CHIP8_INSTRUCTIONS

#include <cstdint>
#include <random>

class Chip8;

class OPCodes {
public:
	OPCodes(Chip8& cpu);
	~OPCodes();

	/// <summary> Execute instruction based on operation code </summary>
	/// <remarks> A switch is used instead of a map or array of function pointers
	/// so that the compiler can optimize it into a faster lookup table. </remarks>
	/// <param name="op_code"> The code of the instruction </param>
	/// <returns> If the function succeeds true is returned, otherwise false. </returns>
	bool execute(uint16_t& op_code);

private:
	Chip8& chip8;

	std::mt19937 rng_eng { std::random_device()() };
	std::uniform_int_distribution<uint16_t> distr { 0, 0xFF };

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

	/// <summary> Skip next instruction if the value of register Vx equals the last byte. </summary>
	/// <param name="adress"> The whole operation code. </param>
	void SE_VxByte(uint16_t& op_code);

	/// <summary> Skip next instruction if the value of register Vx does not equal the last byte. </summary>
	/// <param name="adress"> The operation code. </param>
	void SNE_Vx_Byte(uint16_t& op_code);

	/// <summary> Skip next instruction if value of register Vx equals to the value of register Vy. </summary>
	/// <param name="adress"> The operation code. </param>
	void SE_Vx_Vy(uint16_t& op_code);

	/// <summary> Set Vx to the last byte. </summary>
	/// <param name="adress"> The operation code. </param>
	void LD_Vx_Byte(uint16_t& op_code);

	/// <summary> Add the value of the last byte to the value of register Vx. </summary>
	/// <param name="adress"> The operation code. </param>
	void ADD_Vx_Byte(uint16_t& op_code);

	/// <summary> Set the value of register Vx to the value of register Vy. </summary>
	/// <param name="adress"> The operation code. </param>
	void LD_Vx_Vy(uint16_t& op_code);

	/// <summary> Performs a bitwise OR on the values of register Vx and Vy, then stores the result in Vx. </summary>
	/// <param name="adress"> The operation code. </param>
	void OR_Vx_Vy(uint16_t& op_code);

	/// <summary> Performs a bitwise AND on the values of register Vx and Vy, then stores the result in Vx. </summary>
	/// <param name="adress"> The operation code. </param>
	void AND_Vx_Vy(uint16_t& op_code);

	/// <summary> Performs a bitwise XOR on the values of register Vx and Vy, then stores the result in Vx. </summary>
	/// <param name="adress"> The operation code. </param>
	void XOR_Vx_Vy(uint16_t& op_code);

	/// <summary> Add the values of register Vx and Vy and store the result in Vx, 
	/// if the result is greater than one byte the carry flag VF is set 1 otherwise 0. </summary>
	/// <param name="adress"> The operation code. </param>
	void ADD_Vx_Vy(uint16_t& op_code);

	/// <summary> Substract the value of register Vx with the value of register Vy and store the result in Vx, 
	/// if the value of Vy is greater than the value of Vx the carry flag VF is set 0 otherwise 1. </summary>
	/// <param name="adress"> The operation code. </param>
	void SUB_Vx_Vy(uint16_t& op_code);

	/// <summary> Shift the value of register Vy one bit right and store the result in Vx, 
	/// set register VF to the least significant bit prior to the shift and then divide Vx by 2. </summary>
	/// <param name="adress"> The operation code. </param>
	void SHR_Vx_Vy(uint16_t& op_code);

	/// <summary> Substract the value of register Vy with the value of register Vx and store the result in Vx, 
	/// if the value of Vx is greater than the value of Vy the carry flag VF is set 0 otherwise 1. </summary>
	/// <param name="adress"> The operation code. </param>
	void SUBN_Vx_Vy(uint16_t& op_code);

	/// <summary> Shift the value of register Vy one bit left and store the result in Vx, 
	/// set register VF to the most significant bit prior to the shift and the multiply Vx by 2. </summary>
	/// <param name="adress"> The operation code. </param>
	void SHL_Vx_Vy(uint16_t& op_code);

	/// <summary> Skip next instruction if the value of register Vx does not equal the value of register Vy. </summary>
	/// <param name="adress"> The operation code. </param>
	void SNE_Vx_Vy(uint16_t& op_code);

	/// <summary> Set the value of register I to the last 12 bits of the operation code. </summary>
	/// <param name="adress"> The operation code. </param>
	void LD_I_ADDR(uint16_t& op_code);

	/// <summary> Jump to the address the value of register Vx plus the last 12 bits op the operation code. </summary>
	/// <param name="adress"> The operation code. </param>
	void JP_V0_ADDR(uint16_t& op_code);

	/// <summary> Generate a random number and perform a logical AND with the last byte of the operation code. </summary>
	/// <param name="adress"> The operation code. </param>
	void RND_Vx_Byte(uint16_t& op_code);

	/// <summary> Display n-byte sprite starting at memory location I at (Vx, Vy), set VF if there was a collision. </summary>
	/// <param name="adress"> The operation code. </param>
	void DRW_Vx_Vy_Nibble(uint16_t& op_code);
};

#endif // !CHIP8_INSTRUCTIONS