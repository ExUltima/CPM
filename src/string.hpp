#ifndef STRING_HPP_INCLUDED
#define STRING_HPP_INCLUDED

#include <string>
#include <vector>

template<class T>
T from_string(std::string const & s);

template<class CharT, class Traits, class Alloc>
std::basic_string<CharT, Traits, Alloc> join(std::vector<std::basic_string<CharT, Traits, Alloc>> const & v, std::basic_string<CharT, Traits, Alloc> const & sep);

#include "string.inl"

#endif // STRING_HPP_INCLUDED
