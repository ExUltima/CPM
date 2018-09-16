#include "optionals.hpp"
#include "../filesystem.hpp"
#include "../string.hpp"
#include "../toolchain/identifiers.hpp"

#include <algorithm>
#include <exception>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<optional_option_usage> get_optional_option_usages(std::string const &prefix)
{
	std::vector<optional_option_usage> usages;

	for (auto &e : optional_option_descriptors) {
		std::stringstream usage;

		auto &name = e.first;
		auto &desc = e.second;
		auto &args = desc.args;

		// option name
		usage << prefix << name;

		// option's arguments
		std::vector<std::string> args_name;

		std::transform(args.begin(), args.end(), std::back_inserter(args_name), [](auto &arg)
		{
			auto name = arg.required ? arg.name : "[" + arg.name + "]";
			return std::toupper(name.begin(), name.end());
		});

		if (args_name.size()) {
			usage << " " << join(" ", args_name.begin(), args_name.end());
		}

		usages.push_back(optional_option_usage{usage.str(), desc.description});
	}

	return usages;
}

static void parse_project(program_options &opt, std::vector<std::string> const &args)
{
	try {
		opt.project_path = fs::real_path(args[0]);
	} catch (...) {
		std::throw_with_nested(std::runtime_error("failed to set project directory to " + args[0]));
	}
}

static void parse_toolchain(program_options &opt, std::vector<std::string> const &args)
{
	try {
		opt.toolchain = from_string<toolchain>(args[0]);
	} catch (...) {
		std::throw_with_nested(std::runtime_error("failed to set toolchain to " + args[0]));
	}
}

std::map<std::string, optional_option_descriptor> const optional_option_descriptors = {
	{"project", optional_option_descriptor{
		"root directory of the project, default is current directory",
		parse_project,
		{
			optional_option_argument_descriptor{"path", true}
		}
	}},
	{"toolchain", optional_option_descriptor{
		"toolchain to use, default is toolchain native to current platform",
		parse_toolchain,
		{
			optional_option_argument_descriptor{"name", true}
		}
	}}
};
