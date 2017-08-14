#include <vector>

#include "string.hpp"

namespace fs {

template<class ... Components>
inline std::string combine_path(Components ... c)
{
	std::vector<std::string> items = { c... };
	return join(path_separator, items.begin(), items.end());
}

}
