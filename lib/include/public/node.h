#pragma once

#include <memory>
#include <utility>

#include "frit_export.h"
#include "token.h"

namespace frit {

struct node {
	virtual ~node() = default;
};

struct FRIT_EXPORT number_node : public node {
	token tok;
	explicit number_node(token tok_) : tok(std::move(tok_)) {}
};

struct FRIT_EXPORT bin_op_node : public node {
	std::unique_ptr<node> left;
	token operation;
	std::unique_ptr<node> right;
	bin_op_node(node* left_, token op, node* right_) : left(left_), operation(std::move(op)), right(right_) {}
};

}  // namespace frit
