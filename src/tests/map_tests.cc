#include <gtest/gtest.h>

#include <map>
#include <string>

#include "../containers.h"

using namespace std;

// ------- Map Functions -------

TEST(Map_Functions, default_constructor) {
  std::map<int, char> std_map;
  std_map[0] = 'k';
  
  s21::map<int, char> s21_map;
  s21_map[0] = 'k';

  EXPECT_EQ(std_map[0], s21_map[0]);
  EXPECT_EQ(std_map.size(), s21_map.size());
}

TEST(Map_Functions, initializer_list_constructor) {
  std::map<int, char> std_map{{3, 'x'}, {2, 'y'}, {1, 'z'}};
  s21::map<int, char> s21_map{{3, 'x'}, {2, 'y'}, {1, 'z'}};

  for (int i = 0; i <= 2; i++) EXPECT_EQ(std_map[i], s21_map[i]);

  EXPECT_EQ(std_map.size(), s21_map.size());

  // пустой словарь
  std::map<int, char> std_empty_map{};
  std::map<int, char> s21_empty_map{};
  EXPECT_EQ(std_empty_map.size(), s21_empty_map.size());
}

TEST(Map_Functions, copy_constructor) {
  std::map<int, char> std_copy_map{{3, 'x'}, {2, 'y'}, {1, 'z'}};
  std::map<int, char> std_map = std_copy_map;

  s21::map<int, char> s21_copy_map{{3, 'x'}, {2, 'y'}, {1, 'z'}};
  s21::map<int, char> s21_map = s21_copy_map;

  for (int i = 0; i <= 2; i++) EXPECT_EQ(std_map[i], s21_map[i]);

  EXPECT_EQ(std_map.size(), s21_map.size());
}

TEST(Map_Functions, move_constructor) {
  std::map<int, char> std_moving_map{{3, 'x'}, {2, 'y'}, {1, 'z'}};
  std::map<int, char> std_map = std::move(std_moving_map);

  s21::map<int, char> s21_moving_map{{3, 'x'}, {2, 'y'}, {1, 'z'}};
  s21::map<int, char> s21_map = std::move(s21_moving_map);

  EXPECT_EQ(std_moving_map.size(), s21_moving_map.size());
  EXPECT_EQ(std_map.size(), s21_map.size());

  std::map<int, char> std_null_map;
  std::map<int, char> std_map_2 = std::move(std_moving_map);

  s21::map<int, char> s21_null_map;
  s21::map<int, char> s21_map_2 = std::move(s21_moving_map);

  EXPECT_EQ(std_null_map.size(), s21_null_map.size());
  EXPECT_EQ(std_map_2.size(), s21_map_2.size());
}

TEST(Map_Functions, assignment_operator_overload) {
  std::map<int, char> std_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};
  s21::map<int, char> s21_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};

  std::map<int, char> std_map_2 = {{27, 'q'}, {26, 'w'}, {25, 'e'}};
  s21::map<int, char> s21_map_2 = {{27, 'q'}, {26, 'w'}, {25, 'e'}};

  std_map_2 = std::move(std_map);
  s21_map_2 = std::move(s21_map);

  for (int i = 0; i <= 2; i++) EXPECT_EQ(std_map_2[i], s21_map_2[i]);
}

// ------- Map Element access -------

TEST(Map_Element_access, at) {
  std::map<int, char> std_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};
  s21::map<int, char> s21_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};

  for (int i = 1; i <= 3; i++) EXPECT_EQ(std_map.at(i), s21_map.at(i));

  // пара в качестве ключа
  pair<int, char> p1;
  p1.first = 0;
  p1.second = 'b';

  std::map<pair<int, char>, string> std_map_2{{p1, "privet"}};
  s21::map<pair<int, char>, string> s21_map_2{{p1, "privet"}};
  EXPECT_EQ(std_map_2.at(p1), s21_map_2.at(p1));
}

TEST(Map_Element_access, square_brackets) {
  std::map<int, char> std_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};
  s21::map<int, char> s21_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};

  for (int i = 0; i <= 2; i++) EXPECT_EQ(std_map[i], s21_map[i]);

  // пара в качестве ключа
  pair<int, char> p1;
  p1.first = 1;
  p1.second = 'b';

  std::map<pair<int, char>, string> std_map_2{{p1, "pervi_simvol"}};
  s21::map<pair<int, char>, string> s21_map_2{{p1, "pervi_simvol"}};
  EXPECT_EQ(std_map_2[p1], s21_map_2[p1]);
}

// ------- Map Iterators -------

TEST(Map_Iterators, begin) {
  std::map<int, char> std_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};
  s21::map<int, char> s21_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};
  auto std_it = std_map.begin();
  auto s21_it = s21_map.begin();
  // EXPECT_EQ((*std_it).first, (s21_it).GetPtr()->GetKey());
  // EXPECT_EQ((*std_it).second, (s21_it).GetPtr()->GetValue());
  EXPECT_EQ((*std_it).first, (s21_it).GetPtr()->GetKey());
  EXPECT_EQ((*std_it).second, (s21_it).GetPtr()->GetValue());
}

TEST(Map_Iterators, end) {
  std::map<int, char> std_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};
  s21::map<int, char> s21_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};
  auto std_it = --std_map.end();
  auto s21_it = s21_map.rbegin();
  EXPECT_EQ((*std_it).first, s21_it.GetPtr()->GetKey());
  EXPECT_EQ((*std_it).second, s21_it.GetPtr()->GetValue());
}

// ------- Map Capacity -------

TEST(Map_Capacity, empty) {
  std::map<int, char> std_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};
  s21::map<int, char> s21_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};
  EXPECT_EQ(std_map.empty(), s21_map.empty());

  std::map<int, char> std_empty_map{};
  std::map<int, char> s21_empty_map{};
  EXPECT_EQ(std_empty_map.empty(), s21_empty_map.empty());
}

TEST(Map_Capacity, size) {
  std::map<int, char> std_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};
  s21::map<int, char> s21_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};
  EXPECT_EQ(std_map.size(), s21_map.size());

  std::map<int, char> std_empty_map{};
  std::map<int, char> s21_empty_map{};
  EXPECT_EQ(std_empty_map.size(), s21_empty_map.size());
}

TEST(Map_Capacity, max_size) {
  std::map<int, char> std_empty_map{};
  std::map<int, char> s21_empty_map{};
  EXPECT_EQ(std_empty_map.max_size(), s21_empty_map.max_size());
}

// ------- Map Modifiers -------

TEST(Map_Modifiers, clear) {
  std::map<int, char> std_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};
  s21::map<int, char> s21_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};

  std_map.clear();
  s21_map.clear();

  std::map<int, char> std_empty_map{};
  std::map<int, char> s21_empty_map{};

  EXPECT_EQ(std_map.size(), std_empty_map.size());
  EXPECT_EQ(s21_map.size(), s21_empty_map.size());
}

TEST(Map_Modifier, insert_type_one) {
  std::map<int, char> std_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};
  s21::map<int, char> s21_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};

  auto std_insert_pair = std_map.insert({4, 'f'});
  auto s21_insert_pair = s21_map.insert({4, 'f'});
  EXPECT_EQ(std_insert_pair.first->first, ((s21_insert_pair.first)).GetPtr()->GetKey());
  EXPECT_EQ(std_insert_pair.first->second, ((s21_insert_pair.first)).GetPtr()->GetValue());
  EXPECT_EQ(std_insert_pair.second, s21_insert_pair.second);
  EXPECT_EQ(std_map[4], s21_map[4]);
}

TEST(Map_Modifier, insert_type_two) {
  std::map<int, char> std_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};
  s21::map<int, char> s21_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};

  auto std_insert_pair = std_map.insert({5, 'f'});
  auto s21_insert_pair = s21_map.insert({5, 'f'});
  EXPECT_EQ(std_insert_pair.first->first, ((s21_insert_pair.first)).GetPtr()->GetKey());
  EXPECT_EQ(std_insert_pair.first->second, ((s21_insert_pair.first)).GetPtr()->GetValue());
  EXPECT_EQ(std_insert_pair.second, s21_insert_pair.second);

  EXPECT_EQ(std_map[4], s21_map[4]);
}

TEST(Map_Modifier, insert_or_assign) {
  s21::map<int, char> s21_map = {{0, 'q'}, {1, 'w'}, {2, 'e'}};

  auto s21_insert_pair = s21_map.insert_or_assign(4, 'g');
  EXPECT_EQ(true, s21_insert_pair.second);
  EXPECT_EQ('g', s21_map[4]);

  s21_insert_pair = s21_map.insert_or_assign(0, 'k');
  EXPECT_EQ(false, s21_insert_pair.second);
  EXPECT_EQ('k', s21_map[0]);
}

TEST(Map_Modifier, erase) {
  std::map<int, char> std_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};
  s21::map<int, char> s21_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};

  auto std_it = std_map.begin();
  auto s21_it = s21_map.begin();

  ++std_it;
  ++s21_it;

  std_map.erase(std_it);
  s21_map.erase(s21_it);

  std_it = std_map.begin();
  s21_it = s21_map.begin();
  for (; std_it != std_map.end(); ++std_it, ++s21_it) {
    EXPECT_EQ((*std_it).first, (s21_it).GetPtr()->GetKey());
    EXPECT_EQ((*std_it).second, (s21_it).GetPtr()->GetValue());
  }
}

TEST(Map_Modifier, swap) {
  std::map<int, char> std_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};
  s21::map<int, char> s21_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};

  std::map<int, char> std_map_2 = {{27, 'q'}, {26, 'w'}, {25, 'e'}};
  s21::map<int, char> s21_map_2 = {{27, 'q'}, {26, 'w'}, {25, 'e'}};

  std_map.swap(std_map_2);
  s21_map.swap(s21_map_2);

  for (int i = 0; i <= 2; i++) EXPECT_EQ(std_map_2[i], s21_map_2[i]);

  for (int i = 26; i >= 24; i--) EXPECT_EQ(std_map[i], s21_map[i]);
}

TEST(Map_Modifier, merge) {
  std::map<int, char> std_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};
  s21::map<int, char> s21_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};

  std::map<int, char> std_map_2 = {{27, 'q'}, {26, 'w'}, {25, 'e'}};
  s21::map<int, char> s21_map_2 = {{27, 'q'}, {26, 'w'}, {25, 'e'}};

  std_map.merge(std_map_2);
  s21_map.merge(s21_map_2);

  auto std_it = std_map.begin();
  auto s21_it = s21_map.begin();
  for (; std_it != std_map.end(); ++std_it, ++s21_it) {
    EXPECT_EQ((*std_it).first, (s21_it).GetPtr()->GetKey());
    EXPECT_EQ((*std_it).second, (s21_it).GetPtr()->GetValue());
  }
}

// ------- Map Lookup -------

TEST(Map_Lookup, contains) {
  std::map<int, char> std_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};
  s21::map<int, char> s21_map = {{3, 'x'}, {2, 'y'}, {1, 'z'}};

  EXPECT_EQ(true, s21_map.contains(1));
  EXPECT_EQ(false, s21_map.contains(95));
}

TEST(map_test, constr1) {
  s21::map<int, int> m1 = {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {3, 3}};
  std::map<int, int> m2 = {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {3, 3}};
  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); ++it1, ++it2)
    EXPECT_EQ((it1).GetPtr()->GetValue(), (*it2).second);
  it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); ++it1, ++it2)
    EXPECT_EQ((it1).GetPtr()->GetKey(), (*it2).first);
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(map_test, constr2) {
  s21::map<int, int> m1;
  std::map<int, int> m2;
  EXPECT_EQ(m1.size(), m2.size());
  m1.insert({3, 3});
  m2.insert({3, 3});
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(map_test, constr3) {
  s21::map<int, int> m1 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  std::map<int, int> m2 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  auto m11 = m1;
  auto m22 = m2;
  auto it1 = m1.begin();
  for (auto it2 = m22.begin(); it2 != m22.end(); ++it2, ++it1)
    EXPECT_EQ((it1).GetPtr()->GetValue(), (*it2).second);
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m11.size(), m22.size());
}

TEST(map_test, constr4) {
  s21::map<int, int> m1 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  std::map<int, int> m2 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  auto m11 = std::move(m1);
  auto m22 = std::move(m2);
  auto it1 = m11.begin();
  for (auto it2 = m22.begin(); it2 != m22.end(); ++it2, ++it1)
    EXPECT_EQ((it1).GetPtr()->GetValue(), (*it2).second);
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m11.size(), m22.size());
}

TEST(map_test, at1) {
  s21::map<int, int> m1 = {{1, 11}, {2, 22}, {3, 33}, {4, 44}, {5, 55}};
  std::map<int, int> m2 = {{1, 11}, {2, 22}, {3, 33}, {4, 44}, {5, 55}};
  for (size_t i = 1; i < m1.size(); i++) EXPECT_EQ(m1.at(i), m2.at(i));
}

TEST(map_test, at3) {
  s21::map<int, int> m1 = {{1, 11}, {2, 22}, {3, 33}, {4, 44}, {5, 55}};
  std::map<int, int> m2 = {{1, 11}, {2, 22}, {3, 33}, {4, 44}, {5, 55}};
  EXPECT_EQ(m1.at(5), m2.at(5));
}

TEST(map_test, begin1) {
  s21::map<int, int> m1 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  std::map<int, int> m2 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  auto it1 = m1.begin();
  auto it2 = m2.begin();
  EXPECT_EQ((it1).GetPtr()->GetValue(), (*it2).second);
}

TEST(map_test, empty1) {
  s21::map<int, int> m1 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  std::map<int, int> m2 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(map_test, empty2) {
  s21::map<int, int> m1 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  std::map<int, int> m2 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  m1.clear();
  m2.clear();
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(map_test, size1) {
  s21::map<int, int> m1;
  std::map<int, int> m2;
  std::pair<int, int> pair = {2, 2};
  m1.insert(pair);
  m2.insert(pair);
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(map_test, size2) {
  s21::map<int, int> m1 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  std::map<int, int> m2 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(map_test, size3) {
  s21::map<int, int> m1 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  std::map<int, int> m2 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  m1.clear();
  m2.clear();
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(map_test, clear1) {
  s21::map<int, int> m1 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  std::map<int, int> m2 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  m1.clear();
  m2.clear();
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(map_test, clear2) {
  s21::map<int, int> m1;
  std::map<int, int> m2;
  m1.clear();
  m2.clear();
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(map_test, clear3) {
  s21::map<int, int> m1 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  std::map<int, int> m2 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  m1.clear();
  m2.clear();
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
  m1.clear();
  m2.clear();
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(map_test, insert1) {
  s21::map<int, int> m1 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  std::map<int, int> m2 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  std::pair<int, int> pair = {4, 2};
  EXPECT_EQ(m1.insert(pair).second, m2.insert(pair).second);
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(map_test, insert2) {
  s21::map<int, int> m1;
  std::map<int, int> m2;
  EXPECT_EQ(m1.empty(), m2.empty());
  std::pair<int, int> pair = {3, 1};
  EXPECT_EQ(m1.insert(pair).second, m2.insert(pair).second);
  EXPECT_EQ(m1.empty(), m2.empty());
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(map_test, erase1) {
  s21::map<int, int> m1 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  std::map<int, int> m2 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  EXPECT_EQ(m1.size(), m2.size());
  m1.erase(m1.begin());
  m2.erase(m2.begin());
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(map_test, erase2) {
  s21::map<int, int> m1 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  std::map<int, int> m2 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  m1.erase(m1.begin());
  m2.erase(m2.begin());
  auto it1 = m1.begin();
  auto it2 = m2.begin();
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ((it1).GetPtr()->GetValue(), (*it2).second);
}

TEST(map_test, swap1) {
  s21::map<int, int> m1 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  std::map<int, int> m2 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  s21::map<int, int> m11;
  std::map<int, int> m22;
  m1.swap(m11);
  m2.swap(m22);
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m11.size(), m22.size());
  auto it1 = m11.begin();
  for (auto it2 = m22.begin(); it2 != m22.end(); ++it1, ++it2)
    EXPECT_EQ((it1).GetPtr()->GetValue(), (*it2).second);
}

TEST(map_test, swap2) {
  s21::map<int, int> m1 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  std::map<int, int> m2 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  s21::map<int, int> m11 = {{345, 10}, {345, 10}, {1111, 10},
                            {111, 10}, {111, 10}, {111, 10}};
  std::map<int, int> m22 = {{345, 10}, {345, 10}, {1111, 10},
                            {111, 10}, {111, 10}, {111, 10}};
  EXPECT_EQ(m1.size(), m2.size());  // qestion
  m1.swap(m11);
  m2.swap(m22);
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m11.size(), m22.size());
  auto it1 = m11.begin();
  for (auto it2 = m22.begin(); it2 != m22.end(); ++it1, ++it2)
    EXPECT_EQ((it1).GetPtr()->GetValue(), (*it2).second);
}

TEST(map_test, contains1) {
  s21::map<int, int> m1 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  EXPECT_EQ(m1.contains(11), true);
}

TEST(map_test, contains2) {
  s21::map<int, int> m1 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  EXPECT_EQ(m1.contains(21), true);
}

TEST(map_test, merge2) {
  s21::map<int, int> m1 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  std::map<int, int> m2 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  s21::map<int, int> m11 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  std::map<int, int> m22 = {{11, 11}, {21, 22}, {33, 33}, {44, 44}, {55, 55}};
  m1.merge(m11);
  m2.merge(m22);
  EXPECT_EQ(m1.size(), m2.size());
  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); ++it1, ++it2)
    EXPECT_EQ((it1).GetPtr()->GetValue(), (*it2).second);
}

TEST(MapModifiers, Emplace) {
  s21::map<std::string, int> s_tree = {
      {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}};

  std::map<std::string, int> o_tree = {
      {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}};

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  auto v = s_tree.insert_many(std::pair<std::string, int>{"fourteen", 14},
                              std::pair<std::string, int>{"seventeen", 17},
                              std::pair<std::string, int>{"fifteen", 15},
                              std::pair<std::string, int>{"fifteen", 15});

  o_tree.emplace("fourteen", 14);
  o_tree.emplace("fifteen", 15);
  o_tree.emplace("sixteen", 16);
  auto p2 = o_tree.emplace("seventeen", 17);

  EXPECT_EQ((((v[1].first)).GetPtr()->GetKey()), (*(p2.first)).first);
  EXPECT_EQ(((v[1].first)).GetPtr()->GetValue(), (*(p2.first)).second);
  EXPECT_EQ(v[1].second, p2.second);

  EXPECT_EQ(s_tree.empty(), o_tree.empty());
}

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
