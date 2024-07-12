#include "tests.h"

TEST(ListTest, DefaultConstructor) {
  s21::List<int> our_list;
  std::list<int> std_list;
  EXPECT_EQ(our_list.empty(), std_list.empty());
}

TEST(ListTest, SizeConstructor) {
  s21::List<int> our_list(5);
  std::list<int> std_list(5);
  EXPECT_EQ(our_list.size(), std_list.size());
}

TEST(ListTest, InitializerListConstructor) {
  s21::List<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  EXPECT_EQ(our_list.size(), std_list.size());
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(ListTest, ConstructorCopy) {
  s21::List<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::List<int> our_copy(our_list);
  std::list<int> std_copy(std_list);
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
}

TEST(ListTest, ConstructorMove) {
  s21::List<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::List<int> our_copy(std::move(our_list));
  std::list<int> std_copy(std::move(std_list));
  EXPECT_EQ(our_copy.size(), std_copy.size());
  EXPECT_EQ(our_copy.back(), std_copy.back());
}

TEST(ListTest, OperatorMove) {
  s21::List<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::List<int> our_copy;
  our_copy = std::move(our_list);
  std::list<int> std_copy;
  std_copy = std::move(std_list);
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
}

TEST(ListTest, Size) {
  s21::List<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  EXPECT_EQ(our_list.size(), std_list.size());
}

TEST(ListTest, PushFront) {
  s21::List<int> our_list;
  std::list<int> std_list;
  our_list.push_front(1);
  std_list.push_front(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_front(2);
  std_list.push_front(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_front(3);
  std_list.push_front(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(ListTest, PushBack) {
  s21::List<int> our_list;
  std::list<int> std_list;
  our_list.push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(ListTest, PopFront) {
  s21::List<int> our_list;
  std::list<int> std_list;
  our_list.push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.pop_front();
  std_list.pop_front();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(ListTest, PopBack) {
  s21::List<int> our_list;
  std::list<int> std_list;
  our_list.push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.pop_back();
  std_list.pop_back();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(ListTest, Swap) {
  s21::List<int> our_list_first = {1};
  s21::List<int> our_list_second = {2, 3, 4, 5};
  std::list<int> std_list_first = {1};
  std::list<int> std_list_second = {2, 3, 4, 5};
  our_list_first.swap(our_list_second);
  std_list_first.swap(std_list_second);
  EXPECT_EQ(our_list_first.front(), std_list_first.front());
}

TEST(ListTest, IteratorBegin) {
  s21::List<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::List<int>::iterator our_it;
  our_it = our_list.begin();
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  EXPECT_EQ(*our_it, *std_it);
}

TEST(ListTest, IteratorBeginPlusAndMinus) {
  s21::List<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::List<int>::iterator our_it;
  our_it = our_list.begin();
  ++our_it;
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  --our_it;
  --std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(ListTest, IteratorEnd_Last) {
  s21::List<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::List<int>::iterator our_it;
  our_it = our_list.end();
  --our_it;
  std::list<int>::iterator std_it;
  std_it = std_list.end();
  --std_it;
  EXPECT_EQ(*our_it, *std_it);
}

// TEST(ListTest, IteratorEquals) {
//   s21::List<int> first_list = {1, 2, 3};
//   s21::List<int>::iterator our_it_first;
//   our_it_first = first_list.begin();
//   s21::List<int>::iterator our_it_second;
//   our_it_second = first_list.begin();
//   EXPECT_TRUE(our_it_first == our_it_second);
//   EXPECT_TRUE(our_it_first >= our_it_second);
//   EXPECT_TRUE(our_it_first <= our_it_second);
//   ++our_it_second;
//   EXPECT_TRUE(our_it_first != our_it_second);
//   EXPECT_TRUE(our_it_second > our_it_first);
//   EXPECT_TRUE(our_it_second >= our_it_first);
//   EXPECT_TRUE(our_it_first < our_it_second);
//   EXPECT_TRUE(our_it_first <= our_it_second);
// }

TEST(ListTest, Insert) {
  s21::List<int> our_list;
  std::list<int> std_list;
  s21::List<int>::iterator our_it;
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

TEST(ListTest, Erase) {
  s21::List<int> our_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  our_list.erase(our_list.begin());
  std_list.erase(std_list.begin());
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  s21::List<int>::iterator our_it;
  our_it = our_list.begin();
  ++our_it;
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  ++std_it;
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(ListTest, Splice) {
  s21::List<int> our_list_first = {1};
  s21::List<int> our_list_second = {2, 3, 4, 5};
  std::list<int> std_list_first = {1};
  std::list<int> std_list_second = {2, 3, 4, 5};
  s21::List<int>::const_iterator our_it = our_list_first.begin();
  std::list<int>::const_iterator std_it = std_list_first.begin();
  our_list_first.splice(our_it, our_list_second);
  std_list_first.splice(std_it, std_list_second);
  EXPECT_EQ(our_list_first.front(), std_list_first.front());
  EXPECT_EQ(our_list_first.back(), std_list_first.back());
}

TEST(ListTest, Merge) {
  s21::List<int> our_list_first = {1};
  s21::List<int> our_list_second = {2, 3, 4, 5};
  std::list<int> std_list_first = {1};
  std::list<int> std_list_second = {2, 3, 4, 5};
  our_list_first.merge(our_list_second);
  std_list_first.merge(std_list_second);
  EXPECT_EQ(our_list_first.front(), std_list_first.front());
  EXPECT_EQ(our_list_first.back(), std_list_first.back());
  EXPECT_EQ(our_list_second.empty(), std_list_second.empty());
}

TEST(ListTest, Reverse) {
  s21::List<int> our_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  our_list.reverse();
  std_list.reverse();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(ListTest, Unique) {
  s21::List<int> our_list = {1, 2, 2, 3, 3};
  std::list<int> std_list = {1, 2, 2, 3, 3};
  s21::List<int>::iterator our_it;
  std::list<int>::iterator std_it;
  our_list.unique();
  std_list.unique();
  our_it = our_list.begin();
  std_it = std_list.begin();
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(ListTest, Sort) {
  s21::List<int> our_list = {2, 4, 1, 3, 5};
  std::list<int> std_list = {2, 4, 1, 3, 5};
  s21::List<int>::iterator our_it;
  std::list<int>::iterator std_it;
  our_list.sort();
  std_list.sort();
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

TEST(ListTest, InsertMany) {
  s21::List<int> our_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};
  auto pos_our = std::next(our_list.begin(), 2);
  our_list.insert_many(pos_our, -1, -2, -3);
  auto pos = std::next(std_list.begin(), 2);
  const auto rg = std::vector<int>{-1, -2, -3};
  std_list.insert(pos, rg.cbegin(), rg.cend());

  auto iter = std_list.begin();
  for (auto iter_our = our_list.begin(); iter_our != our_list.end();
       ++iter_our) {
    EXPECT_EQ(*iter_our, *iter++);
  }
}

TEST(ListTest, InsertMany_Back) {
  s21::List<int> our_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  our_list.insert_many_back(7, 8, 9);
  const auto tail = std::vector<int>{7, 8, 9};
  std_list.insert(std_list.end(), tail.cbegin(), tail.cend());

  auto iter = std_list.begin();
  for (auto iter_our = our_list.begin(); iter_our != our_list.end();
       ++iter_our) {
    EXPECT_EQ(*iter_our, *iter++);
  }
}

TEST(ListTest, InsertMany_Front) {
  s21::List<int> our_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  our_list.insert_many_front(7, 8, 9);
  const auto tail = std::vector<int>{7, 8, 9};
  std_list.insert(std_list.begin(), tail.cbegin(), tail.cend());

  auto iter = std_list.begin();
  for (auto iter_our = our_list.begin(); iter_our != our_list.end();
       ++iter_our) {
    EXPECT_EQ(*iter_our, *iter++);
  }
}
