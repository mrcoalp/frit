#pragma once

#include <string>

namespace frit {
enum class token_type { number, ident, add, sub, mul, div, mod, lparen, rparen };

struct token {
	token_type type;
	std::string value;
	inline bool operator==(const token& other) const { return type == other.type && value == other.value; }
};
}  // namespace frit
