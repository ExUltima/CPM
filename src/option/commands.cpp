#include "commands.hpp"

#include <stdexcept>

std::string std::to_string(::program_command c)
{
	switch (c) {
	case ::program_command::build:
		return "build";
	default:
		throw invalid_argument("command is not valid");
	}
}
