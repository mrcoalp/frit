#include "parser.h"

#include "node.h"
#include "token.h"

namespace frit {

void parser::advance() {
	if (m_current_index < m_tokens.size()) {
		m_current_token = &m_tokens.at(m_current_index);
		++m_current_index;
	}
}

std::unique_ptr<node> parser::factor() {
	if (m_current_token->type == token_type::number) {
		advance();
		return std::make_unique<number_node>(*m_current_token);
	}
	return {nullptr};
}

std::unique_ptr<node> parser::term() {
	auto left = factor();

	auto check_op = [&]() -> bool {
		switch (m_current_token->type) {
			case token_type::mul:
			case token_type::div:
				return true;
			default:
				return false;
		}
	};

	while (check_op()) {
		auto* op_token = m_current_token;
		advance();
		auto right = factor();
		left = std::make_unique<bin_op_node>(left.get(), *op_token, right.get());
	}
	return left;
}

std::unique_ptr<node> parser::expression() {
	auto left = term();

	auto check_op = [&]() -> bool {
		switch (m_current_token->type) {
			case token_type::add:
			case token_type::sub:
				return true;
			default:
				return false;
		}
	};

	while (check_op()) {
		auto* op_token = m_current_token;
		advance();
		auto right = term();
		left = std::make_unique<bin_op_node>(left.get(), *op_token, right.get());
	}
	return left;
}

std::unique_ptr<node> parser::parse() { return expression(); }

}  // namespace frit
