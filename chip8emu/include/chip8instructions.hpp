#ifndef CHIP8_INSTRUCTIONS
#define CHIP8_INSTRUCTIONS

#include <cstdint>

/// <summary> Clear the display. </summary>
void CLS();

/// <summary> Return from a subroutine. </summary>
void RET();

/// <summary> Jump to address. </summary>
/// <param name="op_code"> The operation code. </param>
void JP_ADDR(uint16_t& op_code);

/// <summary> Call subroutine at address. </summary>
/// <param name="op_code"> The operation code. </param>
void CALL_ADDR(uint16_t& op_code);

/// <summary> Skip next instruction if the value of register Vx equals the last byte. </summary>
/// <param name="op_code"> The operation code. </param>
void SE_VxByte(uint16_t& op_code);

/// <summary> Skip next instruction if the value of register Vx does not equal the last byte. </summary>
/// <param name="op_code"> The operation code. </param>
void SNE_Vx_Byte(uint16_t& op_code);

/// <summary> Skip next instruction if value of register Vx equals to the value of register Vy. </summary>
/// <param name="op_code"> The operation code. </param>
void SE_Vx_Vy(uint16_t& op_code);

/// <summary> Set Vx to the last byte. </summary>
/// <param name="op_code"> The operation code. </param>
void LD_Vx_Byte(uint16_t& op_code);

/// <summary> Add the value of the last byte to the value of register Vx. </summary>
/// <param name="op_code"> The operation code. </param>
void ADD_Vx_Byte(uint16_t& op_code);

/// <summary> Set the value of register Vx to the value of register Vy. </summary>
/// <param name="op_code"> The operation code. </param>
void LD_Vx_Vy(uint16_t& op_code);

/// <summary> Performs a bitwise OR on the values of register Vx and Vy, then stores the result in Vx. </summary>
/// <param name="op_code"> The operation code. </param>
void OR_Vx_Vy(uint16_t& op_code);

/// <summary> Performs a bitwise AND on the values of register Vx and Vy, then stores the result in Vx. </summary>
/// <param name="op_code"> The operation code. </param>
void AND_Vx_Vy(uint16_t& op_code);

/// <summary> Performs a bitwise XOR on the values of register Vx and Vy, then stores the result in Vx. </summary>
/// <param name="op_code"> The operation code. </param>
void XOR_Vx_Vy(uint16_t& op_code);

/// <summary> Add the values of register Vx and Vy and store the result in Vx, 
/// if the result is greater than one byte the carry flag VF is set 1 otherwise 0. </summary>
/// <param name="op_code"> The operation code. </param>
void ADD_Vx_Vy(uint16_t& op_code);

/// <summary> Substract the value of register Vx with the value of register Vy and store the result in Vx, 
/// if the value of Vy is greater than the value of Vx the carry flag VF is set 0 otherwise 1. </summary>
/// <param name="op_code"> The operation code. </param>
void SUB_Vx_Vy(uint16_t& op_code);

/// <summary> Shift the value of register Vy one bit right and store the result in Vx, 
/// set register VF to the least significant bit prior to the shift and then divide Vx by 2. </summary>
/// <param name="op_code"> The operation code. </param>
void SHR_Vx_Vy(uint16_t& op_code);

/// <summary> Substract the value of register Vy with the value of register Vx and store the result in Vx, 
/// if the value of Vx is greater than the value of Vy the carry flag VF is set 0 otherwise 1. </summary>
void SUBN_Vx_Vy(uint16_t& op_code);

/// <summary> Shift the value of register Vy one bit left and store the result in Vx, 
/// set register VF to the most significant bit prior to the shift and the multiply Vx by 2. </summary>
/// <param name="op_code"> The operation code. </param>
void SHL_Vx_Vy(uint16_t& op_code);

/// <summary> Skip next instruction if the value of register Vx does not equal the value of register Vy. </summary>
/// <param name="op_code"> The operation code. </param>
void SNE_Vx_Vy(uint16_t& op_code);

/// <summary> Set the value of register I to the last 12 bits of the operation code. </summary>
/// <param name="op_code"> The operation code. </param>
void LD_I_ADDR(uint16_t& op_code);

/// <summary> Jump to the address the value of register Vx plus the last 12 bits op the operation code. </summary>
/// <param name="op_code"> The operation code. </param>
void JP_V0_ADDR(uint16_t& op_code);

/// <summary> Generate a random number and perform a logical AND with the last byte of the operation code. </summary>
/// <param name="op_code"> The operation code. </param>
void RND_Vx_Byte(uint16_t& op_code);

/// <summary> Display n-byte sprite starting at memory location I at (Vx, Vy), set VF if there was a collision. </summary>
/// <param name="op_code"> The operation code. </param>
void DRW_Vx_Vy_Nibble(uint16_t& op_code);

/// <summary> Skip the next instruction if the key with the value of register Vx is pressed. </summary>
/// <param name="op_code"> The operation code. </param>
void SKP_Vx(uint16_t& op_code);

/// <summary> Skip the next instruction if the key with the value of register Vx is not pressed. </summary>
/// <param name="op_code"> The operation code. </param>
void SKPN_Vx(uint16_t& op_code);

/// <summary> Set the delay timer to the value of register Vx. </summary>
/// <param name="op_code"> The operation code. </param>
void LD_Vx_DT(uint16_t& op_code);

/// <summary> Wait for a key press, store the value of the key in Vx. </summary>
/// <param name="op_code"> The operation code. </param>
void LD_Vx_K(uint16_t& op_code);

/// <summary> Set the delay timer to the value of register Vx. </summary>
/// <param name="op_code"> The operation code. </param>
void LD_DT_Vx(uint16_t& op_code);

/// <summary> Set the sound timer to the value of register Vx. </summary>
/// <param name="op_code"> The operation code. </param>
void LD_ST_Vx(uint16_t& op_code);

/// <summary> Add the value of register Vx the index register. </summary>
/// <param name="op_code"> The operation code. </param>
void ADD_I_Vx(uint16_t& op_code);

/// <summary> The value of I is set to the location for the hexadecimal sprite,
/// corresponding to the value of Vx. </summary>
/// <param name="op_code"> The operation code. </param>
void LD_F_Vx(uint16_t& op_code);

/// <summary> Take the decimal value of Vx, and places the hundreds digit in memory at location in I,
/// the tens digit at location I+1, and the ones digit at location I+2.</summary>
/// <param name="op_code"> The operation code. </param>
void LD_B_Vx(uint16_t& op_code);

/// <summary> Store registers V0 through Vx in memory starting at location I. </summary>
/// <param name="op_code"> The operation code. </param>
void LD_I_Vx(uint16_t& op_code);
	
/// <summary> Read registers V0 through Vx from memory starting at location I. </summary>
/// <param name="op_code"> The operation code. </param>
void LD_Vx_I(uint16_t& op_code);

#endif // !CHIP8_INSTRUCTIONS