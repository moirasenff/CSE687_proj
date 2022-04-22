#include "FileManager.hpp"
#include <fstream>
#include <boost/log/trivial.hpp>

std::vector<std::string> FileManager::read(std::string directory, int key) {
	std::vector<std::string> retVect;
	std::string filePathName = directory;
	filePathName += "/file";
	filePathName += std::to_string(key);
	filePathName += ".txt";
	BOOST_LOG_TRIVIAL(info) << "file path: " << filePathName;
	std::ifstream file(filePathName);
	std::string line;
	while (std::getline(file, line))
	{
		retVect.push_back(line);
	}
	return retVect;
}