#include <iostream>

#include "lexer.h"

std::string get_token_type_name(frit::token_type type) {
	switch (type) {
		case frit::token_type::number:
			return "number";
		case frit::token_type::ident:
			return "indent";
		case frit::token_type::add:
			return "add";
		case frit::token_type::sub:
			return "sub";
		case frit::token_type::mul:
			return "mul";
		case frit::token_type::div:
			return "div";
		case frit::token_type::mod:
			return "mod";
		case frit::token_type::lparen:
			return "lparen";
		case frit::token_type::rparen:
			return "rparen";
	}
	return "missing_token";
}

int shell() {
	std::string code;
	while (std::getline(std::cin, code)) {
		if (code == "exit") {
			break;
		}
		try {
			for (const auto& token : frit::lexer::tokenize(code)) {
				printf("[%s] %s\n", get_token_type_name(token.type).c_str(), token.value.c_str());
			}
		} catch (const std::exception& ex) {
			printf("%s\n", ex.what());
		}
	}
	return 0;
}

int main(int argc, char** argv) {
	if (argc == 1) {
		return shell();
	}
	return 0;
}
