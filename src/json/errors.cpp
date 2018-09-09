#include "errors.hpp"

bad_json::bad_json(char const *what, std::size_t line, std::size_t col) :
	runtime_error(what),
	l(line),
	c(col)
{
}

bad_json::bad_json(std::string const &what, std::size_t line, std::size_t col) :
	runtime_error(what),
	l(line),
	c(col)
{
}
