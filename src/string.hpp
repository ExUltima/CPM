#ifndef STRING_HPP_INCLUDED
#define STRING_HPP_INCLUDED

#include <string>
#include <vector>

template<class T>
T from_string(std::string const & s); // TODO: use the better way to block non-specialized version

template<class CharT>
std::basic_string<CharT> join(std::vector<std::basic_string<CharT>> const & v, std::basic_string<CharT> const & sep);

#include "string.inl"

#endif // STRING_HPP_INCLUDED
