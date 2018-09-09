#include "parser.hpp"
#include "errors.hpp"
#include "tokenizer.hpp"
#include "value.hpp"

#include <fstream>
#include <sstream>
#include <utility>

static json_value parse_value(json_tokenizer &t);
static json_value parse_object(json_tokenizer &t);
static json_value parse_array(json_tokenizer &t);

json_value json_parse(std::istream &json)
{
	json_tokenizer t(json);

	if (t.next()) {
		return parse_value(t);
	} else {
		return json_value();
	}
}

json_value json_parse(std::string const &json)
{
	std::stringstream s(json);
	return json_parse(s);
}

json_value json_parse_file(std::string const &path)
{
	// open file
	std::ifstream f;

	f.exceptions(std::ios_base::failbit);

	try {
		f.open(path);
	} catch (std::ios_base::failure &) {
		throw std::runtime_error("failed to open " + path);
	}

	// parse
	return json_parse(f);
}

static json_value parse_value(json_tokenizer &t)
{
	switch (t.current_token()) {
	case json_token::null:
		return json_value();
	case json_token::bool_true:
		return json_value(true);
	case json_token::bool_false:
		return json_value(false);
	case json_token::string:
		return json_value(t.current_string());
	case json_token::integer:
		return json_value(std::stol(t.current_string()));
	case json_token::real:
		return json_value(std::stod(t.current_string()));
	case json_token::start_object:
		return parse_object(t);
	case json_token::start_array:
		return parse_array(t);
	default:
		throw bad_json("unexpected token", t.current_line(), t.current_column());
	}
}

static json_value parse_object(json_tokenizer &t)
{
	if (!t.next()) {
		throw bad_json("expected '}'", t.next_line(), t.next_column());
	}

	// parse object body
	json_object o;

	if (t.current_token() == json_token::end_object) {
		// empty object
		return o;
	}

	for (;;) {
		// get member name
		if (t.current_token() != json_token::string) {
			throw bad_json("expected member name", t.current_line(), t.current_column());
		}

		auto name = t.current_string();
		auto line = t.current_line();
		auto col = t.current_column();

		// get member value
		if (!t.next()) {
			throw bad_json("expected ':'", t.next_line(), t.next_column());
		} else if (t.current_token() != json_token::colon) {
			throw bad_json("expected ':'", t.current_line(), t.current_column());
		}

		if (!t.next()) {
			throw bad_json("expected object value", t.next_line(), t.next_column());
		}

		// add member to object
		auto r = o.insert(std::make_pair(name, parse_value(t)));

		if (!r.second) {
			throw bad_json("duplicated member " + name, line, col);
		}

		// move to next member
		if (!t.next()) {
			throw bad_json("expected ',' or '}'", t.next_line(), t.next_column());
		}

		switch (t.current_token()) {
		case json_token::end_object:
			goto done;
		case json_token::comma:
			break;
		default:
			throw bad_json("expected ',' or '}'", t.current_line(), t.current_column());
		}

		if (!t.next()) {
			throw bad_json("expected member name", t.next_line(), t.next_column());
		}
	}

	done:
	return o;
}

static json_value parse_array(json_tokenizer &t)
{
	if (!t.next()) {
		throw bad_json("expected ']'", t.next_line(), t.next_column());
	}

	// parse array body
	json_array a;

	if (t.current_token() == json_token::end_array) {
		// empty array
		return a;
	}

	for (;;) {
		a.push_back(parse_value(t));

		// move to next element
		if (!t.next()) {
			throw bad_json("expected ',' or ']'", t.next_line(), t.next_column());
		}

		switch (t.current_token()) {
		case json_token::end_array:
			goto done;
		case json_token::comma:
			break;
		default:
			throw bad_json("expected ',' or ']'", t.current_line(), t.current_column());
		}

		if (!t.next()) {
			throw bad_json("expected array item", t.next_line(), t.next_column());
		}
	}

	done:
	return a;
}
