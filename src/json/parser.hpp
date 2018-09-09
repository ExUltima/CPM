#ifndef JSON_PARSER_HPP_INCLUDED
#define JSON_PARSER_HPP_INCLUDED

#include "value.hpp"

#include <istream>
#include <string>

json_value json_parse(std::istream &json);
json_value json_parse(std::string const &json);
json_value json_parse_file(std::string const &path);

#endif // JSON_PARSER_HPP_INCLUDED
