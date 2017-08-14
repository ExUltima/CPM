#include "string.hpp"

#include <codecvt>

std::string std::to_string(wstring const & s)
{
	wstring_convert<codecvt_utf8_utf16<wchar_t>> cvt;
	return cvt.to_bytes(s);
}

std::wstring to_wstring(std::string const & s)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> cvt;
	return cvt.from_bytes(s);
}
