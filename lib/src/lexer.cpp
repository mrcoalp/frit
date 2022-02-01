#include "lexer.h"

#include <fstream>
#include <sstream>

namespace frit {
std::vector<token> lexer::tokenize(const std::string& source) {
	std::vector<token> tokens;

	auto parse_number = [&](size_t& i) -> std::string {
		std::string number{m_current_char};

		for (size_t j = i + 1; j < source.size(); ++j) {
			auto next = source.at(j);
			// end of number
			if (!std::isdigit(next) && next != '.') {
				break;
			}
			// increment column position
			++m_position.second;
			// a number can only contain a single dot
			if (next == '.' && number.find('.') != std::string::npos) {
				std::stringstream error;
				error << m_position.first << ":" << m_position.second;
				throw lexer_exception("invalid char at " + error.str());
			}
			// append to number string
			m_current_char = next;
			number += m_current_char;
			++i;
		}

		return number;
	};

	for (size_t i = 0; i < source.size(); ++i) {
		m_current_char = source.at(i);

		if (m_current_char == ' ') {
			tokens.push_back({token_type::ident, " "});
		} else if (m_current_char == '\t') {
			tokens.push_back({token_type::ident, "\t"});
		} else if (m_current_char == '\n') {
			tokens.push_back({token_type::ident, "\n"});
			m_position = {1, 1};
		} else if (m_current_char == '+') {
			tokens.push_back({token_type::add, "+"});
		} else if (m_current_char == '-') {
			tokens.push_back({token_type::sub, "-"});
		} else if (m_current_char == '*') {
			tokens.push_back({token_type::mul, "*"});
		} else if (m_current_char == '/') {
			tokens.push_back({token_type::div, "/"});
		} else if (m_current_char == '%') {
			tokens.push_back({token_type::mod, "%"});
		} else if (m_current_char == '(') {
			tokens.push_back({token_type::lparen, "("});
		} else if (m_current_char == ')') {
			tokens.push_back({token_type::rparen, ")"});
		} else if (std::isdigit(m_current_char)) {
			tokens.push_back({token_type::number, parse_number(i)});
		}

		++m_position.first;
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
