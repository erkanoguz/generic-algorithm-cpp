#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include <list>

/**
 * TODO: add iterator capability
 * 
 */


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
        : _head(nullptr)
        , _tail(nullptr)
    {}

    ~DoublyLinkedList()
    {
        _remove_all_element();
    }

    DoublyLinkedList(const DoublyLinkedList& rhs)
        : _head(nullptr) 
        , _tail(nullptr)
    {
        _allocate_new_list(rhs); 
    }

    DoublyLinkedList& operator= (const DoublyLinkedList& rhs)
    {
        if (*this == rhs) return *this;

        _allocate_new_list(rhs);
        return *this;
    }

    DoublyLinkedList(DoublyLinkedList&& rhs) noexcept 
        : _head(rhs._head)
        , _tail(rhs._tail)
    {
        rhs._tail = nullptr;
        rhs._head = nullptr;
    }

    DoublyLinkedList& operator= (DoublyLinkedList&& rhs) noexcept
    {
        if (_head != nullptr) {
            _remove_all_element();
        }

        _head = rhs._head;
        _tail = rhs._tail;
        rhs._head = nullptr;
        rhs._tail = nullptr;
        return *this;
    }

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
        } else {
            _tail = newNode;
        }
        _head = newNode;
    }

    void push_back(T key) noexcept
    {
        Node_t* newNode = new Node_t(std::move(key));
        if (_tail != nullptr) {
            _tail->_next = newNode;
        } else {
            _head = newNode;
        }
        _tail = newNode;
    }

    void remove(T key) noexcept
    {
        Node_t* node = _do_search(key);

        if (node == nullptr) return;

        if (node == _head) {
            _head = node->_next;
            _head->_prev = nullptr;
            if(node == _tail)  
                _tail = nullptr;
        } else if(node->_next == nullptr) {
            node->_prev->_next = nullptr;
            _tail = node->_prev;
        } else {
            node->_prev->_next = node->_next;
            node->_next->_prev = node->_prev;
        }
        delete node;
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

    void _remove_all_element() noexcept
    {
        while(_head != nullptr) 
        {
            Node_t* dTemp = _head;
            _head = _head->_next;
            delete dTemp;
        }
        _tail = nullptr;
    }

    void _allocate_new_list(const DoublyLinkedList<T>& rhs) noexcept 
    {
        Node_t* temp = rhs._head;
        while(temp != nullptr) {
            push_back(temp->_key);
            temp = temp->_next;
        }  
    }

    Node_t* _head;
    Node_t* _tail;
};




} // namepscae exo



#endif