#include <iostream>

#include "lexer.h"

int main(int argc, char** argv) {
	std::cout << frit::lexer{}.hello() << std::endl;
	return 0;
}
