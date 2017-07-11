#include "exception.hpp"

#include "string.hpp"

std::vector<std::string> get_exception_messages(std::exception const & e)
{
	std::vector<std::string> v;
	get_exception_messages(e, v);
	return v;
}

void get_exception_messages(std::exception const & e, std::vector<std::string> & v)
{
	v.push_back(e.what());

	try {
		std::rethrow_if_nested(e);
	} catch (std::exception & e) {
		get_exception_messages(e, v);
	}
}

std::string std::to_string(exception const & e)
{
	return to_string(e, " -> ");
}

std::string std::to_string(exception const & e, string const & sep)
{
	auto v = ::get_exception_messages(e);
	return join(v, sep);
}
