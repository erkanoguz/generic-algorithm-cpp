#include "gtest/gtest.h"
#include "../src/doubly_linked_list.hpp"

#include <string>

class DoublyLinkedListTest : public ::testing::Test
{
};


TEST_F(DoublyLinkedListTest, DefaultConstructorWithInt) 
{
    exo::DoublyLinkedList<int> l;
    
    bool isEmpty = l.empty();
    bool size = l.size();
    auto iterBegin = l.begin();
    auto iterEnd = l.end();

    EXPECT_TRUE(isEmpty);
    EXPECT_EQ(0, size);
    EXPECT_EQ(iterBegin, iterEnd);
}

TEST_F(DoublyLinkedListTest, DefaultConstructorWithDouble) 
{
    exo::DoublyLinkedList<double> l;
    
    bool isEmpty = l.empty();
    bool size = l.size();
    auto iterBegin = l.begin();
    auto iterEnd = l.end();

    EXPECT_TRUE(isEmpty);
    EXPECT_EQ(0, size);
    EXPECT_EQ(iterBegin, iterEnd);
}

TEST_F(DoublyLinkedListTest, DefaultConstructorWithChar) 
{
    exo::DoublyLinkedList<char> l;
    
    bool isEmpty = l.empty();
    bool size = l.size();
    auto iterBegin = l.begin();
    auto iterEnd = l.end();

    EXPECT_TRUE(isEmpty);
    EXPECT_EQ(0, size);
    EXPECT_EQ(iterBegin, iterEnd);
}

TEST_F(DoublyLinkedListTest, DefaultConstructorWithString) 
{
    exo::DoublyLinkedList<std::string> l;
    
    bool isEmpty = l.empty();
    bool size = l.size();
    auto iterBegin = l.begin();
    auto iterEnd = l.end();

    EXPECT_TRUE(isEmpty);
    EXPECT_EQ(0, size);
    EXPECT_EQ(iterBegin, iterEnd);
}

TEST_F(DoublyLinkedListTest, CopyConstructor)
{
    exo::DoublyLinkedList<int> l{1,2,3,4}
}
