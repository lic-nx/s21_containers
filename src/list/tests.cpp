#include <gtest/gtest.h>
#include "s21_list.h"


TEST(VectorTest, Constructor_initializer_list_1) {
  s21::list<int> A(2);
  A(3);
  
  EXPECT_EQ(3, A.get_elenemt);
}


TEST(VectorTest, Constructor_initializer_list_2) {
  s21::list<int> test({1,2,3});
  // std:: cout<<test.get_elenemt()<<"\n"<<test.next_el();
  
  EXPECT_EQ(1, A.get_elenemt);
  A.next_el();
  EXPECT_EQ(2, A.get_elenemt());
  A.next_el()
  EXPECT_EQ(3, A.get_elenemt());
}

s21::list<int> test({1,2,3});
    std:: cout<<test.get_elenemt()<<"\n"<<test.next_el();

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}