#include "value.hpp"
#include <stdexcept>
#include <utility>

json_value::json_value() noexcept :
	v(nullptr),
	t(json_type::null)
{
}

json_value::json_value(json_object const &v) :
	v(new json_object(v)),
	t(json_type::object)
{
}

json_value::json_value(json_object &&v) :
	v(new json_object(std::move(v))),
	t(json_type::object)
{
}

json_value::json_value(json_array const &v) :
	v(new json_array(v)),
	t(json_type::array)
{
}

json_value::json_value(json_array &&v) :
	v(new json_array(std::move(v))),
	t(json_type::array)
{
}

json_value::json_value(bool v) :
	v(new bool(v)),
	t(json_type::boolean)
{
}

json_value::json_value(std::string const &v) :
	v(new std::string(v)),
	t(json_type::string)
{
}

json_value::json_value(std::string &&v) :
	v(new std::string(std::move(v))),
	t(json_type::string)
{
}

json_value::json_value(std::intmax_t v) :
	v(new std::intmax_t(v)),
	t(json_type::integer)
{
}

json_value::json_value(double v) :
	v(new double(v)),
	t(json_type::real)
{
}

json_value::json_value(json_value const &other) : json_value()
{
	*this = other;
}

json_value::json_value(json_value &&other) noexcept :
	v(other.v),
	t(other.t)
{
	other.v = nullptr;
	other.t = json_type::null;
}

json_value::~json_value()
{
	clear();
}

json_value &json_value::operator=(json_object const &v)
{
	clear();

	this->v = new json_object(v);
	this->t = json_type::object;

	return *this;
}

json_value &json_value::operator=(json_object &&v)
{
	clear();

	this->v = new json_object(std::move(v));
	this->t = json_type::object;

	return *this;
}

json_value &json_value::operator=(json_array const &v)
{
	clear();

	this->v = new json_array(v);
	this->t = json_type::array;

	return *this;
}

json_value &json_value::operator=(json_array &&v)
{
	clear();

	this->v = new json_array(std::move(v));
	this->t = json_type::array;

	return *this;
}

json_value &json_value::operator=(bool v)
{
	clear();

	this->v = new bool(v);
	this->t = json_type::boolean;

	return *this;
}

json_value &json_value::operator=(std::string const &v)
{
	clear();

	this->v = new std::string(v);
	this->t = json_type::string;

	return *this;
}

json_value &json_value::operator=(std::string &&v)
{
	clear();

	this->v = new std::string(std::move(v));
	this->t = json_type::string;

	return *this;
}

json_value &json_value::operator=(std::intmax_t v)
{
	clear();

	this->v = new std::intmax_t(v);
	this->t = json_type::integer;

	return *this;
}

json_value &json_value::operator=(double v)
{
	clear();

	this->v = new double(v);
	this->t = json_type::real;

	return *this;
}

json_value &json_value::operator=(json_value const &rhs)
{
	clear();

	switch (rhs.t) {
	case json_type::null:
		break;
	case json_type::object:
		this->v = new json_object(rhs.value<json_object>());
		break;
	case json_type::array:
		this->v = new json_array(rhs.value<json_array>());
		break;
	case json_type::boolean:
		this->v = new bool(rhs.value<bool>());
		break;
	case json_type::string:
		this->v = new std::string(rhs.value<std::string>());
		break;
	case json_type::integer:
		this->v = new std::intmax_t(rhs.value<std::intmax_t>());
		break;
	case json_type::real:
		this->v = new double(rhs.value<double>());
		break;
	default:
		throw std::invalid_argument("the specified object is not a valid json_value");
	}

	this->t = rhs.t;

	return *this;
}

json_value &json_value::operator=(json_value &&rhs) noexcept
{
	v = rhs.v; rhs.v = nullptr;
	t = rhs.t; rhs.t = json_type::null;

	return *this;
}

json_value const &json_value::operator[](std::size_t i) const
{
	return at(i);
}

json_value &json_value::operator[](std::size_t i)
{
	return at(i);
}

json_value const &json_value::operator[](std::string const &name) const
{
	return at(name);
}

json_value &json_value::operator[](std::string const &name)
{
	return at(name);
}

json_value const &json_value::at(std::size_t i) const
{
	auto &a = value<json_array>();

	if (i >= a.size()) {
		throw std::out_of_range("the specified index is out of range");
	}

	return a[i];
}

json_value &json_value::at(std::size_t i)
{
	return const_cast<json_value &>(const_cast<json_value const *>(this)->at(i));
}

json_value const &json_value::at(std::string const &name) const
{
	auto &o = value<json_object>();

	auto it = o.find(name);
	if (it == o.end()) {
		throw std::out_of_range("member " + name + " does not exists");
	}

	return it->second;
}

json_value &json_value::at(std::string const &name)
{
	return const_cast<json_value &>(const_cast<json_value const *>(this)->at(name));
}

void json_value::clear()
{
	switch (t) {
	case json_type::null:
		return;
	case json_type::object:
		delete reinterpret_cast<json_object *>(v);
		break;
	case json_type::array:
		delete reinterpret_cast<json_array *>(v);
		break;
	case json_type::boolean:
		delete reinterpret_cast<bool *>(v);
		break;
	case json_type::string:
		delete reinterpret_cast<std::string *>(v);
		break;
	case json_type::integer:
		delete reinterpret_cast<std::intmax_t *>(v);
		break;
	case json_type::real:
		delete reinterpret_cast<double *>(v);
		break;
	default:
		throw std::runtime_error("unknown type for current json_value");
	}

	v = nullptr;
	t = json_type::null;
}
