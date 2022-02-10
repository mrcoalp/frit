#include "lexer.h"

#include <fstream>

#include "string_utils.h"
#include "token.h"

namespace frit {

lexer_exception::lexer_exception(const std::string& message, const std::pair<int, int>& position) {
	m_message = string_utils::format("%s at [%i:%i]", message.c_str(), position.first, position.second);
}

std::vector<token> lexer::tokenize(const std::string& source) {
	std::vector<token> tokens;
	char current_char;
	std::pair<int, int> current_position{1, 1};

	auto parse_number = [&](size_t& i) -> std::string {
		std::string number{current_char};

		for (size_t j = i + 1; j < source.size(); ++j) {
			char next = source.at(j);
			// end of number
			if (!std::isdigit(next) && next != '.') {
				break;
			}
			// increment column position
			++current_position.second;
			// a number can only contain a single dot
			if (next == '.' && number.find('.') != std::string::npos) {
				throw lexer_exception("invalid syntax", current_position);
			}
			// append to number string
			current_char = next;
			number += current_char;
			++i;
		}

		return number;
	};

	for (size_t i = 0; i < source.size(); ++i) {
		current_char = source.at(i);

		if (current_char == ' ' || current_char == '\t') {
			void();
		} else if (current_char == '\n') {
			// increment row and reset column
			++current_position.first;
			current_position.second = 0;
		} else if (current_char == '+') {
			tokens.push_back({token_type::add});
		} else if (current_char == '-') {
			tokens.push_back({token_type::sub});
		} else if (current_char == '*') {
			tokens.push_back({token_type::mul});
		} else if (current_char == '/') {
			tokens.push_back({token_type::div});
		} else if (current_char == '%') {
			tokens.push_back({token_type::mod});
		} else if (current_char == '(') {
			tokens.push_back({token_type::lparen});
		} else if (current_char == ')') {
			tokens.push_back({token_type::rparen});
		} else if (std::isdigit(current_char)) {
			tokens.push_back({token_type::number, parse_number(i)});
		} else {
			throw lexer_exception("invalid syntax", current_position);
		}

		++current_position.second;
	}

	return tokens;
}

std::vector<token> lexer::tokenize_file(const std::string& filepath) {
	std::ifstream source{filepath};
	if (!source.is_open()) {
		throw lexer_exception("could not open file");
	}
	return tokenize(std::string{std::istreambuf_iterator<char>{source}, {}});
}

}  // namespace frit
