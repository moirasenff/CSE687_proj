#include <string>
#include <vector>

#pragma once

class FileManager {
public:
	std::vector<std::string> read(std::string directory, int key = 0);
};
