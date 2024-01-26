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


TEST(ListTest, first) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.push_back(6);
  EXPECT_EQ(my_list.back(),6);
  my_list.pop_back();
  EXPECT_EQ(my_list.back(),5);
  my_list.pop_front();
  EXPECT_EQ(my_list.front(),2);
}

TEST(ListTest,  insert) {
  s21::list<int> our_list= {1,2,3};
  std::list<int> std_list = {1,2,3};
  s21::list<int>::iterator our_it;
  our_it = our_list.begin();
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  our_list.insert(our_it, 5);
  std_list.insert(std_it, 5);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.insert(our_it, 7);
  std_list.insert(std_it, 7);
  our_list.insert(our_it, 9);
  std_list.insert(std_it, 9);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(ListTest, Merge) {
  s21::list<int> our_list_first = {1};
  s21::list<int> our_list_second = {2, 3, 4, 5};
  std::list<int> std_list_first = {1};
  std::list<int> std_list_second = {2, 3, 4, 5};
  our_list_first.merge(our_list_second);
  std_list_first.merge(std_list_second);
  EXPECT_EQ(our_list_first.front(), std_list_first.front());
  EXPECT_EQ(our_list_first.back(), std_list_first.back());
  EXPECT_EQ(our_list_second.empty(), std_list_second.empty());
}

TEST(ListTest, Reverse) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  our_list.reverse();
  std_list.reverse();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(ListTest, Sort) {
  s21::list<int> our_list = {2, 4, 1, 3, 5};
  std::list<int> std_list = {2, 4, 1, 3, 5};
  s21::list<int>::iterator our_it;
  std::list<int>::iterator std_it;

  our_list.sort();
  std_list.sort();
  EXPECT_EQ(our_list.front(), std_list.front());
  our_it = our_list.begin();
  std_it = std_list.begin();
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}