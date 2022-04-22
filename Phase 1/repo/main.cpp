#include "FileManager.hpp"
#include "Workflow.hpp"
#include <boost/test/unit_test.hpp>
int main(int argc, char* argv[]) {
	if (argc != 4) {
		BOOST_LOG_TRIVIAL(error) << "Malformed arguments! Please run <executable> <input dir> <temp dir> <output dir>";
		return -1;
	}
	std::string input = argv[1];
	std::string temp = argv[2];
	std::string output = argv[3];
	// check if input is a valid directory
	struct stat buffer;
	if (stat(input.c_str(), &buffer) != 0) {
		BOOST_LOG_TRIVIAL(error) << input << " directory does not exist!";
		return -1;
	}
	else {
		// make new directories
		// _mkdir(temp.c_str());
		_mkdir(output.c_str());
		// clean them in case they already exist
		//for (const auto& entry : std::filesystem::directory_iterator(temp)) {
		//	std::filesystem::remove_all(entry.path());
		//}
		for (const auto& entry : std::filesystem::directory_iterator(output)) {
			std::filesystem::remove_all(entry.path());
		}
	}
	Workflow wf;
	// if checks pass, dirs are valid, pass them off to the workflow
	if (!wf.run(input, temp, output)) {
		BOOST_LOG_TRIVIAL(error) << "Workflow failed to complete!";
		return -1;
	}
}