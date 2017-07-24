#include "json.hpp"

#include <fstream>
#include <locale>
#include <sstream>
#include <utility>

using namespace json;

// static

static value process_start_token(tokenizer & tkn);

static void process_array(value & v, tokenizer & tkn)
{
	if (!tkn.next()) {
		throw bad_json("expected ']'", tkn.next_line(), tkn.next_column());
	}

	v.type(value_type::array);

	if (tkn.current_token_type() == tokenizer::token_type::end_array) {
		// empty array
		return;
	}

	for (;;) {
		v.push_back(process_start_token(tkn));

		// move to comma or end of array
		if (!tkn.next()) {
			throw bad_json("expected ']'", tkn.next_line(), tkn.next_column());
		}

		if (tkn.current_token_type() == tokenizer::token_type::end_array) {
			break;
		}

		// move to next item
		if (tkn.current_token_type() != tokenizer::token_type::comma) {
			throw bad_json("expected ']'", tkn.current_token_line(), tkn.current_token_column());
		}

		if (!tkn.next()) {
			throw bad_json("expected array item", tkn.next_line(), tkn.next_column());
		}

		if (tkn.current_token_type() == tokenizer::token_type::end_array) {
			throw bad_json("expected array item", tkn.current_token_line(), tkn.current_token_column());
		}
	}
}

static void process_object(value & v, tokenizer & tkn)
{
	if (!tkn.next()) {
		throw bad_json("expected '}'", tkn.next_line(), tkn.next_column());
	}

	v.type(value_type::object);

	if (tkn.current_token_type() == tokenizer::token_type::end_object) {
		// empty object
		return;
	}

	for (;;) {
		if (tkn.current_token_type() != tokenizer::token_type::string) {
			throw bad_json("expected quoted string", tkn.current_token_line(), tkn.current_token_column());
		}

		// member name
		auto name = tkn.current_token_value();
		auto namel = tkn.current_token_line();
		auto namec = tkn.current_token_column();

		if (!tkn.next()) {
			throw bad_json("expected ':'", tkn.next_line(), tkn.next_column());
		} else if (tkn.current_token_type() != tokenizer::token_type::colon) {
			throw bad_json("expected ':'", tkn.current_token_line(), tkn.current_token_column());
		}

		if (v.has(name)) {
			std::stringstream m;
			m << "the member '" << name << "' is already exists";
			throw bad_json(m.str(), namel, namec);
		}

		// member value
		if (!tkn.next()) {
			throw bad_json("expected json value", tkn.next_line(), tkn.next_column());
		}

		v.member(name, process_start_token(tkn));

		// move to next member
		if (!tkn.next()) {
			throw bad_json("expected '}'", tkn.next_line(), tkn.next_column());
		}

		if (tkn.current_token_type() == tokenizer::token_type::end_object) {
			break;
		} else if (tkn.current_token_type() != tokenizer::token_type::comma) {
			throw bad_json("expected '}'", tkn.current_token_line(), tkn.current_token_column());
		}

		if (!tkn.next()) {
			throw bad_json("expected quoted string", tkn.next_line(), tkn.next_column());
		}
	}
}

static value process_start_token(tokenizer & tkn)
{
	value v;

	switch (tkn.current_token_type()) {
	case tokenizer::token_type::start_object:
		process_object(v, tkn);
		break;
	case tokenizer::token_type::start_array:
		process_array(v, tkn);
		break;
	case tokenizer::token_type::string:
		v.type(value_type::string);
		v.data(tkn.current_token_value());
		break;
	default:
		throw std::logic_error("json tokenizer return unexpected token");
	}

	return v;
}

// bad_json

bad_json::bad_json(char const * w, std::size_t line, std::size_t col) :
	runtime_error(w),
	l(line),
	c(col)
{
}

bad_json::bad_json(std::string const & w, std::size_t line, std::size_t col) :
	runtime_error(w),
	l(line),
	c(col)
{
}

// functions

value json::parse(std::istream & s)
{
	tokenizer tkn(s);

	if (tkn.next()) {
		return process_start_token(tkn);
	} else {
		// empty json
		return value();
	}
}

value json::parse(std::string const & str)
{
	std::stringstream s(str);
	return parse(s);
}

value json::parse(std::experimental::filesystem::path const & p)
{
	std::ifstream f;

	f.exceptions(std::ios_base::failbit);

	try {
		f.open(p);
	} catch (std::ios_base::failure & e) {
		std::stringstream m;
		m << "failed to open " << p;
		throw std::runtime_error(m.str());
	}

	try {
		return parse(f);
	} catch (bad_json & e) {
		std::stringstream m;
		m << p << ":" << e.line() << ":" << e.column() << ": " << e.what();
		throw bad_json(m.str(), e.line(), e.column());
	}
}

// tokenizer

tokenizer::tokenizer(std::istream & s) :
	s(s),
	type(token_type::null),
	line(0),
	col(0),
	nline(1),
	ncol(1)
{
}

bool tokenizer::next()
{
	s.exceptions(std::ios_base::badbit);

	for (std::string t;; ncol++) {
		t = s.get();
		if (!s.good()) {
			return false;
		}

		if (t[0] == '\n') {
			nline++; ncol = 0;
			continue;
		} else if (std::isspace(t[0], s.getloc())) {
			continue;
		}

		line = nline;
		col = ncol;
		value = t;

		switch (t[0]) {
		case '{':
			type = token_type::start_object;
			break;
		case '}':
			type = token_type::end_object;
			break;
		case '[':
			type = token_type::start_array;
			break;
		case ']':
			type = token_type::end_array;
			break;
		case '"':
			type = token_type::string;
			ncol++; value = read_string();
			break;
		case ':':
			type = token_type::colon;
			break;
		case ',':
			type = token_type::comma;
			break;
		default:
			s.unget();
			s >> t;

			if (t == "null") {
				type = token_type::null;
			} else if (t == "true") {
				type = token_type::bool_true;
			} else if (t == "false") {
				type = token_type::bool_false;
			} else {
				try {
					std::stoi(t, 0, 0);
					type = token_type::integer;
				} catch (std::invalid_argument &) {
					try {
						std::stof(t);
						type = token_type::real;
					} catch (std::invalid_argument &) {
						throw bad_json("unrecognized token", nline, ncol);
					}
				}
			}

			value = t;
			ncol += t.length() - 1;
		}

		break;
	}

	return true;
}

std::string tokenizer::read_string()
{
	std::stringstream buf;
	bool esc = false;

	for (;;) {
		auto ch = s.get();
		if (!s.good()) {
			throw bad_json("expected \"", nline, ncol);
		}

		if (!esc) {
			if (ch == '"') {
				break;
			} else if (ch == '\\') {
				esc = true; ncol++;
				continue;
			}
		}

		buf.put(ch);
		esc = false; ncol++;
	}

	return buf.str();
}

// value

value::value() :
	t(value_type::null)
{
}

value::value(value && other) :
	t(other.t),
	s(std::move(other.s)),
	elems(std::move(other.elems)),
	mem(std::move(other.mem))
{
	other.t = value_type::null;
}

void value::data(std::string const & v)
{
	if (t != value_type::boolean && t != value_type::integer && t != value_type::real && t != value_type::string) {
		throw std::domain_error("the value is not scalar");
	}

	s = v;
}

bool value::has(std::string const & n) const
{
	if (t != value_type::object) {
		throw std::domain_error("the value is not object");
	}

	auto it = mem.find(n);
	return (it != mem.end() && it->second) ? true : false;
}

void value::member(std::string const & n, value && v)
{
	if (t != value_type::object) {
		throw std::domain_error("the value is not object");
	}

	mem[n] = std::make_unique<value>(std::forward<value>(v));
}

void value::push_back(value && v)
{
	if (t != value_type::array) {
		throw std::domain_error("the value is not array");
	}

	elems.push_back(std::make_unique<value>(std::forward<value>(v)));
}

void value::type(value_type t)
{
	this->t = t;

	s.clear();
	elems.clear();
	mem.clear();
}
