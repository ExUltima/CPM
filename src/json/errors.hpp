#ifndef JSON_ERRORS_HPP_INCLUDED
#define JSON_ERRORS_HPP_INCLUDED

#include <cstddef>
#include <stdexcept>
#include <string>

class bad_json final : public std::runtime_error {
public:
	bad_json(char const *what, std::size_t line, std::size_t col);
	bad_json(std::string const &what, std::size_t line, std::size_t col);

	std::size_t line() const noexcept { return l; }
	std::size_t column() const noexcept { return c; }

private:
	std::size_t l;
	std::size_t c;
};

#endif // JSON_ERRORS_HPP_INCLUDED
