#include <string>
#include <vector>

#include "frit_export.h"

namespace frit {
enum class token_type { number, ident, add, sub, mul, div, mod, lparen, rparen };

struct FRIT_EXPORT token {
	token_type type;
	std::string value;
	inline bool operator==(const token& other) const { return type == other.type && value == other.value; }
};

class FRIT_EXPORT lexer {
public:
	std::vector<token> tokenize(const std::string& source);
	std::vector<token> tokenize_file(const std::string& filepath);

private:
	char m_current_char{};
	std::pair<int, int> m_position{1, 1};
};

class FRIT_EXPORT lexer_exception : public std::exception {
public:
	explicit lexer_exception(std::string message) : m_message(std::move(message)) {}

	inline const char* what() const noexcept override { return m_message.c_str(); }

private:
	std::string m_message{};
};

}  // namespace frit
