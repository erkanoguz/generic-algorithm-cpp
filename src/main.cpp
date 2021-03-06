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


    /*move ctor*/
    std::cout << "\n\n******move ctor********\n";
    exo::DoublyLinkedList<int> ds3 (std::move(ds));
    ds3.print();
    ds.print();

    /*move assignment*/
    std::cout << "\n\n******move assignment********\n";
    exo::DoublyLinkedList<int> ds4  = std::move(ds2);
    ds3.print();
    ds2.print();


    /*clear list*/
    std::cout << "\n\n******clear list********\n";
    ds4.clear();
    ds4.print();


    /*Emplace back*/
    std::cout << "\n\n******emplace back********\n";
    exo::DoublyLinkedList<int> ds7;
    ds7.emplace_back(1,2,3,4,54,-1);
    ds7.print();

    /*Emplace front*/
    std::cout << "\n\n******emplace back********\n";
    exo::DoublyLinkedList<int> ds8;
    ds8.emplace_back(1,2,3,4,54,-1);
    ds8.print();

}