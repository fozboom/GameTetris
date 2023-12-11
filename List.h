#ifndef TETRIS_LIST_H
#define TETRIS_LIST_H
#pragma once
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>

template <typename T, typename Allocator = std::allocator<T>>
class List
{
private:
    size_t size_;

    struct FakeListNode
   {
        FakeListNode* prev;
        FakeListNode* next;
    };

    FakeListNode fake_;

    struct ListNode : public FakeListNode
    {
        T element;
        ListNode(const T& elem) : element(elem) {}
        ListNode(T&& elem) : element(std::move(elem)) {}
    };

    using allocator_traits = std::allocator_traits<Allocator>;
    using node_allocator = typename allocator_traits::template rebind_alloc<ListNode>;
    using node_allocator_traits = typename allocator_traits::template rebind_traits<ListNode>;


    static void connect_nodes(FakeListNode* left, FakeListNode* last)
    {
        left->next = last, last->prev = left;
    }


    node_allocator allocator_;

    template <typename... Args>
    FakeListNode* create_node(const T& value)
    {
        FakeListNode* ptr = node_allocator_traits::allocate(allocator_, 1);
        try {
            node_allocator_traits::construct(allocator_, value);
        } catch (...) {
            node_allocator_traits::deallocate(allocator_, value);
            throw;
        }
        return ptr;
    }

    static void insert_nodes(FakeListNode* node, FakeListNode* left, FakeListNode* last)
    {
        connect_nodes(left, node);
        connect_nodes(node, last);
    }

    void destroy_node(FakeListNode* ptr)
    {
        if (ptr != nullptr)
        {
            node_allocator_traits::destroy(allocator_, static_cast<ListNode*>(ptr));
            node_allocator_traits::deallocate(allocator_, static_cast<ListNode*>(ptr),
                                              1);
        }
    }

    void erase_node(FakeListNode* node)
    {
        if (empty())
        {
            return;
        }
        connect_nodes(node->prev, node->next);
        --size_;
        destroy_node(node);
    }

public:
    List(const Allocator& alloc = Allocator()) : size_(0), allocator_(alloc)
    {
        connect_nodes(&fake_, &fake_);
    }

    List(size_t count, const T& element, const Allocator& alloc = Allocator()): List(alloc)
    {
        size_t ind = 0;
        try {
            for (; ind < count; ++ind) {
                push_back(element);
            }
        } catch (...) {
            for (size_t j = 0; j < ind; ++j) {
                pop_front();
            }
            throw;
        }
    }


    template <bool IsConst>
    class BasicIterator
    {
    private:
        FakeListNode* ptr_;

    public:
        using value_type = T;
        using type = std::conditional_t<IsConst, const T, T>;
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using pointer = type*;
        using reference = type&;

        BasicIterator(FakeListNode* node) : ptr_(node){};

        BasicIterator(const BasicIterator& other) : ptr_(other.ptr_) {}

        BasicIterator& operator=(const BasicIterator& other) { ptr_ = other.ptr_; }

        BasicIterator& operator++()
        {
            ptr_ = ptr_->next;
            return *this;
        }

        BasicIterator operator++(int)
        {
            ptr_ = ptr_->next;
            return BasicIterator(ptr_->prev);
        }

        BasicIterator& operator--()
        {
            ptr_ = ptr_->prev;
            return *this;
        }

        BasicIterator operator--(int)
        {
            ptr_ = ptr_->prev;
            return BasicIterator(ptr_->next);
        }

        reference operator*() { return static_cast<ListNode*>(ptr_)->element; }

        pointer operator->() { return &(this->operator*()); }

        const type& operator*() const
        {
            return static_cast<ListNode*>(ptr_)->element;
        }

        const type* operator->() const { return &(this->operator*()); }

        bool operator==(const BasicIterator& other) const
        {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const BasicIterator& other) const
        {
            return ptr_ != other.ptr_;
        }
    };

    using allocator_type = Allocator;
    using value_type = T;
    using iterator = BasicIterator<false>;
    using const_iterator = BasicIterator<true>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;


    List(const List& other) : List(allocator_traits::select_on_container_copy_construction(other.allocator_)) {
        try {
            for (auto it = other.cbegin(), end = other.cend(); it != end; ++it) {
                push_back(*it);
            }
        } catch (...) {
            while (!empty()) {
                pop_back();
            }
            throw;
        }
    }

    static void swap(List& left, List& rigth)
    {
        if (node_allocator_traits::propagate_on_container_swap::value) {
            std::swap(left.allocator_, rigth.allocator_);
        }

        FakeListNode* tmpl = rigth.fake_.prev;
        FakeListNode* tmpr = rigth.fake_.next;
        if (left.size_ != 0) {
            insert_nodes(&rigth.fake_, left.fake_.prev, left.fake_.next);
        } else {
            connect_nodes(&rigth.fake_, &rigth.fake_);
        }
        if (rigth.size_ != 0) {
            insert_nodes(&left.fake_, tmpl, tmpr);
        } else {
            connect_nodes(&left.fake_, &left.fake_);
        }
        std::swap(left.size_, rigth.size_);
    }

    List(List&& other): List(allocator_traits::select_on_container_copy_construction(other.allocator_))
    {
        if (this == &other)
        {
            return;
        }
        swap(*this, List());
        swap(other, *this);
    }

    List& operator=(List&& other){
        List copy(std::move(other));
        if (node_allocator_traits::propagate_on_container_move_assignment::value) {
            allocator_ = other.allocator_;
        }
        swap(*this, copy);

        return *this;
    }

    List& operator=(const List& other) {
        List copy(other);
        if (node_allocator_traits::propagate_on_container_copy_assignment::value) {
            allocator_ = other.allocator_;
        }
        swap(*this, copy);
        return *this;
    }
    iterator begin() const
    {
        return iterator(const_cast<FakeListNode*>(fake_.next));
    }

    iterator end() const { return iterator(const_cast<FakeListNode*>(&fake_)); }

    const_iterator cbegin() const
    {
        return const_iterator(const_cast<FakeListNode*>(fake_.next));
    }

    const_iterator cend() const
    {
        return const_iterator(const_cast<FakeListNode*>(&fake_));
    }
    void push_back(const T& element) { insert(fake_.prev, &fake_, element); }

    void push_front(const T& element) { insert(&fake_, fake_.next, element); }

    void push_back(T&& element) { insert(fake_.prev, &fake_, element); }

    void push_front(T&& element) { insert(&fake_, fake_.next, element); }

    void pop_back() { erase_node(fake_.prev); }

    void pop_front() { erase_node(fake_.next); }

    bool empty() const { return size_ == 0; }

    size_t size() const { return size_; }

    Allocator get_allocator() const { return allocator_; }

    reverse_iterator rbegin() { return std::make_reverse_iterator(end()); }

    reverse_iterator rend() { return std::make_reverse_iterator(begin()); }

    const_reverse_iterator rcbegin() const {
        return std::make_reverse_iterator(cend());
    }

    const_reverse_iterator rcend() const {
        return std::make_reverse_iterator(cbegin());
    }
    T& front() { return reinterpret_cast<ListNode*>(fake_.next)->element; }

    T& back() { return reinterpret_cast<ListNode*>(fake_.prev)->element; }

    const T& front() const
    {
        return reinterpret_cast<ListNode*>(fake_.next)->element;
    }
    const T& back() const
    {
        return reinterpret_cast<ListNode*>(fake_.prev)->element;
    }

    ~List() {
        while (!empty()) {
            pop_back();
        }
    }
};

#endif //TETRIS_LIST_H