#include "Trie.hpp"

#pragma once

class Reducer {
	// exports key and value to a file
	void write(std::string, std::string, int);
	std::string mOutDir;
public:
	// constructor takes in the out path
	Reducer(std::string);
	// reduces the trie into a word and key (quantity) and calls export
	bool reduce(Trie*, std::string, int);

};