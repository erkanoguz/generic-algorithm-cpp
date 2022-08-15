#include "gtest/gtest.h"
#include "../src/doubly_linked_list.hpp"

#include <string>

class DoubleLinkedListIterTest : public ::testing::Test
{
};

TEST_F(DoubleLinkedListIterTest, Begin)
{
    exo::DoublyLinkedList<int> list(20, 17);
    exo::DoublyLinkedList<int>::iterator iter = list.begin();
    const exo::DoublyLinkedList<int>::iterator cIter = list.begin();

    EXPECT_TRUE(iter == cIter);
    EXPECT_FALSE(iter != cIter);
    EXPECT_EQ(*iter, *cIter);
}

TEST_F(DoubleLinkedListIterTest, Dereference) 
{
    exo::DoublyLinkedList<int> list(20, 17);

    exo::DoublyLinkedList<int>::iterator iter = list.begin();
    *iter = 20;

    EXPECT_EQ(*iter, 20);
    EXPECT_EQ(*iter, *list.begin());
}

TEST_F(DoubleLinkedListIterTest, Arrow) 
{
    exo::DoublyLinkedList<std::string> list(20, "Test");
//     //for (auto i = list.begin(); i != list.end(); ++i) {
//     //    //EXPECT_EQ(i->size(), 4U);
//     //}
}