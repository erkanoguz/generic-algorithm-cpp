#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include <memory>

namespace exo
{
namespace detail
{
    template <typename T>
    struct Node 
    {
        T _key;
        Node<T>* _next{nullptr};
        Node<T>* _prev{nullptr};
        Node(T key)
            : _key(std::move(key))
        {}
    };
} // namespace detail


template <typename T>
class DoublyLinkedList
{
    using Node_t = detail::Node<T>;
public:
    DoublyLinkedList()
        :_head(nullptr)
    {}

    ~DoublyLinkedList()
    {}

    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator= (const DoublyLinkedList&) = delete;

    Node_t* search(T key) noexcept
    {
        return _do_search(key);
    }

    void push_front(T key) noexcept
    {
        Node_t* newNode = new Node_t(std::move(key));
        newNode->_next = _head;
        if (_head != nullptr) {
            _head->_prev = newNode;
        }
        _head = newNode;
    }


    void remove(T key) noexcept
    {
        Node_t* node = _do_search(key);

        if (node == nullptr) {
            std::cout << "null\n";
            return;
        }
        if (node == _head) {
            _head = node->_next;
            _head->_prev = nullptr;
        } else if(node->_next == nullptr) {
            node->_prev->_next = nullptr;
        } else {
            node->_prev->_next = node->_next;
            node->_next->_prev = node->_prev;
            delete node;
        }
    }

    void print() noexcept
    {
        Node_t* temp = _head;
        std::cout << "-------------------------------------------\n";
        while(temp != nullptr) {
            std::cout << temp->_key << " ";
            temp = temp->_next;
        }
        std::cout << "\n-------------------------------------------\n";
    }

private:    

    Node_t* _do_search(T key) noexcept 
    {
        Node_t* temp = _head;
    
        while ( temp != nullptr ) {
            if ( temp->_key == key ) return temp;
            temp = temp->_next;
        }   
        return temp;
    }

    Node_t* _head;
};




} // namepscae exo



#endif