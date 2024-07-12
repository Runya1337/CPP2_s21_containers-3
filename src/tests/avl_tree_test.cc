#include "tests.h"

template <typename KeyValue>
bool IsTypeConst() {
  return std::is_const<KeyValue>::value;
}

TEST(TreeTest, Constructor_branch_test_1) {
  s21::Branch<int, char> root(1, 't');
  EXPECT_EQ(root.value_, 't');
  EXPECT_EQ(root.key_, 1);
  EXPECT_EQ(root.left_, nullptr);
  EXPECT_EQ(root.right_, nullptr);
  EXPECT_EQ(root.parent_, nullptr);
  EXPECT_EQ(root.height_, 1);
  EXPECT_EQ(root.size_, 1);
  EXPECT_EQ(root.isSentinel_, false);
}

TEST(TreeTest, Constructor_branch_test_2_const) {
  const int a_key = 1;
  const char b_value = 't';
  s21::Branch<int, char> root(a_key, b_value);
  EXPECT_EQ(root.value_, 't');
  EXPECT_EQ(root.key_, 1);
  EXPECT_EQ(root.left_, nullptr);
  EXPECT_EQ(root.right_, nullptr);
  EXPECT_EQ(root.parent_, nullptr);
  EXPECT_EQ(root.height_, 1);
  EXPECT_EQ(root.size_, 1);
  EXPECT_EQ(root.isSentinel_, false);
}

TEST(TreeTest, Constructor_Iterator_test_1_normal) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(10, 0);
  test_tree.Insert(6, 0);
  auto bebra = test_tree.begin();
  EXPECT_EQ(bebra.GetCurrent()->key_, 6);
  EXPECT_EQ(bebra.GetCurrent()->value_, 0);
}

TEST(TreeTest, Constructor_Iterator_test_1_const) {
  const int a_key = 10;
  const int b_value = 0;
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(a_key, b_value);
  auto bebra = test_tree.begin();
  EXPECT_EQ(bebra.GetCurrent()->key_, 10);
  EXPECT_EQ(bebra.GetCurrent()->value_, 0);
}

TEST(TreeTest, Constructor_Iterator_copy_test_1) {
  s21::AVLTree<int, int> tree;
  tree.Insert(10, 20);
  tree.Insert(5, 10);
  auto original = tree.begin();
  auto copy = original;
  EXPECT_EQ(copy.GetCurrent(), original.GetCurrent());
  ++original;
  EXPECT_NE(copy.GetCurrent(), original.GetCurrent());
}
TEST(TreeTest, Constructor_Iterator_copy_pris_test_1) {
  s21::AVLTree<int, int> tree;
  s21::AVLTree<int, int> tree_1;
  tree.Insert(10, 20);
  tree.Insert(5, 10);
  tree_1.Insert(20, 20);
  tree_1.Insert(15, 10);
  auto original = tree.begin();
  auto copy = tree_1.begin();
  copy = original;
  EXPECT_EQ(copy.GetCurrent(), original.GetCurrent());
  ++original;
  EXPECT_NE(copy.GetCurrent(), original.GetCurrent());
}

TEST(TreeTest, Constructor_Iterator_destructor_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(10, 20);
  test_tree.Insert(5, 10);
  test_tree.~AVLTree();
  EXPECT_TRUE(test_tree.IsEmpty());
}

TEST(TreeTest, CIterator_move_multi_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(10, 0);
  test_tree.Insert(6, 0);
  test_tree.Insert(15, 0);
  test_tree.Insert(7, 0);
  test_tree.Insert(11, 0);
  test_tree.Insert(20, 0);
  test_tree.Insert(4, 0);
  auto bebra = test_tree.begin();
  bebra = bebra + 2;
  EXPECT_EQ(bebra.GetCurrent()->key_, 7);
}

TEST(TreeTest, Iterator_move_one_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(10, 0);
  test_tree.Insert(6, 0);
  test_tree.Insert(15, 0);
  test_tree.Insert(7, 0);
  auto bebra = test_tree.begin();
  bebra++;
  EXPECT_EQ(bebra.GetCurrent()->key_, 7);
}

TEST(TreeTest, Iterator_move_one_post_fix_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(10, 0);
  test_tree.Insert(6, 0);
  test_tree.Insert(15, 0);
  test_tree.Insert(7, 0);
  auto bebra = test_tree.begin();
  ++bebra;
  EXPECT_EQ(bebra.GetCurrent()->key_, 7);
}
TEST(TreeTest, Iterator_decrement_move_one_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(10, 0);
  test_tree.Insert(6, 0);
  test_tree.Insert(15, 0);
  test_tree.Insert(7, 0);
  auto bebra = test_tree.end();
  EXPECT_EQ(bebra.GetCurrent()->key_, 15);
  bebra--;
  EXPECT_EQ(bebra.GetCurrent()->key_, 10);
  bebra--;
  EXPECT_EQ(bebra.GetCurrent()->key_, 7);
}

TEST(TreeTest, Iterator_decrement_move_one_pre_fix_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(10, 0);
  test_tree.Insert(6, 0);
  test_tree.Insert(15, 0);
  test_tree.Insert(7, 0);
  auto bebra = test_tree.end();
  EXPECT_EQ(bebra.GetCurrent()->key_, 15);
  --bebra;
  EXPECT_EQ(bebra.GetCurrent()->key_, 10);
  --bebra;
  EXPECT_EQ(bebra.GetCurrent()->key_, 7);
}

TEST(TreeTest, Iterator_compare_test_1) {
  s21::AVLTree<int, int> test_tree;
  s21::AVLTree<int, int> test_tree_1;
  test_tree.Insert(10, 0);
  test_tree.Insert(6, 0);
  test_tree.Insert(15, 0);
  test_tree.Insert(7, 0);
  auto bebra = test_tree.begin();
  auto bebra_1 = test_tree.begin();
  bebra++;
  bebra_1++;
  EXPECT_TRUE(bebra == bebra_1);
}

TEST(TreeTest, Iterator_not_compare_test_1) {
  s21::AVLTree<int, int> test_tree;
  s21::AVLTree<int, int> test_tree_1;
  test_tree.Insert(10, 0);
  test_tree.Insert(6, 0);
  test_tree.Insert(15, 0);
  test_tree.Insert(7, 0);
  auto bebra = test_tree.begin();
  auto bebra_1 = test_tree.begin();
  bebra++;
  EXPECT_FALSE(bebra == bebra_1);
}

TEST(TreeTest, Iterator_raziemen_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(10, 0);
  auto bebra = test_tree.begin();
  EXPECT_EQ(*bebra, 10);
}

TEST(TreeTest, Iterator_strelochka_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(10, 20);
  auto bebra = test_tree.begin();
  EXPECT_EQ(bebra->key_, 10);
  EXPECT_EQ(bebra->value_, 20);
}

TEST(TreeTest, Constructor_Iterator_strelochka_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(10, 20);
  auto bebra = test_tree.begin();
  EXPECT_EQ(bebra->key_, 10);
  EXPECT_EQ(bebra->value_, 20);
}

TEST(TreeTest, find_max_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(10, 1);
  test_tree.Insert(15, 2);
  test_tree.Insert(8, 3);
  test_tree.Insert(50, 4);
  test_tree.Insert(1, 5);
  auto bebra = test_tree.begin();
  auto root_test = bebra.GetRootIter();
  auto max_item = bebra.MaximumKey_iter(root_test);
  EXPECT_EQ(max_item->key_, 50);
}

TEST(TreeTest, get_current_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(10, 1);
  auto bebra = test_tree.begin();
  EXPECT_EQ(bebra.GetCurrent()->key_, 10);
}

TEST(TreeTest, const_iter_test_1) {
  const int a_key = 1;
  const int b_key = 2;
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(a_key, b_key);
  auto bebra = test_tree.begin();
  EXPECT_EQ(bebra.GetCurrent()->key_, 1);
}

TEST(TreeTest, Constructor_tree_test_1) {
  s21::AVLTree<int, int> test_tree;
  EXPECT_TRUE(test_tree.IsEmpty());
}

TEST(TreeTest, Copy_tree_test_1) {
  s21::AVLTree<int, int> test_tree_1;
  test_tree_1.Insert(10, 100);
  test_tree_1.Insert(20, 200);
  s21::AVLTree<int, int> copied_tree = test_tree_1;
  auto iter_copied_tree = copied_tree.begin();
  EXPECT_EQ(iter_copied_tree.GetCurrent()->key_, 10);
  EXPECT_EQ(iter_copied_tree.GetCurrent()->value_, 100);
  iter_copied_tree++;
  EXPECT_EQ(iter_copied_tree.GetCurrent()->key_, 20);
  EXPECT_EQ(iter_copied_tree.GetCurrent()->value_, 200);
}

TEST(TreeTest, Destructor_tree_test_1) {
  s21::AVLTree<int, int> test_tree_1;
  test_tree_1.Insert(10, 100);
  test_tree_1.Insert(20, 200);
  test_tree_1.~AVLTree();
  EXPECT_TRUE(test_tree_1.IsEmpty());
}

TEST(TreeTest, Copy_oper_tree_test_1) {
  s21::AVLTree<int, int> test_tree_1;
  test_tree_1.Insert(10, 100);
  test_tree_1.Insert(20, 200);
  s21::AVLTree<int, int> copied_tree;
  copied_tree.Insert(30, 100);
  copied_tree.Insert(40, 200);
  copied_tree = test_tree_1;
  auto iter_copied_tree = copied_tree.begin();
  EXPECT_EQ(iter_copied_tree.GetCurrent()->key_, 10);
  EXPECT_EQ(iter_copied_tree.GetCurrent()->value_, 100);
  iter_copied_tree++;
  EXPECT_EQ((iter_copied_tree).GetCurrent()->key_, 20);
  EXPECT_EQ(iter_copied_tree.GetCurrent()->value_, 200);
}

TEST(TreeTest, CopyMove_tree_test_1) {
  s21::AVLTree<int, int> tree1;
  tree1.Insert(1, 100);
  s21::AVLTree<int, int> tree2;
  tree2 = std::move(tree1);
  EXPECT_EQ(tree2.GetRoot()->key_, 1);
  EXPECT_EQ(tree2.GetRoot()->value_, 100);
}

TEST(TreeTest, Insert_tree_test_1) {
  s21::AVLTree<int, int> test_tree;
  int answer_list[6] = {6, 19, 10, 17, 15, 23};
  int counter = 0;
  test_tree.Insert(10, 17);
  test_tree.Insert(6, 19);
  test_tree.Insert(15, 23);
  auto bebra = test_tree.begin();
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(bebra.GetCurrent()->key_, answer_list[counter]);
    counter++;
    EXPECT_EQ(bebra.GetCurrent()->value_, answer_list[counter]);
    bebra++;
    counter++;
  }
}

TEST(TreeTest, Get_root_tree_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(10, 17);
  EXPECT_EQ(test_tree.GetRoot()->key_, 10);
  EXPECT_EQ(test_tree.GetRoot()->value_, 17);
}

TEST(TreeTest, swap_tree_test_1) {
  s21::AVLTree<int, int> tree1;
  tree1.Insert(1, 2);
  tree1.Insert(3, 4);
  s21::AVLTree<int, int> tree2;
  tree2.Insert(5, 6);
  tree2.Insert(7, 8);
  tree1.Swap(tree2);
  auto bebra_1 = tree1.begin();
  auto bebra_2 = tree2.begin();
  EXPECT_EQ(bebra_1.GetCurrent()->key_, 5);
  EXPECT_EQ(bebra_1.GetCurrent()->value_, 6);
  EXPECT_EQ(bebra_2.GetCurrent()->key_, 1);
  EXPECT_EQ(bebra_2.GetCurrent()->value_, 2);
  bebra_1++;
  bebra_2++;
  EXPECT_EQ(bebra_1.GetCurrent()->key_, 7);
  EXPECT_EQ(bebra_1.GetCurrent()->value_, 8);
  EXPECT_EQ(bebra_2.GetCurrent()->key_, 3);
  EXPECT_EQ(bebra_2.GetCurrent()->value_, 4);
}

TEST(TreeTest, get_inserted_tree_test_1) {
  s21::AVLTree<int, int> tree1;
  EXPECT_FALSE(tree1.GetInserted());
}

TEST(TreeTest, get_max_key_tree_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(10, 17);
  test_tree.Insert(6, 19);
  test_tree.Insert(15, 23);
  EXPECT_EQ(test_tree.MaximumKey(test_tree.GetRoot())->key_, 15);
  EXPECT_EQ(test_tree.MaximumKey(test_tree.GetRoot())->value_, 23);
}

TEST(TreeTest, get_min_key_tree_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(10, 17);
  test_tree.Insert(6, 19);
  test_tree.Insert(15, 23);
  EXPECT_EQ(test_tree.GetMin()->key_, 6);
  EXPECT_EQ(test_tree.GetMin()->value_, 19);
}

TEST(TreeTest, get_max_without_node_key_tree_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(10, 17);
  test_tree.Insert(6, 19);
  test_tree.Insert(15, 23);
  EXPECT_EQ(test_tree.GetMax()->key_, 15);
  EXPECT_EQ(test_tree.GetMax()->value_, 23);
}

TEST(TreeTest, begin_tree_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(10, 17);
  EXPECT_EQ(test_tree.begin().GetCurrent()->key_, 10);
  EXPECT_EQ(test_tree.begin().GetCurrent()->value_, 17);
}

TEST(TreeTest, end_tree_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(10, 17);
  EXPECT_EQ(test_tree.end().GetCurrent()->key_, 10);
  EXPECT_EQ(test_tree.end().GetCurrent()->value_, 17);
}

TEST(TreeTest, Iterator_move_one_dop_test_2) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(11, 0);
  test_tree.Insert(20, 0);
  test_tree.Insert(4, 0);
  test_tree.Insert(10, 0);
  test_tree.Insert(6, 0);
  test_tree.Insert(15, 0);
  test_tree.Insert(7, 0);
  auto bebra = test_tree.begin();
  bebra++;
  EXPECT_EQ(bebra.GetCurrent()->key_, 6);
}

TEST(TreeTest, Iterator_razomin_test_2) {
  s21::AVLTree<int, int> test_tree;
  auto bebra = test_tree.begin();
  EXPECT_ANY_THROW(*bebra);
}

TEST(TreeTest, decrement_helper_test_1) {
  s21::AVLTree<int, int> test_tree;
  auto bebra = test_tree.begin();
  EXPECT_ANY_THROW(*bebra);
}

TEST(TreeTest, rotate_iter_test_2) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(11, 0);
  test_tree.Insert(20, 0);
  test_tree.Insert(15, 0);
  test_tree.Insert(22, 0);
  test_tree.Insert(18, 0);

  test_tree.Insert(24, 0);
  test_tree.Insert(10, 0);
  test_tree.Insert(6, 0);
  auto bebra = test_tree.begin();
  EXPECT_EQ(bebra.GetCurrent()->key_, 6);
}

TEST(TreeTest, right_left_test_2) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(5, 0);
  test_tree.Insert(3, 0);
  test_tree.Insert(4, 0);
  auto bebra = test_tree.begin();
  EXPECT_EQ(bebra.GetCurrent()->key_, 3);
}

TEST(TreeTest, left_right_test_2) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(5, 0);
  test_tree.Insert(8, 0);
  test_tree.Insert(6, 0);
  auto bebra = test_tree.begin();
  EXPECT_EQ(bebra.GetCurrent()->key_, 5);
}

TEST(TreeTest, decrementdoper_test_2) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(10, 0);
  test_tree.Insert(8, 0);
  test_tree.Insert(9, 0);
  test_tree.Insert(12, 0);
  test_tree.Insert(1, 0);
  auto bebra = test_tree.begin();
  bebra++;
  bebra++;
  bebra++;
  EXPECT_EQ(bebra.GetCurrent()->key_, 10);
}

TEST(TreeTest, remove_test_test_2) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(5, 0);
  test_tree.Insert(8, 0);
  test_tree.Insert(7, 0);
  test_tree.Insert(1, 0);
  test_tree.Insert(6, 0);
  test_tree.Insert(10, 0);
  auto root = test_tree.GetRoot();
  test_tree.Remove_friend(root, 5);
  test_tree.Remove_friend(root, 10);
  auto bebra = test_tree.begin();
  EXPECT_EQ(bebra.GetCurrent()->key_, 1);
}

TEST(TreeTest, remove_test_new_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(5, 0);
  test_tree.Insert(10, 0);
  test_tree.Insert(8, 0);
  test_tree.Insert(3, 0);
  test_tree.Insert(6, 0);
  test_tree.Insert(12, 0);
  test_tree.Insert(11, 0);
  test_tree.Insert(9, 0);
  auto new_root = test_tree.GetRoot();
  test_tree.Remove_friend(new_root, 11);
  auto bebra = test_tree.begin();
  EXPECT_EQ(bebra.GetCurrent()->key_, 3);
}

TEST(TreeTest, remove_test_new_new_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(5, 0);
  test_tree.Insert(10, 0);
  test_tree.Insert(8, 0);
  test_tree.Insert(3, 0);
  test_tree.Insert(6, 0);
  test_tree.Insert(12, 0);
  test_tree.Insert(11, 0);
  test_tree.Insert(9, 0);
  test_tree.Insert(-1, 0);
  test_tree.Insert(-30, 0);
  test_tree.Insert(-15, 0);
  test_tree.Insert(245, 0);
  test_tree.Insert(7, 0);
  test_tree.Insert(0, 0);
  auto bebra = test_tree.begin();
  EXPECT_EQ(bebra.GetCurrent()->key_, -30);
}

TEST(TreeTest, remove_test_new_new_new_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(8, 0);
  test_tree.Insert(5, 0);
  test_tree.Insert(10, 0);
  auto new_root = test_tree.GetRoot();
  test_tree.Remove_friend(new_root, 8);
  auto bebra = test_tree.begin();
  EXPECT_EQ(bebra.GetCurrent()->key_, 5);
}

TEST(TreeTest, remove_test_new_new_2_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(8, 0);
  test_tree.Insert(5, 0);
  test_tree.Insert(10, 0);
  test_tree.Insert(11, 0);
  auto new_root = test_tree.GetRoot();
  test_tree.Remove_friend(new_root, 10);
  auto bebra = test_tree.begin();
  EXPECT_EQ(bebra.GetCurrent()->key_, 5);
}

TEST(TreeTest, remove_test_new_new_3_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(8, 0);
  test_tree.Insert(5, 0);
  test_tree.Insert(10, 0);
  test_tree.Insert(9, 0);
  auto new_root = test_tree.GetRoot();
  test_tree.Remove_friend(new_root, 10);
  auto bebra = test_tree.begin();
  EXPECT_EQ(bebra.GetCurrent()->key_, 5);
}

TEST(TreeTest, decrement_test_test_1) {
  s21::AVLTree<int, int> test_tree;
  test_tree.Insert(5, 0);
  test_tree.Insert(10, 0);
  test_tree.Insert(8, 0);
  test_tree.Insert(3, 0);
  test_tree.Insert(6, 0);
  test_tree.Insert(12, 0);
  test_tree.Insert(11, 0);
  test_tree.Insert(9, 0);
  test_tree.Insert(-1, 0);
  test_tree.Insert(-30, 0);
  test_tree.Insert(-15, 0);
  test_tree.Insert(245, 0);
  test_tree.Insert(7, 0);
  test_tree.Insert(0, 0);
  auto bebra = test_tree.begin();
  for (; bebra.GetCurrent() != nullptr; bebra++) {
    bebra--;
  }
  EXPECT_EQ(bebra.GetCurrent(), nullptr);
}