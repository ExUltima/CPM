#ifndef PROGRAM_HPP_INCLUDED
#define PROGRAM_HPP_INCLUDED

#include "json/value.hpp"
#include "program_options.hpp"

#include <experimental/filesystem>
#include <string>
#include <vector>

class program final {
public:
	program(program const &) = delete;

	program & operator=(program const &) = delete;

	static program const & current() { return inst; }
	static void run(std::vector<std::string> const & args);

	program_options const & options() const noexcept { return opts; }

private:
	static program inst;

	bool running;

	program_options opts;
	json_value pconf;

	program();
};

#endif // PROGRAM_HPP_INCLUDED
