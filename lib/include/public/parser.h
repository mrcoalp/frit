#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "frit_export.h"

namespace frit {
class token;
class node;

class FRIT_EXPORT parser {
public:
	explicit parser(std::vector<token> tokens) : m_tokens(std::move(tokens)) { advance(); }

	std::unique_ptr<node> parse();

private:
	std::vector<token> m_tokens{};
	token* m_current_token{nullptr};
	size_t m_current_index{0};

	void advance();
	std::unique_ptr<node> factor();
	std::unique_ptr<node> term();
	std::unique_ptr<node> expression();
};
}  // namespace frit
