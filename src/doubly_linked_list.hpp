#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include <list>
#include <iostream>

namespace exo
{
namespace detail
{
    template <typename T>
    struct Node 
    {
        T _key;
        Node<T>* _next;
        Node<T>* _prev;

        Node(const T& key)
            : _key(key)
        { 
            this->init();
        }
        
        void hook(Node* const position) noexcept 
        {
            this->_next = position;
            this->_prev = position->_prev;
            position->_prev->_next = this;   
            position->_prev = this;
        } 

        void unhook() noexcept 
        {
            this->_prev->_next = this->_next;
            this->_next->_prev = this->_prev;
        }

        void init() noexcept 
        {
            _next = _prev = this;
        }
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
    : _node(node) 
    {}

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

    using iterator = _ListIterator<_Tp>;

    _ListConstIterator() noexcept { }

    explicit _ListConstIterator(const detail::Node<_Tp>* node) noexcept
    : _node(node)
    {
        std::cout << "test\n";
    }

    _ListConstIterator(const iterator& it) noexcept 
    : _node(it._node)
    {}

    iterator _const_cast() const noexcept 
    {
        return iterator(const_cast<detail::Node<_Tp>*>(_node));
    }

    reference operator*() const noexcept 
    {
        return _node->_key;
    }

    pointer operator&() const noexcept 
    {
        return &_node->key;
    }

    _ListConstIterator<_Tp>& operator++() noexcept 
    {
        _node = _node->_next;
        return *this;
    }

    _ListConstIterator<_Tp> operator++(int) noexcept 
    {
        _ListConstIterator<_Tp> temp = *this;
        _node = _node->_next;
        return temp;
    }

    _ListConstIterator<_Tp>& operator--() noexcept 
    {
        _node = _node->prev;
        return *this;
    }

    _ListConstIterator<_Tp> operator--(int) noexcept 
    {
        _ListConstIterator<_Tp> temp = *this;
        _node = _node->_prev;
        return temp;
    }

    friend bool operator== (const _ListConstIterator<_Tp>& lhs, const _ListConstIterator<_Tp>& rhs) noexcept 
    {
        return lhs._node == rhs._node;
    } 

    friend bool operator!= (const _ListConstIterator<_Tp>& lhs, const _ListConstIterator<_Tp>& rhs) noexcept 
    {
        return lhs._node != rhs._node;
    } 

    const detail::Node<_Tp>* _node;
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
        : _nodeCount(0)
        , _listPtr(new Node_t(0))
    {}

    ~DoublyLinkedList()
    {
        erase(begin(), end());
    }

    DoublyLinkedList(const DoublyLinkedList& rhs)
        : _nodeCount(0)
    {
        _fill_initialize(rhs.begin(), rhs.end());
    }

    DoublyLinkedList& operator= (const DoublyLinkedList& rhs)
    {
        if (*this == rhs) return *this;

        _fill_initialize(rhs.begin(), rhs.end());
        return *this;
    }

    DoublyLinkedList(DoublyLinkedList&& rhs) noexcept = default;
    DoublyLinkedList& operator= (DoublyLinkedList&& rhs) noexcept = default;

    // iterators
    iterator begin() noexcept { return iterator(_listPtr->_next); }
    const_iterator begin() const noexcept { return const_iterator(_listPtr->_next); }
    iterator end() noexcept { return iterator(_listPtr); }
    const_iterator end() const noexcept { return const_iterator(_listPtr); }
    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
    const_iterator cbegin() const noexcept { return const_iterator(_listPtr->_next); }
    const_iterator cend() const noexcept { return const_iterator(_listPtr); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

    [[nodiscard]] bool empty() const noexcept
    {
        return _listPtr == _listPtr->_next;
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
    void push_front(const value_type& key)
    {
        _insert(begin(), key);
    }

    void push_front(value_type&& key) 
    {
        _insert(begin(), std::move(key));
    }

    void push_back(const value_type& key) 
    {
        _insert(end(), key);
    }

    void push_back(value_type&& key) 
    {
        _insert(end(), std::move(key));
    }

    template <typename ...Args>
    void emplace_front(Args&& ...args) 
    {
        (..., push_front(std::forward<Args>(args)));
    }

    template <typename ...Args>
    void emplace_back(Args&& ...args) 
    {
        (..., push_back(std::forward<Args>(args)));
    }

    void pop_front() noexcept 
    {
        _erase(begin());
    }

    void pop_back() noexcept 
    {
        _erase(iterator(_listPtr->_prev));
    }

    iterator erase(const_iterator position) noexcept 
    {
            iterator ret(position._const_cast()._node->_next);
        _erase(position._const_cast());
        return ret;
    }    

    iterator erase(const_iterator first, const_iterator last) noexcept 
    {
        while (first != last) 
            first = erase(first);

        return iterator();
    }

    void clear() noexcept 
    {
        erase(begin(), end());
        _init();
    }

    void swap(DoublyLinkedList& rhs) noexcept 
    {
        std::swap(_listPtr, rhs._listPtr);
        std::size_t temp = _nodeCount;
        this->_nodeCount = rhs._nodeCount;
        rhs._nodeCount = temp;
    }

    void print() noexcept
    {
        std::cout << "-------------------------------------------\n";
        auto first = this->begin();
        for(; first != end(); ++first)
            std::cout << *first << " ";
        std::cout << "\n-------------------------------------------\n";
    }

private:    

    template <typename _Tp>
    void _insert(iterator position, _Tp&& key) noexcept
    {
        Node_t* temp = _create_node(std::forward<_Tp>(key));
        temp->hook(position._node);
        _increase_size(1);
    }

    void _erase(iterator position) 
    {
        position._node->unhook();
        _delete_node(position._node);
        _decrease_size(1);
    }
 
    Node_t* _create_node(const value_type& key) 
    {
        Node_t* node = new Node_t(key);
        return node;
    }

    Node_t* _create_node(value_type&& key) 
    {
        Node_t* node = new Node_t(std::move(key));
        return node;
    }

    void _delete_node(Node_t* node) 
    {
        delete node;
    }

    void _increase_size(std::size_t n) 
    {
        _nodeCount += n;
    }

    void _decrease_size(std::size_t n) 
    {
        _nodeCount -= n;
    }

    void _init() noexcept 
    {
        _nodeCount = 0;
        _listPtr->init();
    }

    void _fill_initialize(iterator first, iterator last) 
    {
        for (; first != last; ++first)
            emplace_back(*first);
    }

    Node_t* _listPtr;
    std::size_t _nodeCount;
};

} // namepscae exo



#endif