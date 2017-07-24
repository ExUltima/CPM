#include "program.hpp"

#include "exception.hpp"

#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
	std::vector<std::string> args;
	std::copy(argv, &argv[argc], std::back_inserter(args));

	try {
		program::run(args);
	} catch (std::exception & e) {
		std::cerr << std::to_string(e) << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
