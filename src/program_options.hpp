#ifndef PROGRAM_OPTIONS_HPP_INCLUDED
#define PROGRAM_OPTIONS_HPP_INCLUDED

#include <stdexcept>
#include <string>
#include <vector>

class program_options final {
public:
	static std::string get_usage_text(std::string const & prog);
	static program_options parse(std::vector<std::string> const & args);
};

class bad_program_option final : public std::runtime_error {
public:
	std::string const & option() const noexcept { return opt; }

private:
	std::string opt;
};

#endif // PROGRAM_OPTIONS_HPP_INCLUDED
