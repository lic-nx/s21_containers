#include <gtest/gtest.h>

#include "s21_list.h"

TEST(ListTest, DefaultConstructor) {
  s21::list<int> my_list;
  EXPECT_EQ(my_list.size(), 0);
  // EXPECT_TRUE(my_list.empty());
}


int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}