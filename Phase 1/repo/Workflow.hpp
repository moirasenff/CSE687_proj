#include <string>
#include <iostream>
#include <sys/stat.h>
#include <boost/log/trivial.hpp>
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <filesystem>

#pragma once

struct Workflow {
	// params: input dir, temp dir, output dir
	// returns: pass/fail bool
	static bool run(std::string, std::string, std::string);
};