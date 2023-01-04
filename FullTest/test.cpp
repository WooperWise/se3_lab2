#include "pch.h"
#include "ISortedSequence.h"
#include "BackpackItems.cpp"
#include "NTree.cpp"
#include "Hystogram.cpp"
#include "ArraySequence.h"
#include "BinaryTree.h"
#include "BinSearch.h"
#include "BTree.cpp"
#include <vector>

Item item1(10, 50); // 5
Item item2(23, 11); // 0,48
Item item3(56, 64); // 1,14
Item item4(2, 44);  // 22
Item item5(100, 5); // 0,05
Item items[5] = { item1, item2, item3, item4, item5 };
int arr[5] = { 1, 10, 3, 5, 100 };

TEST(SequenceTest, SortItems)
{
	ArraySequence<Item> seq(items, 5);
	ASSERT_EQ(seq.Get(0), item4);
	ASSERT_EQ(seq.Get(1), item1);
	ASSERT_EQ(seq.Get(2), item3);
	ASSERT_EQ(seq.Get(3), item2);
	ASSERT_EQ(seq.Get(4), item5);
}

TEST(TestHystogram, Create)
{
	ArraySequence<int> seq(arr, 5);
	Hystogram hystogram;
	hystogram.CreateRange(1, 3);
	hystogram.CreateRange(10, 100);
	hystogram.CreateRange(5, 60);
	vector<hstgrm> hg = hystogram.CreateHystogram(&seq);
	int arr_ans1[2] = { 3, 1 };
	int arr_ans2[2] = { 100, 10 };
	int arr_ans3[2] = { 10, 5 };
	int arr_ans4[5] = { 100, 10, 5, 3, 1 };
	int* arr_ans[4] = { arr_ans1, arr_ans2, arr_ans3, arr_ans4 };
	for (size_t i = 0; i < hg.size(); i++)
		for (int j = 0; j < hg[i].arr.GetLenght(); j++)
			ASSERT_EQ(hg[i].arr.Get(j), arr_ans[i][j]);
}

TEST(ItemTest, Get)
{
	ASSERT_EQ(item1.GetWeight(), 10);
	ASSERT_EQ(item1.GetCost(), 50);
}

TEST(ItemTest, Operators)
{
	ASSERT_TRUE(item1 > item2);
	ASSERT_TRUE(item2 < item1);
	ASSERT_TRUE(item1 == item1);
}

TEST(BagTest, Get)
{
	ArraySequence<Item>* seq = new ArraySequence<Item>(items, 5);
	Backpack bag(seq, 1000);
	ASSERT_EQ(bag.GetBC(), 1000);
	ASSERT_EQ(bag.GetW(), 191);
	ASSERT_EQ(bag.GetC(), 174);
	ASSERT_EQ(bag.GetItems(), seq);
	delete seq;
}

TEST(BagTest, PushItem)
{
	ArraySequence<Item>* seq = new ArraySequence<Item>(items, 5);
	Backpack bag(seq, 1000);
	Item item6(111, 111);
	bag.PushItem(&item6);
	seq->Append(item6);
	ASSERT_EQ(bag.GetBC(), 1000);
	ASSERT_EQ(bag.GetW(), 191 + 111);
	ASSERT_EQ(bag.GetC(), 174 + 111);
	ASSERT_EQ(bag.GetItems(), seq);
	delete seq;
}

TEST(NTreeTest, Get)
{
	ArraySequence<Item>* seq = new ArraySequence<Item>(items, 5);
	NTreeForBag tree;
	Backpack bag(100);
	tree.TreeBag(seq, &bag);
	ASSERT_EQ(tree.GetData(), item4);
	delete seq;
}

TEST(NTreeTest, Bag)
{
	ArraySequence<Item>* seq = new ArraySequence<Item>(items, 5);
	NTreeForBag tree;
	Backpack bag(100);
	tree.TreeBag(seq, &bag);
	//	std::cout << bag;
	ASSERT_EQ(bag.GetItems()->Get(0), item4);
	ASSERT_EQ(bag.GetItems()->Get(1), item1);
	ASSERT_EQ(bag.GetItems()->Get(2), item3);
	ASSERT_EQ(bag.GetItems()->Get(3), item2);
	delete seq;
}

TEST(BinSearhTest, Search)
{
	ArraySequence<int>* seq = new ArraySequence<int>(arr, 5);
	ASSERT_TRUE(BinSearch<int>::Search(seq, 10));
	ASSERT_TRUE(BinSearch<int>::Search(seq, 100));
	delete seq;
}

TEST(BinaryTreeTest, Find)
{
	ArraySequence<int>* seq = new ArraySequence<int>(arr, 5);
	BinaryTree<int> tree(seq);
	ASSERT_TRUE(tree.Find(100));
	ASSERT_TRUE(tree.Find(10));
	ASSERT_TRUE(tree.Find(5));
	ASSERT_TRUE(tree.Find(3));
	ASSERT_TRUE(tree.Find(1));
	delete seq;
}

TEST(BTreeTest, Search)
{
	BTree tree = BTreeCreate();
	assert(tree);
	for (int i = 0; i < 5; i++)
		BTreeInsert(tree, arr[i]);
	ASSERT_TRUE(BTreeSearch(tree, 10));
	ASSERT_TRUE(BTreeSearch(tree, 100));
	BTreeDestroy(tree);
}


