#include "lexer.h"

#include <fstream>

namespace frit {
namespace lexer {

const char* digits = "0123456789";

std::vector<token> tokenize(const std::string& source) {
	std::vector<token> tokens;
	for (const auto& c : source) {
		switch (c) {
			case ' ':
			case '\t':
				continue;
			case '+':
				tokens.push_back({token_type::ADD, "+"});
			default:
				break;
		}
	}
	return tokens;
}

std::vector<token> tokenize_file(const std::string& filepath) {
	std::ifstream source{filepath};
	if (!source.is_open()) {
		throw std::runtime_error("could not open file");
	}
	return tokenize(std::string{std::istreambuf_iterator<char>{source}, {}});
}

}  // namespace lexer
}  // namespace frit
