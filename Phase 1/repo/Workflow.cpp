#include "Workflow.hpp"
#include "FileManager.hpp"
#include "Reducer.hpp"

bool Workflow::run(std::string inDir, std::string tempDir, std::string outDir) {
	BOOST_LOG_TRIVIAL(info) << "Starting workflow.";
	
	int keyCounter = 0;

	FileManager fileMgr;
	//Mapper mapper;
	//std::vector<std::string> inVect = fileMgr.read(inDir);

	//for (int i = 0; i < inVect.size(); i++) {
	//	// for each file in the inDirectory
	//	mapper.map(keyCounter, inVect.at(i), tempDir);
	//	// temp dir had intermediate files in it. now read it back in
	//	std::vector<std::string> tempVect = fileMgr.read(tempDir, keyCounter);
	//	std::vector<std::string> sortedVect = sort(tempVect);

	//}

	// testing 4/22
	// I am assuming there are valid contents in the temp directory. We still need to map from the
	// input directory to the temp directory
	std::vector<std::string> tempVect = fileMgr.read(tempDir, keyCounter);
	Trie* head = sort(tempVect);

	// trie is populated with string values. pump them out to the vector
	Reducer reducer(outDir);
	if (reducer.reduce(head, outDir, 0)) {
		BOOST_LOG_TRIVIAL(info) << "SUCCESS";
		return true;
	}
	else {
		BOOST_LOG_TRIVIAL(info) << "FAILURE";
		return false;
	}
}

Trie* Workflow::sort(std::vector<std::string> inVect) {
	std::vector<std::string> retVect;
	Trie* head = new Trie();

	for (int i = 0; i < inVect.size(); i++) {
		std::string line = inVect.at(i);
		std::string::size_type start_pos = line.find("\"");
		std::string::size_type end_pos;
		if (start_pos != std::string::npos) {
			end_pos = line.find("\"", start_pos + 1);
			// get the word without quotes
			std::string word = line.substr(start_pos + 1, end_pos - 1);
			// populate the trie
			if (head->search(word) == 0) {
				// this is a new word
				head->insert(word);
			}
			else {
				// word already existed. increment the count
				head->increment(word);
			}
		}
		else {
			BOOST_LOG_TRIVIAL(error) << "Malformed temp directory found in sorted()";
		}
	}
	return head;
}