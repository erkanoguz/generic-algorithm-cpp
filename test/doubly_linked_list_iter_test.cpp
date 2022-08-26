#include "gtest/gtest.h"
#include "../src/doubly_linked_list.hpp"

#include <string>
#include <numeric>
#include <iterator>

class DoublyLinkedListIterTest : public ::testing::Test
{
};

TEST_F(DoublyLinkedListIterTest, Begin)
{
    exo::DoublyLinkedList<int> list(20, 17);
    exo::DoublyLinkedList<int>::iterator iter = list.begin();
    const exo::DoublyLinkedList<int>::iterator cIter = list.begin();

    EXPECT_TRUE(iter == cIter);
    EXPECT_FALSE(iter != cIter);
    EXPECT_EQ(*iter, *cIter);
}

TEST_F(DoublyLinkedListIterTest, Dereference) 
{
    exo::DoublyLinkedList<int> list(20, 17);

    exo::DoublyLinkedList<int>::iterator iter = list.begin();
    *iter = 20;

    EXPECT_EQ(*iter, 20);
    EXPECT_EQ(*iter, *list.begin());
}

TEST_F(DoublyLinkedListIterTest, Arrow) 
{
    exo::DoublyLinkedList<std::string> list(20, "Test");
    for (auto i = list.begin(); i != list.end(); ++i) {
       EXPECT_EQ(i->size(), 4U);
    }
}

TEST_F(DoublyLinkedListIterTest, ConstArrow) 
{
    exo::DoublyLinkedList<std::string> list(20, "Test");
    
    const auto iter = list.begin();

    EXPECT_EQ(iter->length(), 4U);
}

TEST_F(DoublyLinkedListIterTest, IntIncrement)
{
    exo::DoublyLinkedList<std::string> list(20, "Test");

    auto i = list.begin();
    auto check = i++;
    
    EXPECT_EQ(i->length(), 4U);
    EXPECT_EQ(check, --i);
}

TEST_F(DoublyLinkedListIterTest, ConstIntIncrement)
{
    exo::DoublyLinkedList<std::string> list(20, "Test a const iter");

    const auto constIter = list.begin();
 
    EXPECT_EQ(constIter->length(), 17U);
}

TEST_F(DoublyLinkedListIterTest, IncrementDecrement)
{
    exo::DoublyLinkedList<int> list(20, 17);

    exo::DoublyLinkedList<int>::iterator iter = list.begin();
    const exo::DoublyLinkedList<int>::iterator constIter = list.begin();
    
    iter++;
    EXPECT_FALSE(iter == constIter);

    iter--;
    EXPECT_TRUE(iter == constIter);

    ++iter;
    EXPECT_FALSE(iter == constIter);

    --iter;
    EXPECT_TRUE(iter == constIter);
}

TEST_F(DoublyLinkedListIterTest, End)
{
    exo::DoublyLinkedList<int> a(20, 17);
    auto iter = a.begin();

    uint32_t count = 0;
    
    for (; iter != a.end(); ++iter) {
        count++;
        EXPECT_EQ(*iter, 17);
    }
    
    EXPECT_EQ(count, 20UL);
}

TEST_F(DoublyLinkedListIterTest, Advance) 
{
    exo::DoublyLinkedList<int> l{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; 

    auto incIter = l.begin();
    std::advance(incIter, 3);

    auto decIter = incIter;
    std::advance(decIter, -2);

    EXPECT_EQ(*incIter, 3);
    EXPECT_EQ(*decIter, 1);
}

TEST_F(DoublyLinkedListIterTest, AccumulateInt)
{
    exo::DoublyLinkedList<int> l{0, 1, 2, 3, 4, 5};

    int sum = std::accumulate(l.begin(), l.end(), 0);

    EXPECT_EQ(15, sum);
}

TEST_F(DoublyLinkedListIterTest, AccumulateIntDouble)
{
    exo::DoublyLinkedList l{0.0, 1.2, 2.2, 3.3, 4.4, 5.5};

    double sum = std::accumulate(l.begin(), l.end(), 0.0);

    EXPECT_EQ(16.6, sum);
}

TEST_F(DoublyLinkedListIterTest, EmptyContainter)
{
    exo::DoublyLinkedList<std::string> l;

    EXPECT_TRUE(l.begin() == l.end());
    EXPECT_TRUE(l.cbegin() == l.cend());
    EXPECT_TRUE(l.rbegin() == l.rend());
    EXPECT_TRUE(l.crbegin() == l.crend());
}

TEST_F(DoublyLinkedListIterTest, Distance)
{
    exo::DoublyLinkedList l{3, 1, 5, 6, 7 ,8};

    auto numOfElem = std::distance(l.begin(), l.end());

    EXPECT_EQ(numOfElem, 6);
}

TEST_F(DoublyLinkedListIterTest, ReverseDistance)
{
    exo::DoublyLinkedList l{3, 1, 5, 6, 7 ,8};

    auto numOfElem = std::distance(l.end(), l.begin());

    EXPECT_EQ(numOfElem, 1);
}