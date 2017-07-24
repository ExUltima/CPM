#ifndef JSON_HPP_INCLUDED
#define JSON_HPP_INCLUDED

#include <cstdlib>
#include <experimental/filesystem>
#include <istream>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace json {

// forward declaration

class value;

// types

template<class Value>
struct converter {
	Value from_json(value const & j);
	value to_json(Value const & v);
};

enum class value_type {
	null,
	object,
	array,
	boolean,
	string,
	integer,
	real
};

class value final {
public:
	value();
	value(value && other);
	value(value const & other);

	value const & operator[](std::size_t i) const;
	value const & operator[](std::string const & name) const;
	value & operator=(value && rhs);
	value & operator=(value const & rhs);

	std::string const & data() const;
	void data(std::string const & v);
	bool has(std::string const & n) const;
	void member(std::string const & n, value && v);
	void push_back(value && v);
	value_type type() const noexcept { return t; }
	void type(value_type t);

	template<class Value, class Converter = converter<Value>>
	Value as() const;

private:
	value_type t;
	std::string s;
	std::vector<std::unique_ptr<value>> elems;
	std::unordered_map<std::string, std::unique_ptr<value>> mem;
};

class tokenizer final {
public:
	enum class token_type {
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

	tokenizer(std::istream & s);
	tokenizer(tokenizer const &) = delete;

	tokenizer & operator=(tokenizer const &) = delete;

	std::size_t next_column() const noexcept { return ncol; }
	std::size_t next_line() const noexcept { return nline; }

	token_type current_token_type() const noexcept { return type; }
	std::string const & current_token_value() const noexcept { return value; }
	std::size_t current_token_line() const noexcept { return line; }
	std::size_t current_token_column() const noexcept { return col; }

	bool next();
private:
	std::istream & s;
	token_type type;
	std::string value;
	std::size_t line;
	std::size_t col;
	std::size_t nline;
	std::size_t ncol;

	std::string read_string();
};

class bad_json final : public std::runtime_error {
public:
	bad_json(char const * w, std::size_t line, std::size_t col);
	bad_json(std::string const & w, std::size_t line, std::size_t col);

	std::size_t column() const noexcept { return c; }
	std::size_t line() const noexcept { return l; }

private:
	std::size_t l;
	std::size_t c;
};

// functions
value parse(std::istream & s);
value parse(std::string const & str);
value parse(std::experimental::filesystem::path const & p);

}

#endif // JSON_HPP_INCLUDED
