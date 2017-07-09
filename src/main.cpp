#include "program.hpp"

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
	std::vector<std::string> args;
	std::copy(argv, &argv[argc], std::back_inserter(args));

	return program::run(args);
}
