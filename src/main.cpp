#include <iostream>

#include "lexer.h"

int shell() {
	std::string input;
	while (input != "exit") {
		std::cin >> input;
		for (const auto& t : frit::lexer::tokenize(input)) {
			std::cout << t.value << std::endl;
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
