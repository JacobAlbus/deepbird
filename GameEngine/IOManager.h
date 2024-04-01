#pragma once

#include <vector>
#include <string>

namespace GameEngine {

	class IOManager {

	public:
		static bool ReadFileToBuffer(const std::string& file_path, std::vector<unsigned char>& buffer);
	};

}