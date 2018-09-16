#ifndef OPTION_COMMANDS_HPP_INCLUDED
#define OPTION_COMMANDS_HPP_INCLUDED

#include "../string.hpp"

#include <stdexcept>
#include <string>

enum class program_command {
	build
};

template<>
program_command from_string<program_command>(std::string const &s);

namespace std {
string to_string(::program_command c);
}

template<>
inline program_command from_string<program_command>(std::string const &s)
{
	if (s == "build") {
		return program_command::build;
	} else {
		throw std::invalid_argument("command string is not valid");
	}
}

#endif // OPTION_COMMANDS_HPP_INCLUDED
