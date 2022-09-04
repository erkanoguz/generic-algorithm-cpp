#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include <iostream>
#include <initializer_list>

#include "common_defs.h"

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

            Node()
            { this->init(); }

            Node(const T& key)
                : _key(key)
            { this->init(); }
            
            void hook(Node* const position) NOEXCEPT 
            {
                this->_next = position;
                this->_prev = position->_prev;
                position->_prev->_next = this;   
                position->_prev = this;
            } 

            void unhook() NOEXCEPT 
            {
                this->_prev->_next = this->_next;
                this->_next->_prev = this->_prev;
            }

            void init() NOEXCEPT 
            { _next = _prev = this; }
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

        _ListIterator() NOEXCEPT { } 

        explicit _ListIterator(detail::Node<_Tp>* node) NOEXCEPT 
        : _node(node) 
        {}

        reference operator*() const NOEXCEPT 
        {  return _node->_key; }

        pointer operator& () const NOEXCEPT
        { return &_node->key; }

        _ListIterator<_Tp>& operator++() NOEXCEPT 
        {
            _node = _node->_next;
            return *this;
        }

        pointer operator->() const NOEXCEPT
        {  return &_node->_key; }
        
        _ListIterator<_Tp> operator++(int) NOEXCEPT 
        {
            _ListIterator<_Tp> temp = *this;
            _node = _node->_next;
            return temp;
        }

        _ListIterator<_Tp>& operator--() NOEXCEPT 
        {
            _node = _node->_prev;
            return *this;
        }

        _ListIterator<_Tp> operator--(int) NOEXCEPT 
        {
            _ListIterator<_Tp> temp = *this;
            _node = _node->_prev;
            return temp;
        }

        friend bool operator== (const _ListIterator<_Tp>& lhs, const _ListIterator<_Tp>& rhs) NOEXCEPT 
        { return lhs._node == rhs._node; } 

        friend bool operator!= (const _ListIterator<_Tp>& lhs, const _ListIterator<_Tp>& rhs) NOEXCEPT 
        { return lhs._node != rhs._node; } 

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

        _ListConstIterator() NOEXCEPT { }

        explicit _ListConstIterator(const detail::Node<_Tp>* node) NOEXCEPT
        : _node(node)
        {}

        _ListConstIterator(const iterator& it) NOEXCEPT 
        : _node(it._node)
        {}

        iterator _const_cast() const NOEXCEPT 
        { return iterator(const_cast<detail::Node<_Tp>*>(_node)); }

        reference operator*() const NOEXCEPT 
        { return const_cast<detail::Node<_Tp>*>(_node)->_key; }

        pointer operator&() const NOEXCEPT 
        { return &_node->key; }

        _ListConstIterator<_Tp>& operator++() NOEXCEPT 
        {
            _node = _node->_next;
            return *this;
        }

        _ListConstIterator<_Tp> operator++(int) NOEXCEPT 
        {
            _ListConstIterator<_Tp> temp = *this;
            _node = _node->_next;
            return temp;
        }

        _ListConstIterator<_Tp>& operator--() NOEXCEPT 
        {
            _node = _node->prev;
            return *this;
        }

        _ListConstIterator<_Tp> operator--(int) NOEXCEPT 
        {
            _ListConstIterator<_Tp> temp = *this;
            _node = _node->_prev;
            return temp;
        }

        friend bool operator== (const _ListConstIterator<_Tp>& lhs, const _ListConstIterator<_Tp>& rhs) NOEXCEPT 
        { return lhs._node == rhs._node; } 

        friend bool operator!= (const _ListConstIterator<_Tp>& lhs, const _ListConstIterator<_Tp>& rhs) NOEXCEPT 
        { return lhs._node != rhs._node; } 

        const detail::Node<_Tp>* _node;
    };

    template <typename T>
    class DoublyLinkedList
    {
        using _Node = detail::Node<T>;
    public:
        using value_type = T;
        using iterator = _ListIterator<T>;
        using const_iterator = _ListConstIterator<T>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using size_type = std::size_t;

        DoublyLinkedList()
            : _nodeCount(0)
            , _listPtr(new _Node)
        {}

        ~DoublyLinkedList()
        { erase(begin(), end()); }

        DoublyLinkedList(const DoublyLinkedList& rhs)
            : _nodeCount(0)
            , _listPtr(new _Node)
        { _default_initialize(rhs.begin(), rhs.end()); }

        explicit DoublyLinkedList(size_type n, const value_type& value)
            : _nodeCount(0)
            , _listPtr(new _Node)
        { _fill_initialize(n, value); }

        DoublyLinkedList& operator= (const DoublyLinkedList& rhs)
        {
            if (*this == rhs) return *this;

            _default_initialize(rhs.begin(), rhs.end());
            return *this;
        }

        DoublyLinkedList(std::initializer_list<T> l)
            : _listPtr(new _Node) 
            , _nodeCount{0}
        {
            auto first = l.begin();
            for (; first != l.end(); ++first) {
                emplace_back(*first);
            }
        }

        DoublyLinkedList(DoublyLinkedList&& rhs) NOEXCEPT = default;
        DoublyLinkedList& operator= (DoublyLinkedList&& rhs) NOEXCEPT = default;

        // iterators
        iterator begin() NOEXCEPT 
        { return iterator(_listPtr->_next); }
        
        const_iterator begin() const NOEXCEPT 
        { return const_iterator(_listPtr->_next); }
        
        iterator end() NOEXCEPT 
        { return iterator(_listPtr); }
        
        const_iterator end() const NOEXCEPT 
        { return const_iterator(_listPtr); }
        
        reverse_iterator rbegin() NOEXCEPT 
        { return reverse_iterator(end()); }
        
        reverse_iterator rend() NOEXCEPT 
        { return reverse_iterator(begin()); }
        
        const_reverse_iterator rbegin() const NOEXCEPT 
        { return const_reverse_iterator(end()); }
        
        const_reverse_iterator rend() const NOEXCEPT 
        { return const_reverse_iterator(begin()); }
        
        const_iterator cbegin() const NOEXCEPT 
        { return const_iterator(_listPtr->_next); }
        
        const_iterator cend() const NOEXCEPT 
        { return const_iterator(_listPtr); }
        
        const_reverse_iterator crbegin() const NOEXCEPT 
        { return const_reverse_iterator(end()); }
        
        const_reverse_iterator crend() const NOEXCEPT 
        { return const_reverse_iterator(begin()); }

        NODISCARD bool empty() const NOEXCEPT
        { return _listPtr == _listPtr->_next; }

        std::size_t size() const NOEXCEPT 
        { return _nodeCount; }

        // Element access
        T& front() NOEXCEPT 
        {  return *begin(); }
        
        const T& front() const NOEXCEPT 
        {  return *begin(); }

        T& back() NOEXCEPT
        { return *end(); }

        const T& back() const NOEXCEPT 
        { return *end(); }
        
        // Modifiers
        void push_front(const value_type& key)
        { _insert(begin(), key); }

        void push_front(value_type&& key) 
        { _insert(begin(), std::move(key)); }

        void push_back(const value_type& key) 
        { _insert(end(), key); }

        void push_back(value_type&& key) 
        { _insert(end(), std::move(key)); }

        template <typename ...Args>
        void emplace_front(Args&& ...args) 
        {
            (..., push_front(std::forward<Args>(args)));
        }

        template <typename ...Args>
        void emplace_back(Args&& ...args) 
        { (..., push_back(std::forward<Args>(args))); }

        void pop_front() NOEXCEPT 
        { _erase(begin()); }

        void pop_back() NOEXCEPT 
        { _erase(iterator(_listPtr->_prev)); }

        iterator erase(const_iterator position) NOEXCEPT 
        {
            iterator ret(position._const_cast()._node->_next);
            _erase(position._const_cast());
            return ret;
        }    

        iterator erase(const_iterator first, const_iterator last) NOEXCEPT 
        {
            while (first != last) 
                first = erase(first);

            return iterator();
        }

        void clear() NOEXCEPT 
        {
            erase(begin(), end());
            _init();
        }

        void swap(DoublyLinkedList& rhs) NOEXCEPT 
        {
            std::swap(_listPtr, rhs._listPtr);
            std::size_t temp = _nodeCount;
            this->_nodeCount = rhs._nodeCount;
            rhs._nodeCount = temp;
        }

        void print() NOEXCEPT
        {
            std::cout << "-------------------------------------------\n";
            auto first = this->begin();
            for(; first != end(); ++first)
                std::cout << *first << " ";
            std::cout << "\n-------------------------------------------\n";
        }

    private:    

        template <typename _Tp>
        void _insert(iterator position, _Tp&& key) NOEXCEPT
        {
            _Node* temp = _create_node(std::forward<_Tp>(key));
            temp->hook(position._node);
            _increase_size(1);
        }

        void _erase(iterator position) 
        {
            position._node->unhook();
            _delete_node(position._node);
            _decrease_size(1);
        }
    
        _Node* _create_node(const value_type& key) 
        {
            _Node* node = new _Node(key);
            return node;
        }

        _Node* _create_node(value_type&& key) 
        {
            _Node* node = new _Node(std::move(key));
            return node;
        }

        void _delete_node(_Node* node) 
        { delete node; }

        void _increase_size(std::size_t n) 
        { _nodeCount += n; }

        void _decrease_size(std::size_t n) 
        { _nodeCount -= n; }

        void _init() NOEXCEPT 
        {
            _nodeCount = 0;
            _listPtr->init();
        }

        template <typename Iterator>
        void _default_initialize(Iterator first, Iterator last) 
        {
            for (; first != last; ++first) {
                emplace_back(*first);
            }
        }

        void _fill_initialize(size_type n, const value_type& value) 
        {
            for (size_type iter = 0; iter < n; ++iter) {
                push_back(value);
            }
        }

        _Node* _listPtr;
        std::size_t _nodeCount;
    };
} // namespace exo



#endif
