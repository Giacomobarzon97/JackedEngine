#pragma once

#include <vector>
#include <fstream>

class FileIO {
public:
	FileIO() = delete;
	FileIO(FileIO&) = delete;
	FileIO &operator=(FileIO &) = delete;

	static std::vector<char> readFile(const std::string& filename);
};