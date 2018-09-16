#ifndef OPTION_OPTIONAL_PARSERS_HPP_INCLUDED
#define OPTION_OPTIONAL_PARSERS_HPP_INCLUDED

#include "options.hpp"

#include <functional>
#include <map>
#include <string>
#include <vector>

struct optional_option_argument_descriptor {
	std::string name;
	bool required;
};

struct optional_option_descriptor {
	std::string description;
	std::function<void(program_options &, std::vector<std::string> const &)> parser;
	std::vector<optional_option_argument_descriptor> args;
};

struct optional_option_usage {
	std::string usage;
	std::string description;
};

extern std::map<std::string, optional_option_descriptor> const optional_option_descriptors;

std::vector<optional_option_usage> get_optional_option_usages(std::string const &prefix);

#endif // OPTION_OPTIONAL_PARSERS_HPP_INCLUDED
