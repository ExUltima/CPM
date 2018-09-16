#ifndef OPTION_ERRORS_HPP_INCLUDED
#define OPTION_ERRORS_HPP_INCLUDED

#include <stdexcept>
#include <string>

class bad_program_option final : public std::runtime_error {
public:
	bad_program_option(std::string const &what, std::string const &opt);

	std::string const &option() const noexcept { return opt; }

private:
	std::string opt;
};

#endif // OPTION_ERRORS_HPP_INCLUDED
