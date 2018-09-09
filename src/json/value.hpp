#ifndef JSON_VALUE_HPP_INCLUDED
#define JSON_VALUE_HPP_INCLUDED

#include <cinttypes>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

class json_value;

enum class json_type {
	null,
	object,
	array,
	boolean,
	string,
	integer,
	real
};

typedef std::vector<json_value> json_array;
typedef std::unordered_map<std::string, json_value> json_object;

class json_value final {
public:
	json_value() noexcept;
	json_value(json_object const &v);
	json_value(json_object &&v);
	json_value(json_array const &v);
	json_value(json_array &&v);
	json_value(bool v);
	json_value(std::string const &v);
	json_value(std::string &&v);
	json_value(std::intmax_t v);
	json_value(double v);
	json_value(json_value const &other);
	json_value(json_value &&other) noexcept;
	~json_value();

	json_value &operator=(json_object const &v);
	json_value &operator=(json_object &&v);
	json_value &operator=(json_array const &v);
	json_value &operator=(json_array &&v);
	json_value &operator=(bool v);
	json_value &operator=(std::string const &v);
	json_value &operator=(std::string &&v);
	json_value &operator=(std::intmax_t v);
	json_value &operator=(double v);
	json_value &operator=(json_value const &rhs);
	json_value &operator=(json_value &&rhs) noexcept;
	json_value const &operator[](std::size_t i) const;
	json_value &operator[](std::size_t i);
	json_value const &operator[](std::string const &name) const;
	json_value &operator[](std::string const &name);

	json_type type() const noexcept { return t; }
	template<class Type> Type const &value() const;
	template<class Type> Type &value();

	json_value const &at(std::size_t i) const;
	json_value &at(std::size_t i);
	json_value const &at(std::string const &name) const;
	json_value &at(std::string const &name);

	void clear();

private:
	void *v;
	json_type t;
};

template<>
inline json_object const &json_value::value<json_object>() const
{
	if (t != json_type::object) {
		throw std::logic_error("the current value is not an object");
	}

	return *reinterpret_cast<json_object *>(v);
}

template<>
inline json_array const &json_value::value<json_array>() const
{
	if (t != json_type::array) {
		throw std::logic_error("the current value is not an array");
	}

	return *reinterpret_cast<json_array *>(v);
}

template<>
inline bool const &json_value::value<bool>() const
{
	if (t != json_type::boolean) {
		throw std::logic_error("the current value is not a boolean");
	}

	return *reinterpret_cast<bool *>(v);
}

template<>
inline std::string const &json_value::value<std::string>() const
{
	if (t != json_type::string) {
		throw new std::logic_error("the current value is not string");
	}

	return *reinterpret_cast<std::string *>(v);
}

template<>
inline std::intmax_t const &json_value::value<std::intmax_t>() const
{
	if (t != json_type::integer) {
		throw std::logic_error("the current value is not an integer");
	}

	return *reinterpret_cast<std::intmax_t *>(v);
}

template<>
inline double const &json_value::value<double>() const
{
	if (t != json_type::real) {
		throw std::logic_error("the current value is not a floating point number");
	}

	return *reinterpret_cast<double *>(v);
}

template<>
inline json_object &json_value::value<json_object>()
{
	return const_cast<json_object &>(const_cast<json_value const *>(this)->value<json_object>());
}

template<>
inline json_array &json_value::value<json_array>()
{
	return const_cast<json_array &>(const_cast<json_value const *>(this)->value<json_array>());
}

template<>
inline bool &json_value::value<bool>()
{
	return const_cast<bool &>(const_cast<json_value const *>(this)->value<bool>());
}

template<>
inline std::string &json_value::value<std::string>()
{
	return const_cast<std::string &>(const_cast<json_value const *>(this)->value<std::string>());
}

template<>
inline std::intmax_t &json_value::value<std::intmax_t>()
{
	return const_cast<std::intmax_t &>(const_cast<json_value const *>(this)->value<std::intmax_t>());
}

template<>
inline double &json_value::value<double>()
{
	return const_cast<double &>(const_cast<json_value const *>(this)->value<double>());
}

#endif // JSON_VALUE_HPP_INCLUDED
