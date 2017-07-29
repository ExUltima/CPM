#include <algorithm>
#include <cctype>
#include <iterator>
#include <sstream>
#include <vector>

template<class CharT, class Iterator>
inline std::basic_string<CharT> join(CharT const * sep, Iterator first, Iterator last)
{
	return join(std::basic_string<CharT>(sep), first, last);
}

template<class CharT, class Traits, class Alloc, class Iterator>
inline std::basic_string<CharT, Traits, Alloc> join(std::basic_string<CharT, Traits, Alloc> const & sep, Iterator first, Iterator last)
{
	if (first == last) {
		return "";
	}

	std::basic_stringstream<CharT, Traits, Alloc> s;

	for (;;) {
		s << *(first++);
		if (first == last) break;
		s << sep;
	}

	return s.str();
}

template<class Iterator>
inline std::basic_string<typename Iterator::value_type> std::toupper(Iterator first, Iterator last)
{
	vector<typename Iterator::value_type> chars;
	transform(first, last, back_inserter(chars), [](typename Iterator::value_type ch){
		return toupper(ch);
	});
	return basic_string<typename Iterator::value_type>(chars.data(), chars.size());
}

template<class Iterator>
inline std::basic_string<typename Iterator::value_type> trim(Iterator first, Iterator last)
{
	// find first non space character
	while (first != last) {
		if (!std::isspace(*first)) {
			break;
		}
		first++;
	}

	if (first == last) {
		return std::basic_string<typename Iterator::value_type>();
	}

	// find last non space character
	last--;

	while (last != first) {
		if (!std::isspace(*last)) {
			break;
		}
		last--;
	}

	return std::basic_string<typename Iterator::value_type>(first, last + 1);
}
