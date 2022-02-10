#pragma once

#include <string>
#include <vector>

#include "frit_export.h"
#include "token.h"

namespace frit {

class lexer_exception : public std::exception {
public:
	explicit lexer_exception(std::string message) : m_message(std::move(message)) {}

	lexer_exception(const std::string& message, const std::pair<int, int>& position);

	inline const char* what() const noexcept override { return m_message.c_str(); }

private:
	std::string m_message{};
};

namespace lexer {

std::vector<token> FRIT_EXPORT tokenize(const std::string& source);
std::vector<token> FRIT_EXPORT tokenize_file(const std::string& filepath);

}  // namespace lexer

}  // namespace frit
