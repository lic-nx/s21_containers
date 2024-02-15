#include <gtest/gtest.h>

#include <set>
#include <string>

#include "../containers.h"


TEST(set_test, constr1) {
  s21::set<int> s1 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::set<int> s2 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  s21::set<int>::iterator it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, constr2) {
  s21::set<int> s1 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::set<int> s2 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, constr3) {
  s21::set<int> s1;
  std::set<int> s2;
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(set_test, constr4) {
  s21::set<int> s1 = {3, 2, 1};
  std::set<int> s2 = {3, 2, 1};
  auto s11 = std::move(s1);
  auto s22 = std::move(s2);
  auto it1 = s11.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s11.size(), s22.size());
}

TEST(set_test, constr5) {
  s21::set<int> s1 = {3, 2, 1};
  std::set<int> s2 = {3, 2, 1};
  auto s11 = s1;
  auto s22 = s2;
  auto it1 = s1.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s11.size(), s22.size());
}

TEST(set_test, constr6) {
  s21::set<int> s1 = {-10, -20, -1};
  std::set<int> s2 = {-10, -20, -1};
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(set_test, constr7) {
  s21::set<int> s1 = {3, 2, 1};
  std::set<int> s2 = {3, 2, 1};
  s21::set<int> s11;
  std::set<int> s22;
  s11 = std::move(s1);
  s22 = std::move(s2);
  auto it1 = s11.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s11.size(), s22.size());
}

TEST(set_test, begin1) {
  s21::set<int> s1 = {3, 2, 1};
  std::set<int> s2 = {3, 2, 1};
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  EXPECT_EQ(*it1, *it2);
}

TEST(set_test, empty1) {
  s21::set<int> s1 = {3, 2, 1};
  std::set<int> s2 = {3, 2, 1};
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(set_test, empty2) {
  s21::set<int> s1 = {3, 2, 1};
  std::set<int> s2 = {3, 2, 1};
  s1.clear();
  s2.clear();
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(set_test, size1) {
  s21::set<int> s1;
  std::set<int> s2;
  s1.insert(1);
  s2.insert(1);
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(set_test, size2) {
  s21::set<int> s1 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::set<int> s2 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(set_test, size3) {
  s21::set<int> s1 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::set<int> s2 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  s1.clear();
  s2.clear();
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(set_test, clear1) {
  s21::set<double> s1 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::set<double> s2 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  s1.clear();
  s2.clear();
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(set_test, clear2) {
  s21::set<double> s1;
  std::set<double> s2;
  s1.clear();
  s2.clear();
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(set_test, clear3) {
  s21::set<double> s1 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::set<double> s2 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  s1.clear();
  s2.clear();
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
  s1.clear();
  s2.clear();
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(set_test, insert1) {
  s21::set<double> s1 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::set<double> s2 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  EXPECT_EQ(s1.size(), s2.size());
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(set_test, insert2) {
  s21::set<double> s1 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::set<double> s2 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.insert(-1).second, s2.insert(-1).second);
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
  EXPECT_EQ(s1.size(), s2.size());
}

// TEST(set_test, insert3) {
//   s21::set<double> s1 = {3, 9, 8, 7, 6, 5, 4, 3, 2, 1,0};
//   std::set<double> s2 = {3, 9, 8, 7, 6, 5, 4, 3, 2, 1,0};
//   EXPECT_EQ(s1.size(), s2.size());
//   auto it1 = s1.begin();
//   for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2) {
//     EXPECT_EQ(*it1, *it2);
//   }
//   EXPECT_EQ(s1.size(), s2.size());
// }

TEST(set_test, erase1) {
  s21::set<double> s1 = {3, 9, 8, 7, 6, 5, 4, 2, 1, 0};
  std::set<double> s2 = {3, 9, 8, 7, 6, 5, 4, 2, 1, 0};
  EXPECT_EQ(s1.size(), s2.size());
  s1.erase(s1.begin());
  s2.erase(s2.begin());
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(set_test, erase2) {
  s21::set<double> s1 = {3, 9, 8, 7, 6, 5, 4, 2, 1, 0};
  std::set<double> s2 = {3, 9, 8, 7, 6, 5, 4, 2, 1, 0};
  s1.erase(s1.begin());
  s2.erase(s2.begin());
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(*it1, *it2);
}

TEST(set_test, swap1) {
  s21::set<int> s1 = {3, 9, 8, 7, 6, 5, 4, 2, 1, 0};
  std::set<int> s2 = {3, 9, 8, 7, 6, 5, 4, 2, 1, 0};
  s21::set<int> s11;
  std::set<int> s22;
  s1.swap(s11);
  s2.swap(s22);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s11.size(), s22.size());
  auto it1 = s11.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, swap2) {
  s21::set<int> s1 = {3, 9, 8, 7, 6, 5, 4, 2, 1, 0};
  std::set<int> s2 = {3, 9, 8, 7, 6, 5, 4, 2, 1, 0};
  s21::set<int> s11 = {38, 329, 11, 19, 117};
  std::set<int> s22 = {38, 329, 11, 19, 117};
  s1.swap(s11);
  s2.swap(s22);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s11.size(), s22.size());
  auto it1 = s11.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, find1) {
  s21::set<int> s1 = {3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::set<int> s2 = {3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  EXPECT_EQ(*(s1.find(3)), *(s2.find(3)));
}

TEST(set_test, contains1) {
  s21::set<int> s1 = {3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  EXPECT_EQ(s1.contains(1), true);
}

TEST(set_test, contains2) {
  s21::set<int> s1 = {3, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  EXPECT_EQ(s1.contains(0), false);
}

TEST(set_test, iter1) {
  s21::set<int> s1 = {3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::set<int> s2 = {3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  for (int i = 0; i < 9; i++) ++it1, ++it2;
  EXPECT_EQ(*it1, *it2);
}

TEST(set_test, iter3) {
  s21::set<int> s1 = {3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  auto it1 = s1.end();
  auto it2 = s1.end();
  EXPECT_EQ(it1 == it2, true);
}

TEST(set_test, iter4) {
  s21::set<int> s1 = {3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  auto it1 = s1.end();
  auto it2 = s1.end();
  EXPECT_EQ(it1 != it2, false);
}

TEST(set_test, iter5) {
  s21::set<int> s1 = {3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  auto it1 = s1.end();
  auto it2 = s1.end();
  EXPECT_EQ(it1 == it2, true);
}

TEST(set_test, merge1) {
  s21::set<int> s1 = {3, 9, 8, 7, 6, 5, 4, 2, 1, 0};
  std::set<int> s2 = {3, 9, 8, 7, 6, 5, 4, 2, 1, 0};
  s21::set<int> s11 = {112, 1131, 1489, 3589, 38629};
  std::set<int> s22 = {112, 1131, 1489, 3589, 38629};
  s1.merge(s11);
  s2.merge(s22);
  EXPECT_EQ(s1.size(), s2.size());
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(Set, emplase) {
  s21::set<int> s = {3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::set<int> o = {3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

  auto r = s.insert_many(100, 200, 42, 400);

  auto pr3 = o.emplace(42);

  EXPECT_EQ(*(r[2].first), *(pr3.first));
  EXPECT_EQ(r[2].second, pr3.second);
}

using namespace std;

// ------- Set Functions -------

TEST(Set_Functions, initializer_list_constructor) {
  std::set<int> std_set{3, 9, 8, 7, 6, 5, 4, 2, 1, 0};
  s21::set<int> s21_set{3, 9, 8, 7, 6, 5, 4, 2, 1, 0};
  EXPECT_EQ(std_set.size(), s21_set.size());

  // пустое множество
  std::set<int, char> std_empty_set{};
  std::set<int, char> s21_empty_set{};
  EXPECT_EQ(std_empty_set.size(), s21_empty_set.size());
}

TEST(Set_Functions, copy_constructor) {
  std::set<int> std_copy_set{3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::set<int> std_set = std_copy_set;

  s21::set<int> s21_copy_set{3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  s21::set<int> s21_set = s21_copy_set;

  auto std_it = std_set.begin();
  auto s21_it = s21_set.begin();

  for (; std_it != std_set.end(); ++std_it, ++s21_it)
    EXPECT_EQ(*std_it, *s21_it);
}

TEST(Set_Functions, move_constructor) {
  std::set<int> std_moving_set{3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::set<int> std_set = std::move(std_moving_set);

  s21::set<int> s21_moving_set{3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  s21::set<int> s21_set = std::move(s21_moving_set);

  auto std_it = std_set.begin();
  auto s21_it = s21_set.begin();

  for (; std_it != std_set.end(); ++std_it, ++s21_it)
    EXPECT_EQ(*std_it, *s21_it);

  // // перемещение пустого множества
  std::set<int> std_null_set;
  std::set<int> std_set_2 = std::move(std_null_set);

  s21::set<int> s21_null_set;
  s21::set<int> s21_set_2 = std::move(s21_null_set);

  EXPECT_EQ(std_null_set.size(), s21_null_set.size());
  EXPECT_EQ(std_set_2.size(), s21_set_2.size());
}

TEST(Set_Functions, assignment_operator_overload) {
  std::set<int> std_set{3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  s21::set<int> s21_set{3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

  std::set<int> std_set_2{855, 743, 645, 523, 446, 132, -1123};
  s21::set<int> s21_set_2{855, 743, 645, 523, 446, 132, -1123};

  std_set_2 = std::move(std_set);
  s21_set_2 = std::move(s21_set);

  auto std_it = std_set_2.begin();
  auto s21_it = s21_set_2.begin();

  for (; std_it != std_set_2.end(); ++std_it, ++s21_it)
    EXPECT_EQ(*std_it, *s21_it);
}

// ------- Set Iterators -------

TEST(Set_Iterators, begin) {
  std::set<int> std_set{3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  s21::set<int> s21_set{3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

  EXPECT_EQ(*(std_set.begin()), *(s21_set.begin()));
}

// ------- Set Capacity -------

TEST(Set_Capacity, empty) {
  std::set<int> std_set{3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  s21::set<int> s21_set{3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  EXPECT_EQ(std_set.empty(), s21_set.empty());

  // пустое множество
  std::set<int, char> std_empty_set{};
  std::set<int, char> s21_empty_set{};
  EXPECT_EQ(std_empty_set.empty(), s21_empty_set.empty());
}

TEST(Set_Capacity, size) {
  std::set<int> std_set{3, 9, 8, 7, 6, 5, 4, 2, 1, 0};
  s21::set<int> s21_set{3, 9, 8, 7, 6, 5, 4, 2, 1, 0};
  EXPECT_EQ(std_set.size(), s21_set.size());

  // пустое множество
  std::set<int, char> std_empty_set{};
  std::set<int, char> s21_empty_set{};
  EXPECT_EQ(std_empty_set.size(), s21_empty_set.size());
}

TEST(Set_Capacity, max_size) {
  std::set<int, char> std_empty_set{};
  std::set<int, char> s21_empty_set{};
  EXPECT_EQ(std_empty_set.max_size(), s21_empty_set.max_size());
}

// ------- Set Modifiers -------

TEST(Set_Modifiers, clear) {
  std::set<int> std_set{3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  s21::set<int> s21_set{3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

  std_set.clear();
  s21_set.clear();

  std::set<int, char> std_empty_set{};
  std::set<int, char> s21_empty_set{};

  EXPECT_EQ(std_set.size(), std_empty_set.size());
  EXPECT_EQ(s21_set.size(), s21_empty_set.size());
}

TEST(Set_Modifiers, insert) {
  std::set<int> std_set{3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  s21::set<int> s21_set{3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

  auto std_insert_pair = std_set.insert(350);
  auto s21_insert_pair = s21_set.insert(350);

  EXPECT_EQ(std_insert_pair.second, s21_insert_pair.second);

  auto std_it = std_set.begin();
  auto s21_it = s21_set.begin();

  for (; std_it != std_set.end(); ++std_it, ++s21_it)
    EXPECT_EQ(*std_it, *s21_it);
}

TEST(Set_Modifiers, erase) {
  std::set<int> std_set{3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  s21::set<int> s21_set{3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

  auto std_it = std_set.begin();
  auto s21_it = s21_set.begin();

  std_set.erase(std_it);
  s21_set.erase(s21_it);

  std_it = std_set.begin();
  s21_it = s21_set.begin();
  for (; std_it != std_set.end(); ++std_it, ++s21_it)
    EXPECT_EQ(*std_it, *s21_it);
}

TEST(Set_Modifier, swap) {
  std::set<int> std_set{3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  s21::set<int> s21_set{3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

  std::set<int> std_set_2{551, 843, 745, 263, 456, 142, -1123};
  s21::set<int> s21_set_2{551, 843, 745, 263, 456, 142, -1123};

  std_set.swap(std_set_2);
  s21_set.swap(s21_set_2);

  auto std_it = std_set.begin();
  auto s21_it = s21_set.begin();

  for (; std_it != std_set.end(); ++std_it, ++s21_it)
    EXPECT_EQ(*std_it, *s21_it);

  std_it = std_set_2.begin();
  s21_it = s21_set_2.begin();
  for (; std_it != std_set_2.end(); ++std_it, ++s21_it)
    EXPECT_EQ(*std_it, *s21_it);
}

TEST(Set_Modifier, merge) {
  std::set<int> std_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};
  s21::set<int> s21_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};

  std::set<int> std_set_2{551, 843, 745, 263, 456, 142, -1123};
  s21::set<int> s21_set_2{551, 843, 745, 263, 456, 142, -1123};

  std_set.merge(std_set_2);
  s21_set.merge(s21_set_2);

  auto std_it = std_set.begin();
  auto s21_it = s21_set.begin();
  for (; std_it != std_set.end(); ++std_it, ++s21_it)
    EXPECT_EQ(*std_it, *s21_it);
}

// ------- Set Lookup -------

TEST(Set_Lookup, find) {
  std::set<int> std_set{551, 843, 745, 263, 456, 142, -1123, 9};
  s21::set<int> s21_set{551, 843, 745, 263, 456, 142, -1123, 9};

  auto std_it = std_set.find(9);
  auto s21_it = s21_set.find(9);
  EXPECT_EQ(*std_it, *s21_it);
}

TEST(Set_Lookup, contains) {
  std::set<int> std_set{551, 843, 745, 263, 456, 142, -1123, -10};
  s21::set<int> s21_set{551, 843, 745, 263, 456, 142, -1123, -10};

  EXPECT_EQ(true, s21_set.contains(-10));
  EXPECT_EQ(false, s21_set.contains(9555));
}

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
