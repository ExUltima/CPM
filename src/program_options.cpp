#include "program_options.hpp"

#include "filesystem.hpp"
#include "string.hpp"

#include <algorithm>
#include <functional>
#include <iomanip>
#include <iterator>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// optional options

struct optional_option_argument_descriptor {
	std::string name;
	bool required;
};

struct optional_option_descriptor {
	std::string description;
	std::function<void(program_options &, std::vector<std::string> const &)> parser;
	std::vector<optional_option_argument_descriptor> args;
};

static std::map<std::string, optional_option_descriptor> const optional_options_descriptor = {
	{"platform", optional_option_descriptor{
		"set target platform, default is current platform",
		program_options::parse_platform,
		{
			optional_option_argument_descriptor{"name", true}
		}
	}}
};

static std::vector<std::pair<std::string, std::string>> get_optional_option_usage()
{
	std::vector<std::pair<std::string, std::string>> usages;

	for (auto & e : optional_options_descriptor) {
		auto & name = e.first;
		auto & desc = e.second;
		auto & args = desc.args;
		std::stringstream usage;

		// option name
		usage << program_options::optional_prefix << name;

		// option's arguments
		std::vector<std::string> args_name;
		std::transform(args.begin(), args.end(), std::back_inserter(args_name), [](optional_option_argument_descriptor const & arg)
		{
			auto name = arg.required ? arg.name : "[" + arg.name + "]";
			return std::toupper(name.begin(), name.end());
		});

		if (args_name.size()) {
			usage << " " << join(" ", args_name.begin(), args_name.end());
		}

		usages.push_back(std::make_pair(usage.str(), desc.description));
	}

	return usages;
}

// program_options

std::string const program_options::optional_prefix = "--";

program_options::program_options() :
	command(program_command::build)
{
}

std::string program_options::get_usage_text(std::string const & prog)
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
	auto opts_usage = get_optional_option_usage();

	if (opts_usage.size()) {
		buf << std::endl;
		buf << std::endl;
		buf << "Available options:" << std::endl;

		for (auto & p : opts_usage) {
			buf << std::setw(30) << p.first << p.second << std::endl;
		}
	}

	auto s = buf.str();
	return trim(s.begin(), s.end());
}

program_options program_options::parse(std::vector<std::string> const & args)
{
	if (!args.size()) {
		throw std::invalid_argument("insufficient program's arguments");
	}

	program_options opt;

	opt.command_name = args[0];

	// optional options
	std::vector<std::string>::const_iterator i;

	for (i = args.begin() + 1; i != args.end();) {
		auto & arg = *i;

		// check if it is optional argument
		if (arg.compare(0, 2, optional_prefix)) {
			break;
		}

		// find the descriptor for argument
		auto di = optional_options_descriptor.find(arg.substr(2));
		if (di == optional_options_descriptor.end()) {
			throw bad_program_option(arg);
		}

		// get arguments
		i++;

		if (static_cast<std::size_t>(args.end() - i) < di->second.args.size()) {
			throw bad_program_option("insufficient argument for ", arg);
		}

		std::vector<std::string> args(i, i + di->second.args.size());
		i += di->second.args.size();

		// process
		di->second.parser(opt, args);
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

void program_options::parse_platform(program_options & o, std::vector<std::string> const & args)
{
	o.platform = args[0];
}

// bad_program_option

bad_program_option::bad_program_option(std::string const & opt) :
	bad_program_option("unknown option ", opt)
{
}

bad_program_option::bad_program_option(char const *prefix, std::string const & opt) :
	runtime_error(prefix + opt),
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
