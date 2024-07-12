#include "tests.h"

TEST(VectorTest, DefaultConstructor) {
  s21::Vector<int> our_vector;
  std::vector<int> std_vector;
  EXPECT_EQ(our_vector.empty(), std_vector.empty());
  EXPECT_EQ(our_vector.size(), std_vector.size());
}

TEST(VectorTest, SizeConstructor) {
  const size_t size = 5;
  s21::Vector<int> our_vector(size);
  std::vector<int> std_vector(size);
  EXPECT_EQ(our_vector.empty(), std_vector.empty());
  EXPECT_EQ(our_vector.size(), std_vector.size());
  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(our_vector[i], std_vector[i]);
  }
}

TEST(VectorTest, SizeConstructorZero) {
  const size_t size = 0;
  s21::Vector<int> our_vector(size);
  std::vector<int> std_vector(size);
  EXPECT_EQ(our_vector.empty(), std_vector.empty());
  EXPECT_EQ(our_vector.size(), std_vector.size());
}

TEST(VectorTest, InitializerListEmpty) {
  s21::Vector<int> our_vector = {};
  std::vector<int> std_vector = {};
  EXPECT_EQ(our_vector.empty(), std_vector.empty());
  EXPECT_EQ(our_vector.size(), std_vector.size());
}

TEST(VectorTest, InitializerListConstructor) {
  s21::Vector<int> our_vector = {1, 2, 3, 4, 5};
  std::vector<int> std_vector = {1, 2, 3, 4, 5};
  EXPECT_EQ(our_vector.empty(), std_vector.empty());
  EXPECT_EQ(our_vector.size(), std_vector.size());
  EXPECT_EQ(our_vector[0], std_vector[0]);
  EXPECT_EQ(our_vector[4], std_vector[4]);
}

TEST(VectorTest, CopyConstructorEmpty) {
  s21::Vector<int> our_vector;
  s21::Vector<int> our_vector_copy(our_vector);
  std::vector<int> std_vector;
  std::vector<int> std_vector_copy(std_vector);
  EXPECT_EQ(our_vector_copy.empty(), std_vector_copy.empty());
  EXPECT_EQ(our_vector_copy.size(), std_vector_copy.size());
}

TEST(VectorTest, ConstructorCopy) {
  s21::Vector<int> our_vector = {1, 2, 3};
  s21::Vector<int> our_vector_copy(our_vector);
  EXPECT_EQ(our_vector_copy.size(), our_vector.size());
  for (size_t i = 0; i < our_vector.size(); ++i) {
    EXPECT_EQ(our_vector_copy[i], our_vector[i]);
  }
}

TEST(VectorTest, MoveConstructorEmpty) {
  s21::Vector<int> our_vector;
  s21::Vector<int> our_vector_copy(std::move(our_vector));
  EXPECT_TRUE(our_vector_copy.empty());
  EXPECT_EQ(our_vector_copy.size(), (size_t)0);
}

TEST(VectorTest, MoveConstructorNonEmpty) {
  s21::Vector<int> our_vector = {1, 2, 3};
  s21::Vector<int> our_vector_copy(std::move(our_vector));
  std::vector<int> std_vector = {1, 2, 3};
  std::vector<int> std_vector_copy(std::move(std_vector));
  EXPECT_EQ(our_vector_copy.size(), std_vector_copy.size());
  EXPECT_EQ(our_vector.empty(), std_vector.empty());
}

TEST(VectorTest, DestructorEmpty) {
  s21::Vector<int> *v = new s21::Vector<int>();
  delete v;
}

TEST(VectorTest, DestructorNonEmpty) {
  s21::Vector<int> *v = new s21::Vector<int>{1, 2, 3};
  delete v;
}

TEST(VectorTest, MoveAssignmentOperatorNonEmptyToEmpty) {
  s21::Vector<int> our_vector = {1, 2, 3};
  s21::Vector<int> our_vector_move;
  std::vector<int> std_vector = {1, 2, 3};
  std::vector<int> std_vector_move;
  our_vector_move = std::move(our_vector);
  std_vector_move = std::move(std_vector);
  EXPECT_EQ(our_vector_move.size(), std_vector_move.size());
  EXPECT_EQ(our_vector.empty(), std_vector.empty());
}

TEST(VectorTest, MoveAssignmentOperatorNonEmptyToNonEmpty) {
  s21::Vector<int> our_vector = {1, 2, 3};
  s21::Vector<int> our_vector_move = {4, 5, 6};
  std::vector<int> std_vector = {1, 2, 3};
  std::vector<int> std_vector_move = {4, 5, 6};
  our_vector_move = std::move(our_vector);
  std_vector_move = std::move(std_vector);
  EXPECT_EQ(our_vector_move.size(), std_vector_move.size());
  EXPECT_EQ(our_vector.empty(), std_vector.empty());
}

TEST(VectorTest, AtValid) {
  s21::Vector<int> our_vector = {1, 2, 3, 4, 5};
  std::vector<int> std_vector = {1, 2, 3, 4, 5};
  EXPECT_EQ(our_vector.at(0), std_vector.at(0));
  EXPECT_EQ(our_vector.at(2), std_vector.at(2));
  EXPECT_EQ(our_vector.at(4), std_vector.at(4));
}

TEST(VectorTest, AtInvalid) {
  s21::Vector<int> our_vector = {1, 2, 3, 4, 5};
  EXPECT_THROW(our_vector.at(5), std::out_of_range);
  EXPECT_THROW(our_vector.at(10), std::out_of_range);
}

TEST(VectorTest, IndexOperatorValid) {
  s21::Vector<int> our_vector = {1, 2, 3, 4, 5};
  std::vector<int> std_vector = {1, 2, 3, 4, 5};
  EXPECT_EQ(our_vector[0], std_vector[0]);
  EXPECT_EQ(our_vector[2], std_vector[2]);
  EXPECT_EQ(our_vector[4], std_vector[4]);
}

TEST(VectorTest, ConstIndexOperatorValidI) {
  s21::Vector<int> our_vector = {1, 2, 3, 4, 5};
  std::vector<int> std_vector = {1, 2, 3, 4, 5};
  EXPECT_EQ(our_vector[0], std_vector[0]);
  EXPECT_EQ(our_vector[2], std_vector[2]);
  EXPECT_EQ(our_vector[4], std_vector[4]);
}

TEST(VectorTest, FrontConst) {
  s21::Vector<int> our_vector = {1, 2, 3, 4, 5};
  std::vector<int> std_vector = {1, 2, 3, 4, 5};
  EXPECT_EQ(our_vector.front(), std_vector.front());
}

TEST(VectorTest, BackConst) {
  s21::Vector<int> our_vector = {1, 2, 3, 4, 5};
  std::vector<int> std_vector = {1, 2, 3, 4, 5};
  EXPECT_EQ(our_vector.back(), std_vector.back());
}

TEST(VectorTest, Data) {
  s21::Vector<int> our_vector = {1, 2, 3, 4, 5};
  std::vector<int> std_vector = {1, 2, 3, 4, 5};
  int *dataPtr = our_vector.data();
  int *dataPtr1 = std_vector.data();
  EXPECT_EQ(*dataPtr, *dataPtr1);
  *dataPtr = 10;
  *dataPtr1 = 10;
  EXPECT_EQ(our_vector[0], std_vector[0]);
}

TEST(VectorTest, DataEmpty) {
  s21::Vector<int> our_vector;
  int *dataPtr = our_vector.data();
  EXPECT_EQ(dataPtr, nullptr);
}

TEST(VectorTest, Begin) {
  s21::Vector<int> our_vector = {1, 2, 3, 4, 5};
  std::vector<int> std_vector = {1, 2, 3, 4, 5};
  auto it = our_vector.begin();
  auto it1 = std_vector.begin();
  EXPECT_EQ(*it, *it1);
  *it = 10;
  *it1 = 10;
  EXPECT_EQ(our_vector[0], std_vector[0]);
}

TEST(VectorTest, BeginEmpty) {
  s21::Vector<int> our_vector;
  auto it = our_vector.begin();
  EXPECT_EQ(it, our_vector.end());
}

TEST(VectorTest, End) {
  s21::Vector<int> our_vector = {1, 2, 3, 4, 5};
  auto it = our_vector.end();
  auto beginIt = our_vector.begin();
  EXPECT_NE(it, beginIt);
}

TEST(VectorTest, EndEmpty) {
  s21::Vector<int> our_vector;
  auto it = our_vector.end();
  EXPECT_EQ(it, our_vector.begin());
}

TEST(VectorTest, Empty) {
  const s21::Vector<int> our_vector;
  const std::vector<int> std_vector;
  EXPECT_EQ(our_vector.empty(), std_vector.empty());
}

TEST(VectorTest, EmptyNonEmptyVector) {
  const s21::Vector<int> our_vector = {1, 2, 3};
  const std::vector<int> std_vector = {1, 2, 3};
  EXPECT_EQ(our_vector.empty(), std_vector.empty());
}

TEST(VectorTest, SizeEmpty) {
  const s21::Vector<int> our_vector;
  const std::vector<int> std_vector;
  EXPECT_EQ(our_vector.size(), std_vector.size());
}

TEST(VectorTest, Size) {
  const s21::Vector<int> our_vector = {1, 2, 3};
  const std::vector<int> std_vector = {1, 2, 3};
  EXPECT_EQ(our_vector.size(), std_vector.size());
}

TEST(VectorTest, MaxSize) {
  const s21::Vector<int> our_vector;
  EXPECT_GT(our_vector.max_size(), 0U);
}

TEST(VectorTest, ReserveIncreaseCapacity) {
  s21::Vector<int> our_vector;
  size_t initialCapacity = our_vector.capacity();
  size_t newCapacity = initialCapacity + 10;
  our_vector.reserve(newCapacity);
  EXPECT_GE(our_vector.capacity(), newCapacity);
}

TEST(VectorTest, ReserveDecreaseCapacity) {
  s21::Vector<int> our_vector = {1, 2, 3, 4, 5};
  size_t initialCapacity = our_vector.capacity();
  size_t newCapacity = initialCapacity - 2;
  our_vector.reserve(newCapacity);
  EXPECT_LE(our_vector.capacity(), initialCapacity);
  EXPECT_GE(our_vector.capacity(), newCapacity);
}

TEST(VectorTest, CapacityEmpty) {
  const s21::Vector<int> our_vector;
  const std::vector<int> std_vector;
  EXPECT_EQ(our_vector.capacity(), std_vector.capacity());
}

TEST(VectorTest, CapacityNonEmptyVector) {
  const s21::Vector<int> our_vector = {1, 2, 3};
  const std::vector<int> std_vector = {1, 2, 3};
  EXPECT_EQ(our_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(our_vector.size(), std_vector.size());
}

TEST(VectorTest, ShrinkToFitEmptyVector) {
  s21::Vector<int> our_vector;
  our_vector.shrink_to_fit();
  EXPECT_GE(our_vector.capacity(), 0U);
}

TEST(VectorTest, ShrinkToFitNonEmptyVector) {
  s21::Vector<int> our_vector = {1, 2, 3, 4, 5};
  size_t initialCapacity = our_vector.capacity();
  our_vector.pop_back();
  our_vector.shrink_to_fit();
  EXPECT_LE(our_vector.capacity(), our_vector.size());
  EXPECT_LE(our_vector.capacity(), initialCapacity);
}

TEST(VectorTest, ClearEmptyVector) {
  s21::Vector<int> our_vector;
  our_vector.clear();
  EXPECT_TRUE(our_vector.empty());
  EXPECT_EQ(our_vector.size(), 0U);
  EXPECT_GE(our_vector.capacity(), 0U);
}

TEST(VectorTest, ClearNonEmptyVector) {
  s21::Vector<int> our_vector = {1, 2, 3, 4, 5};
  our_vector.clear();
  EXPECT_TRUE(our_vector.empty());
  EXPECT_EQ(our_vector.size(), 0U);
  EXPECT_GE(our_vector.capacity(), 0U);
}

TEST(VectorTest, InsertBeginning) {
  s21::Vector<int> our_vector = {2, 3, 4};
  auto it = our_vector.insert(our_vector.begin(), 1);
  std::vector<int> std_vector = {2, 3, 4};
  auto it1 = std_vector.insert(std_vector.begin(), 1);
  EXPECT_EQ(our_vector.size(), std_vector.size());
  EXPECT_EQ(our_vector[0], std_vector[0]);
  EXPECT_EQ(*it, *it1);
}

TEST(VectorTest, InsertMiddle) {
  s21::Vector<int> our_vector = {2, 3, 4};
  auto it = our_vector.insert(our_vector.begin() + 1, 2);
  std::vector<int> std_vector = {2, 3, 4};
  auto it1 = std_vector.insert(std_vector.begin() + 1, 2);
  EXPECT_EQ(our_vector.size(), std_vector.size());
  EXPECT_EQ(our_vector[1], std_vector[1]);
  EXPECT_EQ(*it, *it1);
}

TEST(VectorTest, InsertEnd) {
  s21::Vector<int> our_vector = {2, 3, 4};
  auto it = our_vector.insert(our_vector.end(), 5);
  std::vector<int> std_vector = {2, 3, 4};
  auto it1 = std_vector.insert(std_vector.end(), 5);
  EXPECT_EQ(our_vector.size(), std_vector.size());
  EXPECT_EQ(our_vector[3], std_vector[3]);
  EXPECT_EQ(*it, *it1);
}

TEST(VectorTest, EraseBeginning) {
  s21::Vector<int> our_vector = {1, 2, 3, 4};
  our_vector.erase(our_vector.begin());
  std::vector<int> std_vector = {1, 2, 3, 4};
  std_vector.erase(std_vector.begin());
  EXPECT_EQ(our_vector.size(), std_vector.size());
  EXPECT_EQ(our_vector[0], std_vector[0]);
}

TEST(VectorTest, EraseMiddle) {
  s21::Vector<int> our_vector = {1, 2, 3, 4};
  our_vector.erase(our_vector.begin() + 1);
  std::vector<int> std_vector = {1, 2, 3, 4};
  std_vector.erase(std_vector.begin() + 1);
  EXPECT_EQ(our_vector.size(), std_vector.size());
  EXPECT_EQ(our_vector[1], std_vector[1]);
}

TEST(VectorTest, EraseEnd) {
  s21::Vector<int> our_vector = {1, 2, 3, 4};
  our_vector.erase(our_vector.end() - 1);
  std::vector<int> std_vector = {1, 2, 3, 4};
  std_vector.erase(std_vector.end() - 1);
  EXPECT_EQ(our_vector.size(), std_vector.size());
  EXPECT_EQ(our_vector[2], std_vector[2]);
}

TEST(VectorTest, PushBackEmptyVector) {
  s21::Vector<int> our_vector;
  our_vector.push_back(1);
  std::vector<int> std_vector;
  std_vector.push_back(1);
  EXPECT_EQ(our_vector.size(), std_vector.size());
  EXPECT_EQ(our_vector[0], std_vector[0]);
}

TEST(VectorTest, PushBackNonEmptyVector) {
  s21::Vector<int> our_vector = {1, 2, 3};
  our_vector.push_back(4);
  std::vector<int> std_vector = {1, 2, 3};
  std_vector.push_back(4);
  EXPECT_EQ(our_vector.size(), std_vector.size());
  EXPECT_EQ(our_vector[3], std_vector[3]);
}

TEST(VectorTest, PopBackNonEmptyVector) {
  s21::Vector<int> our_vector = {1, 2, 3};
  our_vector.pop_back();
  std::vector<int> std_vector = {1, 2, 3};
  std_vector.pop_back();
  EXPECT_EQ(our_vector.size(), std_vector.size());
  EXPECT_EQ(our_vector.back(), std_vector.back());
}

TEST(VectorTest, PopBackEmptyVector) {
  s21::Vector<int> our_vector;
  our_vector.pop_back();
  EXPECT_EQ(our_vector.empty(), 1);
}

TEST(VectorTest, SwapNonEmptyVectors) {
  s21::Vector<int> our_vector = {1, 2, 3};
  s21::Vector<int> our_vector_swap = {4, 5, 6};
  our_vector.swap(our_vector_swap);
  EXPECT_EQ(our_vector.size(), 3U);
  EXPECT_EQ(our_vector_swap.size(), 3U);
  EXPECT_EQ(our_vector[0], 4);
  EXPECT_EQ(our_vector[2], 6);
  EXPECT_EQ(our_vector_swap[0], 1);
  EXPECT_EQ(our_vector_swap[2], 3);
}

TEST(VectorTest, SwapEmptyAndNonEmptyVectors) {
  s21::Vector<int> our_vector;
  s21::Vector<int> our_vector_swap = {1, 2, 3};
  our_vector.swap(our_vector_swap);
  EXPECT_EQ(our_vector.size(), 3U);
  EXPECT_FALSE(our_vector.empty());
  EXPECT_EQ(our_vector_swap.size(), 0U);
  EXPECT_TRUE(our_vector_swap.empty());
}

TEST(VectorTest, InsertMany) {
  s21::Vector<int> our_vector = {1, 2, 3, 7, 8};
  std::vector<int> std_vector = {1, 2, 3, 7, 8};
  auto pos_std = std::next(std_vector.begin(), 3);
  const auto pos_our = std::next(our_vector.begin(), 3);
  const auto rg_std = std::list<int>{4, 5, 6};
  std_vector.insert(pos_std, rg_std.cbegin(), rg_std.cend());
  our_vector.insert_many(pos_our, 4, 5, 6);
  EXPECT_EQ(our_vector.size(), std_vector.size());
  for (std::size_t i = 0; i < our_vector.size(); ++i) {
    EXPECT_EQ(our_vector[i], std_vector[i]);
  }
}

TEST(VectorTest, InsertManyBack) {
  s21::Vector<int> our_vector = {1, 2, 3, 4};
  our_vector.insert_many_back(5, 6, 7);
  EXPECT_EQ(our_vector.size(), 7U);
  for (std::size_t i = 0; i < our_vector.size(); ++i) {
    EXPECT_EQ(our_vector[i], (int)i + 1);
  }
}