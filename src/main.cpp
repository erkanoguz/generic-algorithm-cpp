#include <iostream>
#include "doubly_linked_list.hpp"


int main()
{
    exo::DoublyLinkedList<int> ds;
    ds.push_front(100);
    ds.print();
}