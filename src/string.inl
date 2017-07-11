#include <sstream>

template<class CharT>
inline std::basic_string<CharT> join(std::vector<std::basic_string<CharT>> const & v, std::basic_string<CharT> const & sep)
{
	std::basic_stringstream<CharT> s;

	for (auto it = v.begin();;) {
		s << *(it++);
		if (it == v.end()) break;
		s << sep;
	}

	return s.str();
}
