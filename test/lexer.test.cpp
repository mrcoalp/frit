#include "lexer.h"

#include "assertions.h"

using namespace frit;

int main() {
	std::vector<token> expected{
		{token_type::number, "1"},
		{token_type::add},
		{token_type::number, "2"},
	};

	require(lexer::tokenize("1+2") == expected);

	expected = {
		{token_type::number, "1.3"},
		{token_type::mul},
		{token_type::number, "2.6"},
	};

	require(lexer::tokenize("1.3*2.6") == expected);

	try {
		lexer::tokenize("2.6.2");
		require(false);
	} catch (const lexer_exception& err) {
		require(std::string{"invalid syntax at [1:4]"} == err.what());
	}

	return 0;
}
