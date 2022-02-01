#include <string>
#include <vector>

#include "frit_export.h"

namespace frit {
enum class token_type { INT, IDENT, ADD, SUB, MUL, DIV };

struct FRIT_EXPORT token {
	token_type type;
	std::string value;
};

namespace lexer {
std::vector<token> FRIT_EXPORT tokenize(const std::string& source);
std::vector<token> FRIT_EXPORT tokenize_file(const std::string& filepath);
}  // namespace lexer
}  // namespace frit
