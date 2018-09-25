#include "program.hpp"
#include "filesystem.hpp"
#include "json/errors.hpp"
#include "json/parser.hpp"
#include "json/value.hpp"
#include "option/commands.hpp"
#include "option/errors.hpp"
#include "option/options.hpp"
#include "project/config.hpp"
#include "project_builder.hpp"

#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

static project_configurations load_project_configurations(std::string const &path);

program::program() :
	running(false)
{
}

void program::run(std::vector<std::string> const &args)
{
	// check to make sure we don't run into weird
	// behavior if there is accidentally call into run multiple times
	if (running) {
		throw std::logic_error("the program is already running");
	}

	running = true;

	// parse options
	try {
		opts = program_options::parse(args);
	} catch (bad_program_option &e) {
		if (e.option() == "--help") {
			std::cout << program_options::get_usage_text(args[0]) << std::endl;
			return;
		}

		throw;
	}

	// parse project configuration
	proj = load_project_configurations(opts.project_path);

	// execute command
	switch (opts.command) {
	case program_command::build:
		build_project();
		break;
	default:
		// TODO: find out which exception to throw
		break;
	}
}

static project_configurations load_project_configurations(std::string const &path)
{
	auto config = fs::combine_path(path, "project.json");
	json_value json;

	try {
		json = json_parse_file(config);
	} catch (bad_json &e) {
		auto msg = config + ":" + std::to_string(e.line()) + ":" + std::to_string(e.column()) + ": " + e.what();
		throw std::runtime_error(msg);
	}

	return project_configurations::from_json(json);
}
