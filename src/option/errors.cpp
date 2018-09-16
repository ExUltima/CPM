#include "errors.hpp"

bad_program_option::bad_program_option(std::string const &what, std::string const &opt) :
	runtime_error(what),
	opt(opt)
{
}
