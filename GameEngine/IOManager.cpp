#include "IOManager.h"

#include <fstream>

namespace GameEngine {

	bool IOManager::ReadFileToBuffer(const std::string& file_path, std::vector<unsigned char>& buffer) {

		std::ifstream file(file_path, std::ios::binary);

		if (file.fail()) {
			perror(file_path.c_str());
			return false;
		}

		// Seek to end of file, grab size, then seek to beginning
		file.seekg(0, std::ios::end);

		int file_size = file.tellg();

		file.seekg(0, std::ios::beg);

		// Rmove header bytes from file size
		file_size -= file.tellg();

		buffer.resize(file_size);
		file.read((char*)&(buffer[0]), file_size);
		file.close();

		return true;
	}

}