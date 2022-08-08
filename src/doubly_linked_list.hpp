#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include <list>
#include <iostream>
#include <vector>

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


template <typename _Tp>
struct _ListIterator 
{
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = _Tp;
    using pointer  = _Tp*;
    using reference = _Tp&;

    _ListIterator() noexcept { } 

    explicit _ListIterator(detail::Node<_Tp>* node) noexcept 
    : _node(node) { }

    reference operator*() const noexcept 
    {
        return _node->_key;
    }

    pointer operator& () const noexcept
    {
        return &_node->key;
    }

    _ListIterator<_Tp>& operator++() noexcept 
    {
        _node = _node->_next;
        return *this;
    }

    _ListIterator<_Tp> operator++(int) noexcept 
    {
        _ListIterator<_Tp> temp = *this;
        _node = _node->_next;
        return temp;
    }

    _ListIterator<_Tp>& operator--() noexcept 
    {
        _node = _node->prev;
        return *this;
    }

    _ListIterator<_Tp> operator--(int) noexcept 
    {
        _ListIterator<_Tp> temp = *this;
        _node = _node->_prev;
        return temp;
    }

    friend bool operator== (const _ListIterator<_Tp>& lhs, const _ListIterator<_Tp>& rhs) noexcept 
    {
        return lhs._node == rhs._node;
    } 

    friend bool operator!= (const _ListIterator<_Tp>& lhs, const _ListIterator<_Tp>& rhs) noexcept 
    {
        return lhs._node != rhs._node;
    } 

    detail::Node<_Tp>* _node;
};

template <typename _Tp>
struct _ListConstIterator 
{
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = _Tp;
    using pointer  = _Tp*;
    using reference = _Tp&;  

    _ListConstIterator() noexcept { }

    explicit _ListConstIterator(const detail::Node<_Tp>* node) noexcept
    : _node(node) { }

    _ListConstIterator(const _ListConstIterator<T>& listIter) noexcept
    : _node(listIter._node) { }

    reference operator*() const noexcept 
    {
        return _node->_key;
    }

    pointer operator&() const noexcept 
    {
        return &_node->key;
    }

    _ListIterator<_Tp>& operator++() noexcept 
    {
        _node = _node->_next;
        return *this;
    }

    _ListIterator<_Tp> operator++(int) noexcept 
    {
        _ListIterator<_Tp> temp = *this;
        _node = _node->_next;
        return temp;
    }

    _ListIterator<_Tp>& operator--() noexcept 
    {
        _node = _node->prev;
        return *this;
    }

    _ListIterator<_Tp> operator--(int) noexcept 
    {
        _ListIterator<_Tp> temp = *this;
        _node = _node->_prev;
        return temp;
    }

    friend bool operator== (const _ListIterator<_Tp>& lhs, const _ListIterator<_Tp>& rhs) noexcept 
    {
        return lhs._node == rhs._node;
    } 

    friend bool operator!= (const _ListIterator<_Tp>& lhs, const _ListIterator<_Tp>& rhs) noexcept 
    {
        return lhs._node != rhs._node;
    } 

    detail::Node<_Tp>* _node;
};



template <typename T>
class DoublyLinkedList
{
    using Node_t = detail::Node<T>;
public:
    using value_type = T;
    using iterator = _ListIterator<T>;
    using const_iterator = _ListConstIterator<T>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using reverse_iterator = std::reverse_iterator<iterator>;

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

    // iterators
    iterator begin() noexcept { return iterator(_head); }
    const_iterator begin() const noexcept { return const_iterator(_head); }
    iterator end() noexcept { return iterator(_tail); }
    const_iterator end() const noexcept { return const_iterator(_tail); }
    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
    const_iterator cbegin() const noexcept { return const_iterator(_head); }
    const_iterator cend() const noexcept { return const_iterator(_tail); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

    [[nodiscard]] bool empty() const noexcept
    {
        if (_head == nullptr) return true;

        return false;
    }

    std::size_t size() const noexcept 
    {
        return _nodeCount;
    }

    // Element access
    T& front() noexcept 
    { 
        return *begin(); 
    }
    
    const T& front() const noexcept 
    { 
        return *begin(); 
    }

    T& back() noexcept
    {
        return *end();
    }

    const T& back() const noexcept 
    {
        return *end();
    }
    

    // Modifiers
    void push_front(const value_type& key) noexcept
    {
        newNode->_next = _head;
        if (_head != nullptr) {
            _head->_prev = newNode;
        } else {
            _tail = newNode;
        }
        _head = newNode;
    }

    Node_t* _create_node(const value_type& key) 
    {
        Node_t* node = new Node_t(std::move(key));
        return node;
    }

    void _insert(Node_t* node, const value_type& key) noexcept
    {
        Node_t* temp = _create_node(key);


        _listPtr
    }

    Node_t* search(T key) noexcept
    {
        return _do_search(key);
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

    void swap(DoublyLinkedList& rhs) noexcept 
    {
        std::swap(_head, rhs._head);
        std::swap(_tail, rhs._tail);
    }

    void clear() noexcept 
    {
        _remove_all_element();
    }

    template<typename ...Args>
    void emplace_back(Args&& ...args) noexcept 
    {
        (..., push_back(std::forward<Args>(args)));
    }

    template<typename ...Args>
    void emplace_font(Args&& ...args) noexcept 
    {
        (push_front(std::forward<Args>(args)), ...);
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

    Node_t* _listPtr;
};

} // namepscae exo



#endif