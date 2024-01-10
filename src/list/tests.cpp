#include <gtest/gtest.h>
#include "s21_list.h"


TEST(VectorTest, Constructor_initializer_list_1) {
  s21::list<int> A(2);
  A(3);
  
  EXPECT_EQ(3, A.get_elenemt);
}


int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}