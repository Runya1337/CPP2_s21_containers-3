#include "tests.h"

TEST(StackTest, ConstructorDefault) {
  s21::Stack<int> our_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(our_stack.empty(), std_stack.empty());
}

TEST(StackTest, ConstructorList) {
  s21::Stack<int> our_stack = {1, 2, 3};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  EXPECT_EQ(our_stack.top(), std_stack.top());
}

TEST(StackTest, ConstructorCopy) {
  s21::Stack<int> our_stack = {1, 2, 3};
  s21::Stack<int> our_copy(our_stack);
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_copy(std_stack);
  EXPECT_EQ(our_copy.top(), std_copy.top());
}

TEST(StackTest, ConstructorMove) {
  s21::Stack<int> our_stack = {1, 2, 3};
  s21::Stack<int> our_move(std::move(our_stack));
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_move(std::move(std_stack));
  EXPECT_EQ(our_move.top(), std_move.top());
}

TEST(StackTest, OperatorMove) {
  s21::Stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::Stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  our_stack_empty = std::move(our_stack_int);
  std_stack_empty = std::move(std_stack_int);
  EXPECT_EQ(our_stack_empty.top(), std_stack_empty.top());
}

TEST(StackTest, Top) {
  s21::Stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::Stack<double> our_stack_double = {1.1f, 2.1f, 3.1f};
  std::stack<double> std_stack_double;
  std_stack_double.push(1.1f);
  std_stack_double.push(2.1f);
  std_stack_double.push(3.1f);
  s21::Stack<std::string> our_stack_string = {"abc", "def", "ghf"};
  std::stack<std::string> std_stack_string;
  std_stack_string.push("abc");
  std_stack_string.push("def");
  std_stack_string.push("ghf");
  EXPECT_EQ(our_stack_int.top(), std_stack_int.top());
  EXPECT_EQ(our_stack_double.top(), std_stack_double.top());
  EXPECT_EQ(our_stack_string.top(), std_stack_string.top());
}

TEST(StackTest, Empty) {
  s21::Stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
  s21::Stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  EXPECT_EQ(our_stack_empty.empty(), std_stack_empty.empty());
}

TEST(StackTest, Size) {
  s21::Stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  EXPECT_EQ(our_stack_int.size(), std_stack_int.size());
  s21::Stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  EXPECT_EQ(our_stack_empty.size(), std_stack_empty.size());
}

TEST(StackTest, Push) {
  s21::Stack<int> our_stack_int;
  our_stack_int.push(1);
  our_stack_int.push(2);
  our_stack_int.push(3);
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  EXPECT_EQ(our_stack_int.top(), std_stack_int.top());
}

TEST(StackTest, Pop) {
  s21::Stack<int> our_stack_int;
  our_stack_int.push(1);
  our_stack_int.push(2);
  our_stack_int.push(3);
  our_stack_int.pop();
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  std_stack_int.pop();
  EXPECT_EQ(our_stack_int.top(), std_stack_int.top());
  our_stack_int.pop();
  our_stack_int.pop();
  std_stack_int.pop();
  std_stack_int.pop();
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

TEST(StackTest, Swap) {
  s21::Stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::Stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  our_stack_empty.swap(our_stack_int);
  std_stack_empty.swap(std_stack_int);
  EXPECT_EQ(our_stack_empty.top(), std_stack_empty.top());
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

TEST(StackTest, InsertManyFront) {
  s21::Stack<int> our_stack_int;
  our_stack_int.insert_many_front(1, 2, 3);
  EXPECT_EQ(our_stack_int.top(), 3);
}
