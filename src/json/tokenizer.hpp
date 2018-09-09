#ifndef JSON_TOKENIZER_HPP_INCLUDED
#define JSON_TOKENIZER_HPP_INCLUDED

#include <cstddef>
#include <istream>
#include <string>

enum class json_token {
	null,
	bool_true,
	bool_false,
	string,
	integer,
	real,
	colon,
	comma,
	start_object,
	end_object,
	start_array,
	end_array
};

class json_tokenizer final {
public:
	json_tokenizer(std::istream &json);
	json_tokenizer(json_tokenizer const &) = delete;

	json_tokenizer &operator=(json_tokenizer const &) = delete;

	bool next();

	std::size_t next_column() const noexcept { return nc; }
	std::size_t next_line() const noexcept { return nl; }

	json_token current_token() const noexcept { return t; }
	std::string const & current_string() const noexcept { return s; }
	std::size_t current_line() const noexcept { return l; }
	std::size_t current_column() const noexcept { return c; }
private:
	std::string read_quoted();

	std::istream &j;
	std::size_t l;
	std::size_t c;
	std::size_t nl;
	std::size_t nc;
	json_token t;
	std::string s;
};

#endif // JSON_TOKENIZER_HPP_INCLUDED
