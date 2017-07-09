#ifndef PROGRAM_HPP_INCLUDED
#define PROGRAM_HPP_INCLUDED

#include "program_options.hpp"

#include <string>
#include <vector>

class program final {
public:
	program(program const &) = delete;

	program & operator=(program const &) = delete;

	static program const & current() { return curr; }
	static int run(std::vector<std::string> const & args);

	program_options const & options() const noexcept { return opts; }

private:
	static program curr;

	program_options opts;

	program();
};

#endif // PROGRAM_HPP_INCLUDED
