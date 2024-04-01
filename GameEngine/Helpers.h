#pragma once

#include "Errors.h"

#include <cstdlib>
#include <filesystem>
#include <SDL/SDL.h>
#include <string>
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

namespace GameEngine {

	class Helpers {

	public:
		static std::string ReadFile(const std::string& file_path) {
			std::ifstream file(file_path);
			if (file.fail()) {
				perror(file_path.c_str());
				FatalError("Failed to open a " + file_path);
			}

			std::string file_contents;
			std::string line;

			while (std::getline(file, line)) {
				file_contents += line + "\n";
			}

			file.close();

			return file_contents;
		}

		static void FatalError(std::string error_string) {
			std::cout << error_string << std::endl;
			std::cout << "Press any key to quit..." << std::endl;

			int temp;
			std::cin >> temp;
			SDL_Quit();
			exit(42);
		}
	};

}