#include <gtest/gtest.h>

#include "lexer.h"

TEST(DummyTest, BasicAssertions) { EXPECT_EQ(frit::lexer{}.test(), 0); }
