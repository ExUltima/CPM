#include "errors.hpp"

bad_program_option::bad_program_option(std::string const &opt) :
	bad_program_option("unknown option ", opt)
{
}

bad_program_option::bad_program_option(char const *prefix, std::string const &opt) :
	runtime_error(prefix + opt),
	opt(opt)
{
}
