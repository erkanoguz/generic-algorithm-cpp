#include <iostream>
#include "doubly_linked_list.hpp"


int main()
{
    exo::DoublyLinkedList<int> ds;

    // push node
    for(std::size_t i = 0; i < 10; i++){
        ds.push_front(i*5);
    }
    // ds.print();

    // delete node
    ds.remove(0);
    ds.remove(5);
    ds.remove(45);
    ds.remove(50);
    // ds.remove(20);
    // ds.print();


    /*copy constructor*/
    std::cout << "\n\n******copy ctor********\n";
    exo::DoublyLinkedList<int> ds1(ds);
    ds1.print();
    ds.print();

    /*copy assignemnt*/
    std::cout << "\n\n******copy assignment********\n";
    exo::DoublyLinkedList<int> ds2 = ds;
    ds2.print();
    ds.print();


}