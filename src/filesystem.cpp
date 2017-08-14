#include "filesystem.hpp"

#include "string.hpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <cerrno>
#include <climits>
#include <cstdlib>

#include <unistd.h>
#endif

#include <system_error>

namespace fs {

#ifdef _WIN32
std::string const path_separator = "\\";
#else
std::string const path_separator = "/";
#endif

std::string current_path()
{
#ifdef _WIN32
	WCHAR buf[MAX_PATH];
	if (!GetCurrentDirectoryW(MAX_PATH, buf)) {
		throw std::system_error(GetLastError(), std::system_category());
	}
	return std::to_string(buf);
#else
	char buf[PATH_MAX];
	if (!getcwd(buf, PATH_MAX)) {
		throw std::system_error(errno, std::system_category());
	}
	return buf;
#endif
}

std::string real_path(std::string const & p)
{
#ifdef _WIN32
	WCHAR buf[MAX_PATH];
	if (!GetFullPathNameW(to_wstring(s).c_str(), MAX_PATH, buf, nullptr)) {
		throw std::system_error(GetLastError(), std::system_category());
	}
	return std::to_string(buf);
#else
	char buf[PATH_MAX];
	if (!::realpath(p.c_str(), buf)) {
		throw std::system_error(errno, std::system_category());
	}
	return buf;
#endif
}

}
