#ifndef OPTION_OPTIONS_HPP_INCLUDED
#define OPTION_OPTIONS_HPP_INCLUDED

#include "commands.hpp"

#include <string>
#include <vector>

class program_options final {
public:
	static program_command const default_command = program_command::build;
	static std::string const optional_prefix;

	program_command command;
	std::string command_name;
	std::string platform;
	std::string project_path;

	program_options();

	static std::string get_usage_text(std::string const &prog);
	static program_options parse(std::vector<std::string> const &args);

	static void parse_platform(program_options &o, std::vector<std::string> const &args);
};

#endif // OPTION_OPTIONS_HPP_INCLUDED
