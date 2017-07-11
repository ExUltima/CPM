#include "program.hpp"

#include <cstdlib>
#include <iostream>

program program::curr;

program::program()
{
}

int program::run(std::vector<std::string> const & args)
{
	try {
		curr.opts = program_options::parse(args);
	} catch (bad_program_option & e) {
		if (e.option() == "--help") {
			std::cout << program_options::get_usage_text(args[0]) << std::endl;
			return EXIT_SUCCESS;
		}

		throw;
	}

	return EXIT_SUCCESS;
}
