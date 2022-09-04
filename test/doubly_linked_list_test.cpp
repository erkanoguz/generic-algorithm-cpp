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
    std::size_t size = l.size();
    auto iterBegin = l.begin();
    auto iterEnd = l.end();

    EXPECT_TRUE(isEmpty);
    EXPECT_EQ(0, size);
    EXPECT_EQ(iterBegin, iterEnd);
}

TEST_F(DoublyLinkedListTest, ConstructorWithSize)
{
    exo::DoublyLinkedList<int> l(10,0);

    bool isEmpty = l.empty();
    std::size_t size = l.size();
    auto iterBegin = l.begin();
    auto iterEnd = l.end();
    int value = l.front();

    EXPECT_FALSE(isEmpty);
    EXPECT_EQ(10, size);
    EXPECT_NE(iterBegin, iterEnd);
    EXPECT_EQ(0, value);
}

TEST_F(DoublyLinkedListTest, ConstructorWithInitializerList)
{
    exo::DoublyLinkedList<int> l{1,5,4,7,8,10};

    bool isEmpty = l.empty();
    std::size_t size = l.size();
    auto iterBegin = l.begin();
    auto iterEnd = l.end();
    int value = l.front();

    EXPECT_FALSE(isEmpty);
    EXPECT_EQ(6, size);
    EXPECT_NE(iterBegin, iterEnd);
    EXPECT_EQ(1, value);
}

TEST_F(DoublyLinkedListTest, CopyConstructor)
{
    exo::DoublyLinkedList<int> l{10,4,5}; 
    exo::DoublyLinkedList copyL(l);

    bool isEmpty = copyL.empty(); 
    std::size_t size = copyL.size();
    auto iterBegin = copyL.begin();
    auto iterEnd = copyL.end();

    EXPECT_FALSE(isEmpty);
    EXPECT_EQ(3, size);
    EXPECT_NE(iterBegin, iterEnd);
}