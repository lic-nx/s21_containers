#include <gtest/gtest.h>

#include "s21_list.h"

TEST(mull, HanglesInitedEqualMatrices) {
  // TestS21Matrix A, B;
  s21::member<int> A(3);
  EXPECT_EQ(3, A.value_get());
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
