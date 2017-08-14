#ifndef FILESYSTEM_HPP_INCLUDED
#define FILESYSTEM_HPP_INCLUDED

#include <string>

namespace fs {

extern std::string const path_separator;

template<class ... Components>
std::string combine_path(Components ... c);

std::string current_path();
std::string real_path(std::string const & p);

}

#include "filesystem.inl"

#endif // FILESYSTEM_HPP_INCLUDED
