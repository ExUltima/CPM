#include "exception.hpp"
#include "program.hpp"

#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
	try {
		// convert argv to vector
		std::vector<std::string> args;
		std::copy(argv, &argv[argc], std::back_inserter(args));

		// run
		program prog;
		prog.run(args);
	} catch (std::exception & e) {
		std::cerr << std::to_string(e) << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
