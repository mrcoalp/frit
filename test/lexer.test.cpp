#include "lexer.h"

#include <gtest/gtest.h>

using namespace frit;

TEST(lexer, integers) {
	std::vector<token> expected{
		{token_type::number, "1"},
		{token_type::add},
		{token_type::number, "2"},
	};
	EXPECT_EQ(lexer::tokenize("1+2"), expected);
}

TEST(lexer, floats) {
	std::vector<token> expected{
		{token_type::number, "1.3"},
		{token_type::mul},
		{token_type::number, "2.6"},
	};
	EXPECT_EQ(lexer::tokenize("1.3*2.6"), expected);
}

TEST(lexer, float_exception) {
	try {
		lexer::tokenize("2.6.2");
		FAIL();
	} catch (const lexer_exception& err) {
		EXPECT_STREQ("invalid syntax @1:4", err.what());
	}
}
