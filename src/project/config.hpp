#ifndef PROJECT_CONFIG_HPP_INCLUDED
#define PROJECT_CONFIG_HPP_INCLUDED

#include "../json/value.hpp"

class project_configurations final {
public:
	static project_configurations from_json(json_value const &json);
};

#endif // PROJECT_CONFIG_HPP_INCLUDED
