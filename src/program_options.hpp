#ifndef PROGRAM_OPTIONS_HPP_INCLUDED
#define PROGRAM_OPTIONS_HPP_INCLUDED

#include "string.hpp"

#include <experimental/filesystem>
#include <stdexcept>
#include <string>
#include <vector>

// types

enum class program_command {
	build
};

class program_options final {
public:
	static program_command const default_command = program_command::build;
	static std::experimental::filesystem::path const default_project_file;

	program_command command;
	std::string command_name;
	std::experimental::filesystem::path project_file;

	program_options();

	static std::string get_usage_text(std::string const & prog);
	static program_options parse(std::vector<std::string> const & args);
};

class bad_program_option final : public std::runtime_error {
public:
	bad_program_option(std::string const & opt);

	std::string const & option() const noexcept { return opt; }

private:
	std::string opt;
};

// functions

template<>
program_command from_string<program_command>(std::string const & s);

namespace std {
string to_string(::program_command c);
}

#include "program_options.inl"

#endif // PROGRAM_OPTIONS_HPP_INCLUDED
