#ifndef EXCEPTION_HPP_INCLUDED
#define EXCEPTION_HPP_INCLUDED

#include <exception>
#include <string>
#include <vector>

std::vector<std::string> get_exception_messages(std::exception const & e);
void get_exception_messages(std::exception const & e, std::vector<std::string> & v);

namespace std {
string to_string(exception const & e);
string to_string(exception const & e, string const & sep);
}

#endif // EXCEPTION_HPP_INCLUDED
