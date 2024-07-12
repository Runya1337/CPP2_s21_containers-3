#include "tests.h"

TEST(MultisetTest, copy_operator_01) {
  s21::Multiset<char> multiset_2({'J', 'J', 'J', 'J', 'J', 'J', 'J'});
  EXPECT_EQ(multiset_2.GetRoot()->size_, 7);
}

TEST(MultisetTest, copy_operator_02) {
  s21::Multiset<int> multiset_1({1, 2, 1});
  s21::Multiset<int> multiset_2;

  std::multiset<int> orignal_multiset_1({1, 2, 1});
  std::multiset<int> orignal_multiset_2;

  EXPECT_EQ(multiset_1.size(), 3);

  multiset_1 = multiset_2;
  orignal_multiset_1 = orignal_multiset_2;
  EXPECT_EQ(multiset_1.size(), (int)orignal_multiset_1.size());
  EXPECT_EQ(multiset_1.size(), 0);
  EXPECT_EQ(multiset_2.size(), 0);
}

TEST(MultisetTest, copy_operator_05) {
  s21::Multiset<int> multiset_1;
  s21::Multiset<int> multiset_2;

  EXPECT_EQ(multiset_1.size(), 0);

  multiset_1 = multiset_2;
  EXPECT_EQ(multiset_1.size(), 0);
  EXPECT_EQ(multiset_2.size(), 0);
}

TEST(MultisetTest, copy_operator_03) {
  s21::Multiset<int> multiset_1({1, 2, 2});
  s21::Multiset<int> multiset_2({11, 22, 33, 11});

  EXPECT_EQ(multiset_1.size(), 3);
  EXPECT_EQ(multiset_2.size(), 4);

  multiset_1 = multiset_2;
  EXPECT_EQ(multiset_1.size(), 4);
  EXPECT_EQ(multiset_2.size(), 4);

  auto it = multiset_1.begin();
  EXPECT_EQ(*it, 11);
  ++it;
  EXPECT_EQ(*it, 11);
  ++it;
  EXPECT_EQ(*it, 22);
  ++it;
  EXPECT_EQ(*it, 33);
  it = multiset_1.begin();
  auto it_2 = multiset_2.begin();
  for (; it != nullptr; ++it) {
    EXPECT_EQ(*it, *it_2);
    ++it_2;
  }
}

TEST(MultisetTest, test_count) {
  s21::Multiset<int> multiset_1({1, 1, 3, 4, 5, 6, 7, 8, 4, 10, 4, 12});
  std::multiset<int> orignal_multiset_1({1, 1, 3, 4, 5, 6, 7, 8, 4, 10, 4, 12});
  EXPECT_EQ(multiset_1.size(), 12);

  auto res_test_1 = multiset_1.count(4);

  EXPECT_EQ(res_test_1, (size_t)3);
  auto orig_test_1 = orignal_multiset_1.count(4);
  EXPECT_EQ(res_test_1, orig_test_1);

  res_test_1 = multiset_1.count(1);
  EXPECT_EQ(res_test_1, (size_t)2);
  orig_test_1 = orignal_multiset_1.count(1);
  EXPECT_EQ(res_test_1, orig_test_1);

  res_test_1 = multiset_1.count(50);
  EXPECT_EQ(res_test_1, (size_t)0);
  orig_test_1 = orignal_multiset_1.count(50);
  EXPECT_EQ(res_test_1, orig_test_1);
}

TEST(MultisetTest, move_constr) {
  s21::Multiset<int> multiset_1({5, 3, 1, 2, 2, 5});
  EXPECT_EQ(multiset_1.size(), 6);
  s21::Multiset<int> multiset_2(std::move(multiset_1));

  EXPECT_EQ(multiset_1.size(), 0);
  EXPECT_EQ(multiset_2.size(), 6);

  std::multiset<int> orignal_multiset_1({5, 3, 1, 2, 2, 5});

  auto it = multiset_2.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 5);

  it = multiset_2.begin();
  auto it_2 = orignal_multiset_1.begin();
  for (; it != nullptr; ++it) {
    EXPECT_EQ(*it, *it_2);
    ++it_2;
  }
}

TEST(MultisetTest, move_operator) {
  s21::Multiset<int> multiset_1({1, 2, 2});
  EXPECT_EQ(multiset_1.size(), 3);
  s21::Multiset<int> multiset_2({11, 22, 33, 11});
  EXPECT_EQ(multiset_2.size(), 4);

  multiset_1 = std::move(multiset_2);

  EXPECT_EQ(multiset_1.size(), 4);
  EXPECT_EQ(multiset_2.size(), 0);

  auto it = multiset_1.begin();
  EXPECT_EQ(*it, 11);
  ++it;
  EXPECT_EQ(*it, 11);
  ++it;
  EXPECT_EQ(*it, 22);
  ++it;
  EXPECT_EQ(*it, 33);
}

TEST(MultisetTest, move_operator_05) {
  s21::Multiset<int> multiset_1({5, 3, 1, 2, 2, 2});
  s21::Multiset<int> multiset_2({11, 22, 33, 11});
  std::multiset<int> orignal_multiset_1({5, 3, 1, 2, 2, 2});
  std::multiset<int> orignal_multiset_2({11, 22, 33, 11});
  multiset_2 = std::move(multiset_1);
  orignal_multiset_2 = std::move(orignal_multiset_1);
  s21::Multiset<int>::iterator it = multiset_2.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 5);
  it = multiset_2.begin();
  auto it_2 = orignal_multiset_2.begin();
  for (; it != multiset_2.end() && it_2 != orignal_multiset_2.end(); ++it) {
    EXPECT_EQ(*it, *it_2);
    ++it_2;
  }
}

TEST(MultisetTest, move_operator_02) {
  s21::Multiset<int> multiset_1({1, 2, 1});
  s21::Multiset<int> multiset_2({11, 22, 33, 11});
  multiset_2 = std::move(multiset_1);
  auto it = multiset_2.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(MultisetTest, move_operator_03) {
  s21::Multiset<int> multiset_1;
  EXPECT_EQ(multiset_1.size(), 0);
  s21::Multiset<int> multiset_2;
  EXPECT_EQ(multiset_2.size(), 0);
  multiset_2 = std::move(multiset_1);
  EXPECT_EQ(multiset_1.size(), 0);
  EXPECT_EQ(multiset_2.size(), 0);
}

TEST(MultisetTest, move_operator_04) {
  s21::Multiset<int> multiset_1({1, 2});
  EXPECT_EQ(multiset_1.size(), 2);
  s21::Multiset<int> multiset_2;
  EXPECT_EQ(multiset_2.size(), 0);
  multiset_1 = std::move(multiset_2);
  EXPECT_EQ(multiset_1.size(), 0);
  EXPECT_EQ(multiset_2.size(), 0);
}

TEST(MultisetTest, test_empty) {
  s21::Multiset<int> multiset_1({2, 4, 6, 8});
  s21::Multiset<int> multiset_2;
  EXPECT_EQ(multiset_1.empty(), false);
  EXPECT_EQ(multiset_2.empty(), true);
}

TEST(MultisetTest, test_size) {
  s21::Multiset<double> multiset_1({1.1, 2.2, 3.3, 4.4, 5.5, 1.1, 5.5});
  std::multiset<double> orignal_multiset_1({1.1, 2.2, 3.3, 4.4, 5.5, 1.1, 5.5});
  EXPECT_EQ(multiset_1.size(), 7);
  EXPECT_EQ(multiset_1.size(), (int)orignal_multiset_1.size());
}

TEST(MultisetTest, test_clear) {
  s21::Multiset<int> multiset_1({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
  s21::Multiset<int> multiset_2({1});
  s21::Multiset<int> multiset_3;
  EXPECT_EQ(multiset_1.size(), 12);
  EXPECT_EQ(multiset_2.size(), 1);
  EXPECT_EQ(multiset_3.size(), 0);
  multiset_1.clear();
  multiset_2.clear();
  multiset_3.clear();
  EXPECT_EQ(multiset_1.size(), 0);
  EXPECT_EQ(multiset_2.size(), 0);
  EXPECT_EQ(multiset_3.size(), 0);
}

TEST(MultisetTest, test_insert) {
  s21::Multiset<double> multiset_1({1.1, 2.2, 3.3, 4.4, 5.5, 5.5, 1.1});
  std::multiset<double> orignal_multiset_1({1.1, 2.2, 3.3, 4.4, 5.5, 5.5, 1.1});
  multiset_1.insert(3.2);
  EXPECT_TRUE(multiset_1.contains(3.2));
}

TEST(MultisetTest, lower_bound_test_test_insert) {
  s21::Multiset<double> multiset_1(
      {1, 2, 4, 6, 8, 12, 15, 19, 57, 100, 111, 112});
  std::multiset<double> orignal_multiset_1(
      {1, 2, 4, 6, 8, 12, 15, 19, 57, 100, 111, 112});
  EXPECT_EQ(*(orignal_multiset_1.lower_bound(58)),
            *(multiset_1.lower_bound(58)));
}

TEST(MultisetTest, lower_bound_test_notelement_test_insert) {
  s21::Multiset<double> multiset_1(
      {1, 2, 4, 6, 8, 12, 15, 19, 57, 100, 111, 112});
  std::multiset<double> orignal_multiset_1(
      {1, 2, 4, 6, 8, 12, 15, 19, 57, 100, 111, 112});
  multiset_1.lower_bound(200);
}

TEST(MultisetTest, upper_bound_test_test_insert) {
  s21::Multiset<double> multiset_1(
      {1, 2, 4, 6, 8, 12, 15, 19, 57, 100, 111, 112});
  std::multiset<double> orignal_multiset_1(
      {1, 2, 4, 6, 8, 12, 15, 19, 57, 100, 111, 112});
  // printf("%lf", *(orignal_multiset_1.upper_bound(58)) );
  EXPECT_EQ(*(orignal_multiset_1.upper_bound(58)),
            *(multiset_1.upper_bound(58)));
}

TEST(MultisetTest, upper_bound_test_not_element_test_insert) {
  s21::Multiset<double> multiset_1(
      {1, 2, 4, 6, 8, 12, 15, 19, 57, 100, 111, 112});
  std::multiset<double> orignal_multiset_1(
      {1, 2, 4, 6, 8, 12, 15, 19, 57, 100, 111, 112});
  multiset_1.upper_bound(200);
}

TEST(MultisetTest, equal_range_test_insert) {
  s21::Multiset<double> multiset_1(
      {1, 2, 4, 6, 8, 12, 15, 19, 57, 100, 111, 112});
  std::multiset<double> orignal_multiset_1(
      {1, 2, 4, 6, 8, 12, 15, 19, 57, 100, 111, 112});
  auto pair_iter = orignal_multiset_1.equal_range(100);
  auto pair_iter_my = multiset_1.equal_range(100);
  EXPECT_EQ(*(pair_iter_my.first), *(pair_iter.first));
  EXPECT_EQ(*(pair_iter_my.second), *(pair_iter.second));
}