#include <fmt/format.h>

#include <string>
#include <vector>

#include "frit_export.h"

namespace frit {

enum class token_type { number, ident, add, sub, mul, div, mod, lparen, rparen };

struct token {
	token_type type;
	std::string value;
	inline bool operator==(const token& other) const { return type == other.type && value == other.value; }
};

class lexer_exception : public std::exception {
public:
	explicit lexer_exception(const std::string& message, const std::pair<int, int>& position)
		: m_message(std::move(fmt::format("{} @{}:{}", message, position.first, position.second))) {}

	inline const char* what() const noexcept override { return m_message.c_str(); }

private:
	std::string m_message{};
};

namespace lexer {

std::vector<token> FRIT_EXPORT tokenize(const std::string& source);
std::vector<token> FRIT_EXPORT tokenize_file(const std::string& filepath);

}  // namespace lexer

}  // namespace frit
