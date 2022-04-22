#include "Reducer.hpp"
#include "fstream"

Reducer::Reducer(std::string dir) {
	mOutDir = dir;
}

bool Reducer::reduce(Trie* head, std::string outPath, int key) {
	while (head->isLeaf == false) {
		// this cleans up the trie and pops off all the words and quantities
		std::tuple<std::string, int> val = head->pop();
		std::string s = "\"" + std::get<0>(val) + "\"" + ", " + std::to_string(std::get<1>(val)) + "\n";
		write(s, outPath, key);
	}
	return true;
}

void Reducer::write(std::string word, std::string path, int key) {
	// TODO this needs to happen in the filesystem class
	std::ofstream outFile;
	outFile.open(std::string(path + "/file" + std::to_string(key) + ".txt"), std::ios_base::app);
	outFile << word;
	outFile.close();
}