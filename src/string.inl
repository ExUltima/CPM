#include <sstream>

template<class CharT, class Traits, class Alloc>
inline std::basic_string<CharT, Traits, Alloc> join(std::vector<std::basic_string<CharT, Traits, Alloc>> const & v, std::basic_string<CharT, Traits, Alloc> const & sep)
{
	std::basic_stringstream<CharT, Traits, Alloc> s;

	for (auto it = v.begin();;) {
		s << *(it++);
		if (it == v.end()) break;
		s << sep;
	}

	return s.str();
}
