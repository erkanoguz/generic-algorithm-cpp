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
        std::shared_ptr<T> _next;
        std::shared_ptr<T> _prev;
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
        Node_t* temp = _head;
        while(temp != nullptr && temp->_data != key) {
            temp = temp->next;
        }
        return temp;
    }

    void push_front(T key) noexcept
    {
        std::unique_ptr<T> newNode = std::make_unique<Node_t>(std::move(key));
        if(_head != nullptr) {
            Node_t* temp = _head;
            _head = std::move(newNode);
            _head->next = temp;
            temp->_prev = _head;
        } else {
            _head = std::move(newNode);
        }
    }

    void print() noexcept
    {
        Node_t* temp = _head;
        std::cout << "-------------------------------------------\n";
        while(temp != nullptr) {
            std::cout << temp->_key << " ";
        }
        std::cout << "-------------------------------------------\n";
    }

private:    
    Node_t* _head;
};




} // namepscae exo



#endif