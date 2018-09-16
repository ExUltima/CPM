#include "options.hpp"
#include "commands.hpp"
#include "errors.hpp"
#include "optionals.hpp"
#include "../filesystem.hpp"
#include "../string.hpp"

#include <cstddef>
#include <exception>
#include <iomanip>
#include <ios>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

std::string const program_options::optional_prefix = "--";

program_options::program_options() :
	command(program_command::build)
{
}

std::string program_options::get_usage_text(std::string const &prog)
{
	std::stringstream buf;

	// program's usage
	buf << std::left;
	buf << "Usage: " << prog << " [OPTION]... [PROJECT] [COMMAND] [ARG]..." << std::endl;
	buf << std::endl;
	buf << "Execute COMMAND on a PROJECT." << std::endl;
	buf << std::endl;
	buf << "Parameters:" << std::endl;
	buf << std::setw(30) << "PROJECT" << "root directory of the project, default is current directory" << std::endl;
	buf << std::setw(30) << "COMMAND" << "the command to execute, default is " << std::to_string(default_command) << std::endl;
	buf << std::setw(30) << "ARG" << "argument for the command";

	// optional option's usage
	auto optionals = get_optional_option_usages(optional_prefix);

	if (optionals.size()) {
		buf << std::endl;
		buf << std::endl;
		buf << "Available options:" << std::endl;

		for (auto &optional : optionals) {
			buf << std::setw(30) << optional.usage << optional.description << std::endl;
		}
	}

	auto s = buf.str();
	return trim(s.begin(), s.end());
}

program_options program_options::parse(std::vector<std::string> const &args)
{
	if (!args.size()) {
		throw std::invalid_argument("insufficient program's arguments");
	}

	program_options opt;

	opt.program = args[0];

	// optional options
	std::vector<std::string>::const_iterator i;

	for (i = args.begin() + 1; i != args.end();) {
		auto &arg = *i;

		// check if it is optional argument
		if (arg.compare(0, 2, optional_prefix)) {
			break;
		}

		// find the descriptor for argument
		auto desc = optional_option_descriptors.find(arg.substr(2));

		if (desc == optional_option_descriptors.end()) {
			throw bad_program_option("unknown option " + arg, arg);
		}

		// get argument's arguments
		i++;

		if (static_cast<std::size_t>(args.end() - i) < desc->second.args.size()) {
			throw bad_program_option("insufficient argument for " + arg, arg);
		}

		std::vector<std::string> args(i, i + desc->second.args.size());
		i += desc->second.args.size();

		// process
		desc->second.parser(opt, args);
	}

	// project file
	if (i != args.end()) {
		opt.project_path = fs::real_path(*(i++));

		if (i != args.end()) {
			try {
				opt.command = from_string<program_command>(*(i++));
			} catch (...) {
				std::throw_with_nested(std::runtime_error("failed to parse command"));
			}
		} else {
			opt.command = default_command;
		}
	} else {
		opt.project_path = fs::current_path();
		opt.command = default_command;
	}

	return opt;
}
