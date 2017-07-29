#ifndef STRING_HPP_INCLUDED
#define STRING_HPP_INCLUDED

#include <string>
#include <vector>

template<class T>
T from_string(std::string const & s);

template<class CharT, class Iterator>
std::basic_string<CharT> join(CharT const * sep, Iterator first, Iterator last);

template<class CharT, class Traits, class Alloc, class Iterator>
std::basic_string<CharT, Traits, Alloc> join(std::basic_string<CharT, Traits, Alloc> const & sep, Iterator first, Iterator last);

template<class Iterator>
std::basic_string<typename Iterator::value_type> trim(Iterator first, Iterator last);

namespace std {

template<class Iterator>
basic_string<typename Iterator::value_type> toupper(Iterator first, Iterator last);

}

#include "string.inl"

#endif // STRING_HPP_INCLUDED
