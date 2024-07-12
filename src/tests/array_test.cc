#include "tests.h"

TEST(ArrayTest, DefaultConstructor) {
  s21::Array<int, 5> our_arr;
  std::array<int, 5> std_arr;
  EXPECT_EQ(our_arr.size(), std_arr.size());
}

TEST(ArrayTest, InitListConstructor) {
  s21::Array<int, 5> our_arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(our_arr.size(), std_arr.size());
  for (size_t i = 0; i < our_arr.size(); ++i) {
    EXPECT_EQ(our_arr[i], std_arr[i]);
  }
}

TEST(ArrayTest, CopyConstructor) {
  s21::Array<int, 5> our_arr = {1, 2, 3, 4, 5};
  s21::Array<int, 5> our_arrCopy(our_arr);
  std::array<int, 5> std_arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_arrCopy(std_arr);
  EXPECT_EQ(our_arrCopy.size(), std_arrCopy.size());
  for (size_t i = 0; i < our_arr.size(); ++i) {
    EXPECT_EQ(our_arrCopy[i], std_arrCopy[i]);
  }
}

TEST(ArrayTest, MoveConstructor) {
  s21::Array<int, 5> our_arr = {1, 2, 3, 4, 5};
  s21::Array<int, 5> our_arrMoved(std::move(our_arr));
  std::array<int, 5> std_arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_arrCopy(std::move(std_arr));
  EXPECT_EQ(our_arrMoved.size(), 5U);
  for (size_t i = 0; i < our_arrMoved.size(); ++i) {
    EXPECT_EQ(our_arrMoved[i], std_arrCopy[i]);
  }
}

TEST(ArrayTest, Data) {
  s21::Array<int, 5> our_arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(*our_arr.data(), *std_arr.data());
}

TEST(ArrayTest, Begin) {
  s21::Array<int, 5> our_arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_arr = {1, 2, 3, 4, 5};
  auto it = our_arr.begin();
  auto it_std = std_arr.begin();
  EXPECT_EQ(*it, *it_std);
  *it = 10;
  *it_std = 10;
  EXPECT_EQ(our_arr[0], std_arr[0]);
}

TEST(ArrayTest, End) {
  s21::Array<int, 5> our_arr = {1, 2, 3, 4, 5};
  auto it = our_arr.end();
  auto beginIt = our_arr.begin();
  EXPECT_EQ(it, beginIt + 5);
}

TEST(ArrayTest, AtValidIndex) {
  s21::Array<int, 5> our_arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_arr = {1, 2, 3, 4, 5};
  int value = our_arr.at(2);
  int value_std = std_arr.at(2);
  EXPECT_EQ(value, value_std);
}

TEST(ArrayTest, AtOutOfBounds) {
  s21::Array<int, 5> our_arr = {1, 2, 3, 4, 5};
  EXPECT_THROW(our_arr.at(10), std::out_of_range);
}

TEST(ArrayTest, Front) {
  s21::Array<int, 5> our_arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_arr = {1, 2, 3, 4, 5};
  int value = our_arr.front();
  int value_std = std_arr.front();
  EXPECT_EQ(value, value_std);
}

TEST(ArrayTest, Back) {
  s21::Array<int, 5> our_arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_arr = {1, 2, 3, 4, 5};
  int value = our_arr.back();
  int value_std = std_arr.back();
  EXPECT_EQ(value, value_std);
}

TEST(ArrayTest, ConstFront) {
  const s21::Array<int, 5> our_arr = {1, 2, 3, 4, 5};
  const std::array<int, 5> std_arr = {1, 2, 3, 4, 5};
  int value = our_arr.front();
  int value_std = std_arr.front();
  EXPECT_EQ(value, value_std);
}

TEST(ArrayTest, ConstBack) {
  const s21::Array<int, 5> our_arr = {1, 2, 3, 4, 5};
  const std::array<int, 5> std_arr = {1, 2, 3, 4, 5};
  int value = our_arr.back();
  int value_std = std_arr.back();
  EXPECT_EQ(value, value_std);
}

TEST(ArrayTest, EmptyNonEmptyArray) {
  s21::Array<int, 5> our_arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(our_arr.empty(), std_arr.empty());
}

TEST(ArrayTest, EmptyEmptyArray) {
  s21::Array<int, 0> our_arr;
  std::array<int, 0> std_arr;
  EXPECT_EQ(our_arr.empty(), std_arr.empty());
}

TEST(ArrayTest, SizeNonEmptyArray) {
  s21::Array<int, 5> our_arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(our_arr.size(), std_arr.size());
}

TEST(ArrayTest, SizeEmptyArray) {
  s21::Array<int, 0> our_arr;
  std::array<int, 0> std_arr;
  EXPECT_EQ(our_arr.size(), std_arr.size());
}

TEST(ArrayTest, MaxSize) {
  s21::Array<int, 5> our_arr;
  std::array<int, 5> std_arr;
  EXPECT_EQ(our_arr.max_size(), std_arr.max_size());
}

TEST(ArrayTest, Swap) {
  s21::Array<int, 5> our_arr1 = {1, 2, 3, 4, 5};
  s21::Array<int, 5> our_arr2 = {6, 7, 8, 9, 10};
  std::array<int, 5> std_arr1 = {1, 2, 3, 4, 5};
  std::array<int, 5> std_arr2 = {6, 7, 8, 9, 10};
  our_arr1.swap(our_arr2);
  std_arr1.swap(std_arr2);
  for (size_t i = 0; i < our_arr1.size(); ++i) {
    EXPECT_EQ(our_arr1[i], std_arr1[i]);
  }
  for (size_t i = 0; i < our_arr2.size(); ++i) {
    EXPECT_EQ(our_arr2[i], std_arr2[i]);
  }
}

TEST(ArrayTest, Fill) {
  s21::Array<int, 5> our_arr;
  std::array<int, 5> std_arr;
  our_arr.fill(10);
  std_arr.fill(10);
  for (size_t i = 0; i < our_arr.size(); ++i) {
    EXPECT_EQ(our_arr[i], std_arr[i]);
  }
}

TEST(ArrayTest, MoveAssignmentOperator) {
  s21::Array<int, 5> our_arr1 = {1, 2, 3, 4, 5};
  s21::Array<int, 5> our_arr2 = {6, 7, 8, 9, 10};
  std::array<int, 5> std_arr1 = {1, 2, 3, 4, 5};
  std::array<int, 5> std_arr2 = {6, 7, 8, 9, 10};
  our_arr1 = std::move(our_arr2);
  std_arr1 = std::move(std_arr2);
  for (size_t i = 0; i < our_arr1.size(); ++i) {
    EXPECT_EQ(our_arr1[i], std_arr1[i]);
  }
}

TEST(ArrayTest, OperatorBracket) {
  s21::Array<int, 5> our_arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_arr = {1, 2, 3, 4, 5};
  for (size_t i = 0; i < our_arr.size(); ++i) {
    EXPECT_EQ(our_arr[i], std_arr[i]);
  }
  our_arr[2] = 10;
  std_arr[2] = 10;
  EXPECT_EQ(our_arr[2], std_arr[2]);
}
