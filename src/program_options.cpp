#include "program_options.hpp"

#include <sstream>

std::string program_options::get_usage_text(std::string const & prog)
{
	std::stringstream s;

	s << "Usage: " << prog << std::endl;

	return s.str();
}

program_options program_options::parse(std::vector<std::string> const & args)
{
	return program_options();
}
