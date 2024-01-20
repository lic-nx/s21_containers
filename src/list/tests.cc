#include <gtest/gtest.h>
#include <list>
#include "s21_list.h"

TEST(ListTest, DefaultConstructor) {
  s21::list<int> my_list;
  EXPECT_EQ(my_list.size(), 0);
  EXPECT_TRUE(my_list.empty());
}

TEST(ListTest, DefaultConstructor2) {
  s21::list<int> my_list(3);
  EXPECT_EQ(my_list.size(), 3);
  EXPECT_TRUE(!my_list.empty());
}

TEST(ListTest, CompareLists) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.push_front(0);
  EXPECT_EQ(my_list.get_elenemt(),0);
  int i = 0;
  for (auto iter =  my_list.begin(); iter !=  my_list.end(); iter++)
    {
      EXPECT_EQ(*iter,i);
      i++;
    }
  my_list.next_el();
  EXPECT_EQ(my_list.get_elenemt(),1);
  EXPECT_EQ(my_list.size(),6);
}


TEST(ListTest, CompareLists1) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  s21::list<int> my_list2(my_list);
   my_list2.push_front(0);
  EXPECT_EQ(my_list2.get_elenemt(),0);
  int i = 0;
  for (auto iter =  my_list2.begin(); iter !=  my_list2.end(); iter++)
    {
      EXPECT_EQ(*iter,i);
      i++;
    }

  EXPECT_EQ(my_list2.size(),6);
}

TEST(ListTest, moveTest) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  s21::list<int> my_list2(my_list);
   my_list2.push_front(0);
  EXPECT_EQ(my_list2.get_elenemt(),0);
  int i = 0;
  for (auto iter =  my_list2.begin(); iter !=  my_list2.end(); iter++)
    {
      EXPECT_EQ(*iter,i);
      i++;
    }

  EXPECT_EQ(my_list2.size(),6);
}


TEST(ListTest, moveTest2) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  s21::list<int> my_list2 = my_list;
  // my_list2 = my_list;
  my_list2.push_front(0);
  EXPECT_EQ(my_list2.get_elenemt(),0);
  int i = 0;
  for (auto iter =  my_list2.begin(); iter !=  my_list2.end(); iter++)
    {
      EXPECT_EQ(*iter,i);
      i++;
    }

  EXPECT_EQ(my_list2.size(),6);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}