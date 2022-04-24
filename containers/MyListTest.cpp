#include <gtest/gtest.h>
#include "myList.h"

TEST(correctness, push_back)
{
	MyList<char> l{};
	l.push_back('a');
	l.push_back('b');
	EXPECT_EQ(l.getSize(), 2);
	EXPECT_EQ(*l.begin(), 'a');
	EXPECT_EQ(*l.rbegin(), 'b');
	EXPECT_TRUE(l.end() == nullptr);
	EXPECT_TRUE(l.rend() == nullptr);
}

TEST(correctness, push_front)
{
	MyList<char> l{};
	l.push_front('1');
	l.push_front('2');
	EXPECT_EQ(l.getSize(), 2);
	EXPECT_EQ(*l.begin(), '2');
	EXPECT_EQ(*l.rbegin(), '1');
	EXPECT_TRUE(l.end() == nullptr);
	EXPECT_TRUE(l.rend() == nullptr);
}

TEST(correctness, begin) {
	MyList<int> l{};
	EXPECT_TRUE(l.begin() == nullptr);
	l.push_back(10);
	EXPECT_EQ(*l.begin(), 10);
	//удалить элемент
}

TEST(correctness, end) {
	MyList<int> l{};
	EXPECT_TRUE(l.end() == nullptr);
	l.push_back(10);
	EXPECT_TRUE(l.end() == nullptr);
	//удалить элемент
}

TEST(correctness, rbegin) {
	MyList<int> l{};
	EXPECT_TRUE(l.rbegin() == nullptr);
	l.push_back(10);
	EXPECT_EQ(*l.rbegin(), 10);
	//удалить элемент
}

TEST(correctness, rend) {
	MyList<int> l{};
	EXPECT_TRUE(l.rend() == nullptr);
	l.push_back(10);
	EXPECT_TRUE(l.rend() == nullptr);
	//удалить элемент
}

TEST(correctness, forward_iterator_equals)
{
	MyList<int> l{};
	l.push_back(123);
	MyList<int>::iterator f1 = l.begin();
	MyList<int>::iterator f2 = l.begin();
	EXPECT_TRUE(f1 == f2);
	f2 = l.end();
	EXPECT_TRUE(!(f1 == f2));
}

TEST(correctness, forward_iterator_not_equals)
{
	MyList<int> l{};
	l.push_back(123);
	l.push_back(40);

	MyList<int>::iterator f1 = l.begin();
	MyList<int>::iterator f2 = l.begin();
	EXPECT_TRUE(!(f1 != f2));
	f2 = l.end();
	EXPECT_TRUE(f1 != f2);
}

TEST(correctness, reverse_iterator_equals)
{
	MyList<int> l{};
	l.push_back(123);
	MyList<int>::reverse_iterator f1 = l.rbegin();
	MyList<int>::reverse_iterator f2 = l.rbegin();
	EXPECT_TRUE(f1 == f2);
	f2 = l.rend();
	EXPECT_TRUE(!(f1 == f2));
}

TEST(correctness, reverse_iterator_not_equals)
{
	MyList<int> l{};
	l.push_back(123);
	MyList<int>::reverse_iterator f1 = l.rbegin();
	MyList<int>::reverse_iterator f2 = l.rbegin();
	EXPECT_TRUE(!(f1 != f2));
	f2 = l.rend();
	EXPECT_TRUE(f1 != f2);
}

TEST(correctness, forward_iterator_infix_increment) {
	MyList<int> l{};
	l.push_back(123);
	l.push_back(3450);
	MyList<int>::iterator f1 = l.begin();
	MyList<int>::iterator f2 = ++f1;
	EXPECT_TRUE(*f1 == 3450);
	EXPECT_TRUE(*f2 == 3450);
}

TEST(correctness, forward_iterator_postfix_increment) {
	MyList<int> l{};
	l.push_back(123);
	l.push_back(3450);
	MyList<int>::iterator f1 = l.begin();
	MyList<int>::iterator f2 = f1++;
	EXPECT_TRUE(*f1 == 3450);
	EXPECT_TRUE(*f2 == 123);
}

TEST(correctness, reverse_iterator_infix_increment) {
	MyList<int> l{};
	l.push_back(123);
	l.push_back(3450);
	MyList<int>::reverse_iterator f1 = l.rbegin();
	MyList<int>::reverse_iterator f2 = ++f1;
	EXPECT_TRUE(*f1 == 123);
	EXPECT_TRUE(*f2 == 123);
}

TEST(correctness, reverse_iterator_postfix_increment) {
	MyList<int> l{};
	l.push_back(123);
	l.push_back(3450);
	MyList<int>::reverse_iterator f1 = l.rbegin();
	MyList<int>::reverse_iterator f2 = f1++;
	EXPECT_TRUE(*f1 == 123);
	EXPECT_TRUE(*f2 == 3450);
}

TEST(correctness, insert_before_element)
{
	MyList<int> l{};
	l.push_back(123);
	MyList<int>::iterator f2 = l.insert(l.begin(), 0);
	EXPECT_EQ(*f2, 0);
	EXPECT_EQ(*l.begin(), 0);
	EXPECT_EQ(l.getSize(), 2);
}

TEST(correctness, clear)
{
	MyList<int> l{};
	l.push_back(13);
	l.push_back(25);
	l.clear();
	EXPECT_TRUE(l.begin() == nullptr);
	EXPECT_TRUE(l.rbegin() == nullptr);
	EXPECT_EQ(l.getSize(), 0);
}