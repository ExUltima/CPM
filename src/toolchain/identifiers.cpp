#include "identifiers.hpp"

std::string std::to_string(::toolchain t)
{
	switch (t) {
	case toolchain::none:
		return "none";
	case toolchain::gcc:
		return "gcc";
	case toolchain::clang:
		return "clang";
	case toolchain::msvc:
		return "msvc";
	default:
		throw std::invalid_argument("toolchain is not valid");
	}
}
