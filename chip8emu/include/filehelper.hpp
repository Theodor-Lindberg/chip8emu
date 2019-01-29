#ifndef FILE_HELPER
#define FILE_HELPER

#include "chip8.hpp"

namespace FileHelper {
	bool load_binaries(const char* file_path, Chip8& chip8);
}

#endif // !FILE_HELPER
