#include "program.hpp"

#include "project_builder.hpp"

#include <iostream>
#include <stdexcept>

program program::inst;

program::program() :
	running(false)
{
}

void program::run(std::vector<std::string> const & args)
{
	// check to make sure we don't run into weird
	// behavior if there is accidentally call into run multiple times
	if (inst.running) {
		throw std::logic_error("the program is already running");
	}

	inst.running = true;

	// parse options
	try {
		inst.opts = program_options::parse(args);
	} catch (bad_program_option & e) {
		if (e.option() == "--help") {
			std::cout << program_options::get_usage_text(args[0]) << std::endl;
			return;
		}

		throw;
	}

	inst.pconf = json::parse(inst.opts.project_path / "project.json");

	// execute command
	switch (inst.opts.command) {
	case program_command::build:
		build_project();
		break;
	default:
		// TODO: find out which exception to throw
		break;
	}
}
