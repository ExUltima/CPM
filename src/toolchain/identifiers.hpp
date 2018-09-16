#ifndef TOOLCHAIN_IDENTIFIERS_HPP_INCLUDED
#define TOOLCHAIN_IDENTIFIERS_HPP_INCLUDED

#include "../string.hpp"

#include <stdexcept>
#include <string>

enum class toolchain {
	none,
	gcc,
	clang,
	msvc
};

template<>
toolchain from_string<toolchain>(std::string const &s);

namespace std {
string to_string(::toolchain t);
}

template<>
inline toolchain from_string<toolchain>(std::string const &s)
{
	if (s == "none") {
		return toolchain::none;
	} else if (s == "gcc") {
		return toolchain::gcc;
	} else if (s == "clang") {
		return toolchain::clang;
	} else if (s == "msvc") {
		return toolchain::msvc;
	} else {
		throw std::invalid_argument("toolchain is not valid");
	}
}

#endif // TOOLCHAIN_IDENTIFIERS_HPP_INCLUDED
