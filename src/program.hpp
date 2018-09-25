#ifndef PROGRAM_HPP_INCLUDED
#define PROGRAM_HPP_INCLUDED

#include "option/options.hpp"
#include "project/config.hpp"

#include <string>
#include <vector>

class program final {
public:
	program();
	program(program const &) = delete;

	program &operator=(program const &) = delete;

	program_options const &options() const noexcept { return opts; }

	void run(std::vector<std::string> const &args);

private:
	bool running;
	program_options opts;
	project_configurations proj;
};

#endif // PROGRAM_HPP_INCLUDED
