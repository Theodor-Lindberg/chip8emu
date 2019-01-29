#include "filehelper.hpp"
#include <iostream>
#include <fstream>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

bool FileHelper::load_binaries(const char* file_path, Chip8& chip8) {
	std::ifstream file(file_path, std::ios::binary | std::ios::ate);

	if (file.bad()) {
		std::cerr << "Error: could not open file." << std::endl;
		std::cerr << "Error code: " << strerror(errno) << std::endl;
		return false;
	}

	size_t len = file.tellg();

	char* buffer = new char[len];
	file.seekg(0, std::ios::beg);
	file.read(buffer, len);

	if (file.bad())
	{
		std::cerr << "Error: could not read file." << std::endl;
		std::cerr << "Error code: " << strerror(errno) << std::endl;
		return false;
	}
	file.close();

	bool result = chip8.load_rom((uint8_t*)buffer, len);
	delete[] buffer;
	return result;
}