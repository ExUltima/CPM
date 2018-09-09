#include "tokenizer.hpp"
#include "errors.hpp"

#include <cctype>
#include <sstream>
#include <stdexcept>

json_tokenizer::json_tokenizer(std::istream &json) :
	j(json),
	l(0),
	c(0),
	nl(1),
	nc(1),
	t(json_token::null)
{
}

bool json_tokenizer::next()
{
	j.exceptions(std::ios_base::badbit);

	for (std::string ch;; nc++) {
		// get next character
		ch = j.get();

		if (!j.good()) {
			return false;
		}

		// skip if it is line break or space
		if (ch[0] == '\n') {
			nl++;
			nc = 0; // actually we need 1 but we need 0 here because it will be increased by 1 by for statement
			continue;
		} else if (std::isspace(ch[0], j.getloc())) {
			continue;
		}

		// parse token
		l = nl;
		c = nc;
		s = ch;

		switch (ch[0]) {
		case '{':
			t = json_token::start_object;
			break;
		case '}':
			t = json_token::end_object;
			break;
		case '[':
			t = json_token::start_array;
			break;
		case ']':
			t = json_token::end_array;
			break;
		case '"':
			t = json_token::string;
			s = read_quoted(); // this method will update nc automatically
			break;
		case ':':
			t = json_token::colon;
			break;
		case ',':
			t = json_token::comma;
			break;
		default:
			// character is not recognized, try to read the whole word instead
			j.unget();
			j >> ch;

			if (ch == "null") {
				t = json_token::null;
			} else if (ch == "true") {
				t = json_token::bool_true;
			} else if (ch == "false") {
				t = json_token::bool_false;
			} else {
				// word is not recognized as json keyword, try to check if it is number
				try {
					std::stol(ch, 0, 0);
					t = json_token::integer;
				} catch (std::invalid_argument &) {
					try {
						std::stod(ch);
						t = json_token::real;
					} catch (std::invalid_argument &) {
						throw bad_json("unrecognized token", l, c);
					}
				}
			}

			s = ch;
			nc += ch.length() - 1; // we need to minus 1 here since for statement will increasing it by 1
		}

		break;
	}

	return true;
}

std::string json_tokenizer::read_quoted()
{
	std::stringstream s;

	// read until reached "
	bool esc = false;

	for (nc++ ;;) {
		auto ch = j.get();

		if (!j.good()) {
			throw bad_json("expected \"", nl, nc);
		}

		// check if it is escaped
		if (!esc) {
			if (ch == '"') {
				break;
			} else if (ch == '\\') {
				esc = true;
				nc++;
				continue;
			}
		}

		s.put(ch);

		esc = false;
		nc++;
	}

	return s.str();
}
