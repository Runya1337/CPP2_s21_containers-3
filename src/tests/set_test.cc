#include "tests.h"

TEST(SetTest, DefaultConstructor) {
  s21::Set<int> s;
  EXPECT_TRUE(s.empty());
}

TEST(SetTest, InitializerListConstructor) {
  s21::Set<int> s = {1, 2, 3};
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(SetTest, CopyConstructor) {
  s21::Set<int> s1 = {1, 2, 3};
  s21::Set<int> s2(s1);
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(SetTest, MoveConstructor) {
  s21::Set<int> s1 = {1, 2, 3};
  s21::Set<int> s2(std::move(s1));
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}
TEST(SetTest, BeginEnd) {
  s21::Set<int> s{3, 5, 1, 4, 2};
  auto it = s.begin();
  ASSERT_EQ(it.GetCurrent()->key_, 1);
  it = s.end();
  ASSERT_EQ(it.GetCurrent()->key_, 5);

  s.clear();
  it = s.begin();
  ASSERT_EQ(it, nullptr);
}

TEST(SetTest, SizeMaxSize) {
  s21::Set<int> s{3, 5, 1, 4, 2};
  std::set<int> s1{3, 5, 1, 4, 2};
  ASSERT_GE(s.max_size(), s1.max_size());
}
TEST(SetTest, Erase) {
  s21::Set<int> s{1, 2, 3, 4, 5};
  auto it = s.find(3);
  s.erase(it);
  EXPECT_FALSE(s.contains(3));
}

TEST(SetTest, Swap) {
  s21::Set<int> s1{1, 2, 3};
  s21::Set<int> s2{4, 5, 6};
  s1.swap(s2);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s1.contains(4));
}

TEST(SetTest, Merge) {
  s21::Set<int> s1{1, 2, 3};
  s21::Set<int> s2{3, 4, 5};
  s1.merge(s2);
  EXPECT_TRUE(s1.contains(4));
  EXPECT_FALSE(s2.contains(3));
}

TEST(SetTest, Find) {
  s21::Set<int> s{1, 2, 3};
  auto it1 = s.find(2);
  EXPECT_EQ(it1.GetCurrent()->key_, 2);
}

TEST(SetTest, RotateCheck) {
  s21::Set<int> s1 = {1, 2, 3, 6, 7, 8, 9, 99, -56};
  s1.insert(-1000);
  s1.insert(-10002);
  s1.insert(-100023);
  s1.insert(-100024);
  s1.insert(-100026);
  auto it1 = s1.end();
  auto it2 = s1.begin();
  EXPECT_EQ(it1.GetCurrent()->key_, 99);
  EXPECT_EQ(it2.GetCurrent()->key_, -100026);
}

TEST(SetTest, operatorpris_test1) {
  s21::Set<int> s_1{1, 2, 3};
  s21::Set<int> s_2;
  s_2 = std::move(s_1);
  auto it2 = s_2.begin();
  EXPECT_EQ(s_2.size(), 3);
  EXPECT_EQ(it2.GetCurrent()->key_, 1);
}

TEST(SetTest, insert_many_test1) {
  s21::Set<int> s_1;
  s_1.insert_many(1, 2, 3);
  auto it = s_1.begin();
  EXPECT_EQ(it.GetCurrent()->key_, 1);
  it++;
  EXPECT_EQ(it.GetCurrent()->key_, 2);
  it++;
  EXPECT_EQ(it.GetCurrent()->key_, 3);
}