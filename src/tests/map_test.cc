#include "tests.h"

TEST(MapTest, MapConstructors_Default) {
  s21::Map<int, int> own;
  std::map<int, int> orig;

  EXPECT_TRUE(own.isEmpty());
  EXPECT_TRUE(orig.empty());
}

TEST(MapTest, MapConstructors_InitializerListInt) {
  s21::Map<int, int> own = {{5, 50}, {6, 60}, {7, 70}};
  std::map<int, int> orig = {{5, 50}, {6, 60}, {7, 70}};
  EXPECT_EQ(own.begin()->first, orig.begin()->first);
}

TEST(MapTest, MapConstructors_InitializerListFloat) {
  s21::Map<float, float> own = {{5.4, 50.1}, {1.6, 6.0}, {7, 70}};
  std::map<float, float> orig = {{5.4, 50.1}, {1.6, 6.0}, {7, 70}};
  EXPECT_EQ(own.begin()->first, orig.begin()->first);
}

TEST(MapTest, MapConstructors_InitializerListString) {
  s21::Map<std::string, int> own = {
      {"Exampletest1", 50}, {"Exampletest3", 60}, {"abobus", 70}};
  std::map<std::string, int> orig = {
      {"Exampletest1", 50}, {"Exampletest3", 60}, {"abobus", 70}};
  EXPECT_EQ(own.begin()->first, orig.begin()->first);
}

TEST(MapTest, MapConstructors_CopyConstructor) {
  s21::Map<int, int> A = {{5, 50}, {6, 60}, {7, 70}};
  s21::Map<int, int> copied = A;
  EXPECT_EQ(A.size(), copied.size());
}

TEST(MapTest, MapConstructors_CopyAssingent) {
  s21::Map<int, int> A = {{5, 50}, {6, 60}, {7, 70}};
  s21::Map<int, int> copied;
  copied = A;
  EXPECT_EQ(A.size(), copied.size());
}

TEST(MapTest, MapConstructors_MoveConstructor) {
  s21::Map<int, int> A = {{5, 50}, {6, 60}, {7, 70}};
  s21::Map<int, int> expected = {{5, 50}, {6, 60}, {7, 70}};
  s21::Map<int, int> moved = std::move(A);
  EXPECT_EQ(expected.size(), moved.size());
}

TEST(MapTest, MapConstructors_MoveAssigment) {
  s21::Map<int, int> A = {{5, 50}, {6, 60}, {7, 70}};
  s21::Map<int, int> expected = {{5, 50}, {6, 60}, {7, 70}};
  s21::Map<int, int> moved;
  moved = std::move(A);
  EXPECT_TRUE(A.empty());
  EXPECT_EQ(expected.size(), moved.size());
}

TEST(MapTest, MapIterator_MapIteratorPlus) {
  s21::Map<int, int> A = {{5, 50}, {6, 60}, {7, 70}, {8, 80}};
  auto itr = A.begin();
  itr++;
  EXPECT_EQ(itr->first, 6);
  EXPECT_EQ(itr->second, 60);
  ++itr;
  EXPECT_EQ(itr->first, 7);
  EXPECT_EQ(itr->second, 70);
}

TEST(MapTest, MapIterator_MapIteratorMinus) {
  s21::Map<int, int> A = {{5, 50}, {6, 60}, {7, 70}, {8, 80}};
  auto itr = A.end();
  --itr;
  EXPECT_EQ(itr->first, 7);
  EXPECT_EQ(itr->second, 70);
  itr--;
  EXPECT_EQ(itr->first, 6);
  EXPECT_EQ(itr->second, 60);
}

TEST(MapTest, MapIterator_MapIteratorString) {
  s21::Map<std::string, std::string> A = {{"Exampletest1", "Exampletest2"},
                                          {"Exampletest3", "Exampletest4"},
                                          {"Exampletest5", "Exampletest6"},
                                          {"No name", "No nickname"}};
  auto itr = A.begin();
  EXPECT_EQ(itr->first, "Exampletest1");
  EXPECT_EQ(itr->second, "Exampletest2");
  ++itr;
  EXPECT_EQ(itr->first, "Exampletest3");
  EXPECT_EQ(itr->second, "Exampletest4");
}

TEST(MapTest, MapFind_FindAndModify) {
  s21::Map<std::string, std::string> A = {{"Exampletest1", "Exampletest2"},
                                          {"Exampletest3", "Exampletest4"},
                                          {"Exampletest5", "Exampletest6"},
                                          {"Exampletest7", "kek"}};
  auto it = A.find("Exampletest7");
  EXPECT_EQ(it->second, "kek");
  it->second = "lolkek";
  EXPECT_EQ(A.find("Exampletest7")->second, "lolkek");
}

TEST(MapTest, MapFind_JustFind) {
  s21::Map<int, std::string> A = {{1, "Exampletest2"},
                                  {2, "Exampletest4"},
                                  {3, "Exampletest6"},
                                  {4, "dreamcat"}};
  auto it = A.find(2);
  EXPECT_EQ(it->second, "Exampletest4");
}

TEST(MapTest, MapClear_Test1) {
  s21::Map<std::string, std::string> A = {{"Exampletest1", "Exampletest2"},
                                          {"Exampletest3", "Exampletest4"},
                                          {"Exampletest5", "Exampletest6"},
                                          {"Exampletest7", "kek"}};
  A.clear();
  EXPECT_TRUE(A.empty());
}

TEST(MapTest, MapClear_Test2) {
  s21::Map<std::string, std::string> A = {{"Exampletest1", "Exampletest2"},
                                          {"Exampletest3", "Exampletest4"},
                                          {"Exampletest5", "Exampletest6"},
                                          {"Exampletest7", "kek"}};
  A.clear();
  EXPECT_TRUE(A.empty());
}

TEST(MapTest, MapClear_ClearEmptyMap) {
  s21::Map<std::string, std::string> my_map;
  my_map.clear();
  EXPECT_TRUE(my_map.empty());
}

TEST(MapTest, MapAt_Test0) {
  s21::Map<int, int> a{{1, 10}, {2, 20}, {3, 30}};
  std::map<int, int> b{{1, 10}, {2, 20}, {3, 30}};

  EXPECT_EQ(a.at(2), b.at(2));
  EXPECT_EQ(a.at(2), 20);
  EXPECT_ANY_THROW(a.at(5));
  EXPECT_ANY_THROW(b.at(5));
}

TEST(MapTest, MapSquareBrackets_Test0) {
  s21::Map<int, int> a{{1, 10}, {2, 20}, {3, 30}};
  std::map<int, int> b{{1, 10}, {2, 20}, {3, 30}};
  b[2] = 5;
  a[2] = 5;
  EXPECT_EQ(a[2], 5);
  EXPECT_EQ(b[2], 5);
}

TEST(MapTest, MapSquareBrackets_Test1) {
  s21::Map<int, int> a{{1, 10}, {2, 20}, {3, 30}};
  std::map<int, int> b{{1, 10}, {2, 20}, {3, 30}};

  b[4] = 5;
  EXPECT_EQ(b[4], 5);
}

TEST(MapTest, MapSquareBrackets_Test2) {
  s21::Map<std::string, std::string> a = {{"Exampletest1", "Exampletest2"},
                                          {"Exampletest3", "Exampletest4"},
                                          {"Exampletest5", "Exampletest6"},
                                          {"Exampletest7", "kek"}};
  EXPECT_EQ(a["Exampletest3"], "Exampletest4");
}

TEST(MapTest, MapInsert_BaseInsert) {
  s21::Map<std::string, std::string> my_map = {
      {"Exampletest1", "Exampletest2"}};
  my_map.insert({"Exampletest3", "Exampletest4"});
  EXPECT_EQ(my_map["Exampletest3"], "Exampletest4");
}

TEST(MapTest, MapInsert_InsertExistingKey) {
  s21::Map<std::string, std::string> my_map = {
      {"Exampletest1", "Exampletest2"}, {"Exampletest3", "Exampletest4"}};
  my_map.insert({"Exampletest3", "Liyaskin"});
  EXPECT_EQ(my_map["Exampletest3"], "Exampletest4");
}

TEST(MapTest, MapInsert_InsertInEmptyMap) {
  s21::Map<std::string, std::string> my_map;
  my_map.insert({"Exampletest3", "Exampletest4"});
  EXPECT_EQ(my_map["Exampletest3"], "Exampletest4");
}

TEST(MapTest, MapInsert_InsertMultipleElements) {
  s21::Map<std::string, std::string> my_map;
  my_map.insert({"Exampletest3", "Exampletest4"});
  my_map.insert({"Exampletest1", "Exampletest2"});
  my_map.insert({"Exampletest5", "Exampletest6"});
  EXPECT_EQ(my_map["Exampletest3"], "Exampletest4");
  EXPECT_EQ(my_map["Exampletest1"], "Exampletest2");
}

TEST(MapTest, MapInsertByKeyVal_InsertExistingKey) {
  s21::Map<std::string, std::string> my_map = {
      {"Exampletest1", "Exampletest2"}, {"Exampletest3", "Exampletest4"}};
  my_map.insert({"Exampletest3", "Liyaskin"});
  EXPECT_EQ(my_map["Exampletest1"], "Exampletest2");
}

TEST(MapTest, MapInsertByKeyVal_InsertMultipleElements) {
  s21::Map<std::string, std::string> my_map;
  my_map.insert({"Exampletest3", "Exampletest4"});
  my_map.insert({"Exampletest1", "Exampletest2"});
  my_map.insert({"Exampletest5", "Exampletest6"});
  EXPECT_EQ(my_map["Exampletest3"], "Exampletest4");
  EXPECT_EQ(my_map["Exampletest5"], "Exampletest6");
  EXPECT_EQ(my_map["Exampletest1"], "Exampletest2");
}

TEST(MapTest, MapInsertOrAssign_InsertValue) {
  s21::Map<std::string, std::string> my_map = {{"Exampletest1", "unknown"},
                                               {"Exampletest3", "unknown"}};
  auto insert_res = my_map.insert_or_assign("Exampletest5", "Exampletest6");
  EXPECT_TRUE(insert_res.second);
  EXPECT_EQ(my_map["Exampletest5"], "Exampletest6");
}

TEST(MapTest, MapErase_EmptyMap) {
  s21::Map<int, int> my_map;
  my_map.erase(my_map.begin());
  EXPECT_TRUE(my_map.empty());
}

TEST(MapTest, MapErase_ExistingElement) {
  s21::Map<int, int> my_map = {{1, 10}, {2, 20}, {3, 30}};
  my_map.erase(++my_map.begin());
  EXPECT_FALSE(my_map.contains(2));
}

TEST(MapTest, MapErase_EraseSearchedElements) {
  s21::Map<std::string, std::string> my_map = {{"Exampletest1", "Exampletest2"},
                                               {"Exampletest3", "Exampletest4"},
                                               {"Exampletest5", "Exampletest6"},
                                               {"Exampletest7", "kek"}};
  my_map.erase(my_map.find("Exampletest7"));
  EXPECT_FALSE(my_map.contains("Exampletest7"));
}

TEST(MapTest, MapContains_EmptyMap) {
  s21::Map<int, std::string> my_map;
  EXPECT_FALSE(my_map.contains(5));
}

TEST(MapTest, MapContains_SingleElementPresent) {
  s21::Map<int, std::string> my_map = {{1, "one"}};
  EXPECT_TRUE(my_map.contains(1));
}

TEST(MapTest, MapContains_SingleElementAbsent) {
  s21::Map<int, std::string> my_map = {{1, "one"}};
  EXPECT_FALSE(my_map.contains(2));
}

TEST(MapTest, MapContains_MultipleElementsPresent) {
  s21::Map<char, int> my_map = {{'a', 1}, {'b', 2}, {'c', 3}};
  EXPECT_TRUE(my_map.contains('b'));
}

TEST(MapTest, MapContains_MultipleElementsAbsent) {
  s21::Map<char, int> my_map = {{'a', 1}, {'b', 2}, {'c', 3}};
  EXPECT_FALSE(my_map.contains('d'));
}

TEST(MapTest, MapSwapTest_SwapEmptyMapWithNonEmptyMap) {
  s21::Map<int, std::string> map1;
  s21::Map<int, std::string> map2 = {{1, "one"}, {2, "two"}, {3, "three"}};
  map1.swap(map2);
  EXPECT_TRUE(map2.empty());
}

TEST(MapTest, MapSwapTest_SwapNonEmptyMapWithEmptyMap) {
  s21::Map<int, std::string> map1 = {{1, "one"}, {2, "two"}, {3, "three"}};
  s21::Map<int, std::string> map2;
  map1.swap(map2);
  EXPECT_TRUE(map1.empty());
}

TEST(MapTest, MapSwapTest_SwapNonEmptyMaps) {
  s21::Map<int, std::string> map1 = {{1, "one"}, {2, "two"}, {3, "three"}};
  s21::Map<int, std::string> map2 = {{4, "four"}, {5, "five"}};
  int size_map1 = map1.size();
  int size_map2 = map2.size();
  map1.swap(map2);
  EXPECT_EQ(map1.size(), size_map2);
  EXPECT_EQ(map2.size(), size_map1);
}

TEST(MapTest, MapSwapTest_ValidIteratorsAfterSwap) {
  s21::Map<int, std::string> map1 = {{1, "one"}, {2, "two"}, {3, "three"}};
  s21::Map<int, std::string> map2 = {{4, "four"}, {5, "five"}};
  auto it_map1_begin = map1.begin();
  auto it_map2_begin = map2.begin();
  map1.swap(map2);
  EXPECT_TRUE(it_map1_begin == map2.begin());
  EXPECT_TRUE(it_map2_begin == map1.begin());
}

TEST(MapTest, MapTestMerge_Test1) {
  s21::Map<int, std::string> a{{1, "apple"}, {5, "pear"}, {10, "banana"}};
  s21::Map<int, std::string> c{
      {2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};
  a.merge(c);
  EXPECT_EQ(a.size(), 6);
}

TEST(MapTest, MapTestMerge_Test2) {
  s21::Map<int, std::string> a{{1, "apple"}, {2, "test"}};
  EXPECT_EQ(a.size(), 2);
}

TEST(MapTest, MapTestMerge_Test3) {
  s21::Map<int, std::string> a{{1, "apple"}, {5, "pear"}, {10, "banana"}};
  s21::Map<int, std::string> c{
      {2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};
  a.merge(c);
  EXPECT_EQ(a[1], "apple");
}

TEST(MapTest, MapMergeTest_MergeEmptyMaps) {
  s21::Map<int, std::string> map1;
  s21::Map<int, std::string> map2;
  map1.merge(map2);
  EXPECT_TRUE(map1.empty());
  EXPECT_TRUE(map2.empty());
}

TEST(MapTest, MapMergeTest_MergeNonEmptyMapIntoNonEmptyMap) {
  s21::Map<int, std::string> map1 = {{1, "one"}, {2, "two"}};
  s21::Map<int, std::string> map2 = {{3, "three"}, {4, "four"}};
  map1.merge(map2);
  EXPECT_TRUE(map2.empty());
}

TEST(MapTest, MapMergeTest_SelfMerge) {
  s21::Map<int, std::string> my_map = {{1, "one"}, {2, "two"}};
  my_map.merge(my_map);
  EXPECT_EQ(my_map.size(), 2);
  EXPECT_EQ(my_map[1], "one");
  EXPECT_EQ(my_map[2], "two");
}

TEST(MapTest, MapSquareBracketsNotElement_Test0) {
  s21::Map<int, int> a{{1, 10}, {2, 20}, {3, 30}};
  a[6] = 0;
  EXPECT_EQ(a[6], 0);
}

TEST(MapTest, InsertManyTest_Test0) {
  s21::Map<int, std::string> map1;
  map1.insert_many(1, "one", 2, "two", 3, "three");
  auto it = map1.begin();
  EXPECT_EQ(it.GetCurrent()->key_, 1);
  EXPECT_EQ(it.GetCurrent()->value_, "one");
  it++;
  EXPECT_EQ(it.GetCurrent()->key_, 2);
  EXPECT_EQ(it.GetCurrent()->value_, "two");
  it++;
  EXPECT_EQ(it.GetCurrent()->key_, 3);
  EXPECT_EQ(it.GetCurrent()->value_, "three");
}