#include "program_options.hpp"

#include <sstream>
#include <stdexcept>

// program_options

program_options::program_options() :
	command(program_command::build)
{
}

std::string program_options::get_usage_text(std::string const & prog)
{
	std::stringstream s;

	s << "Usage: " << prog << " [OPTION]... [PROJECT] [COMMAND]" << std::endl;
	s << std::endl;
	s << "Execute COMMAND on a PROJECT." << std::endl;
	s << std::endl;
	s << "Parameters:" << std::endl;
	s << "PROJECT\t\troot directory of the project, default is current directory" << std::endl;
	s << "COMMAND\t\tthe command to execute, default is " << std::to_string(default_command) << std::endl;
	s << std::endl;
	s << "Available options:";

	return s.str();
}

program_options program_options::parse(std::vector<std::string> const & args)
{
	if (!args.size()) {
		throw std::invalid_argument("insufficient program's arguments");
	}

	program_options opt;

	opt.command_name = args[0];

	// optional options
	std::vector<std::string>::const_iterator it;

	for (it = args.begin() + 1; it != args.end(); it++) {
		auto & arg = *it;

		if (arg.compare(0, 2, "--")) {
			break;
		}

		throw bad_program_option(arg);
	}

	// project file
	if (it != args.end()) {
		opt.project_path = std::experimental::filesystem::canonical(*(it++));

		if (it != args.end()) {
			try {
				opt.command = from_string<program_command>(*(it++));
			} catch (...) {
				std::throw_with_nested(std::runtime_error("failed to parse command"));
			}
		} else {
			opt.command = default_command;
		}
	} else {
		opt.project_path = std::experimental::filesystem::current_path();
		opt.command = default_command;
	}

	return opt;
}

// bad_program_option

bad_program_option::bad_program_option(std::string const & opt) :
	std::runtime_error("unknown option " + opt),
	opt(opt)
{
}

// functions

std::string std::to_string(::program_command c)
{
	switch (c) {
	case ::program_command::build:
		return "build";
	default:
		throw std::invalid_argument("command is not valid");
	}
}
