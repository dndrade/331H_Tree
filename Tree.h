#pragma once

#include "Node.h"
#include <iostream>

template<typename T>
class Tree : protected Node<T>
{
public:
    virtual ~Tree() = default;

    void insert(T);
    template<typename ... Args>
    void insert(Args...);
    void traverse();
    std::size_t size() const { return _size; }
    std::size_t total_size() const { return _total_size; }

protected:
    virtual void insert_action_if_duplicate(Node<T>*) {}

private:
    void insert_impl(T, Node<T>*);
    static void traverse_impl(Node<T>*);

    std::size_t _size = 0;
    std::size_t _total_size = 0;
};

template<typename T>
void Tree<T>::insert(T data)
{
    ++_total_size;
    insert_impl(data, this);
}

template<typename T>
template<typename... Args>
void Tree<T>::insert(Args... args)
{
    insert(T(args...));
}

template<typename T>
void Tree<T>::insert_impl(T data, Node<T>* node)
{

    if(!node->data)
    {
        node->data = std::make_shared<T>(data);
        ++_size;
    }
    else if(data < *(node->data))
    {
        if(!(node->left))
        {
            node->left = std::make_shared<Node<T>>();
        }
        insert_impl(data, node->left.get());
    }
    else if(*(node->data) == data)
    {
        insert_action_if_duplicate(node);
    }
    else if(data > *(node->data))
    {
        if(!(node->right))
        {
            node->right = std::make_shared<Node<T>>();
        }
        insert_impl(data, node->right.get());
    }
}

template<typename T>
void Tree<T>::traverse()
{
    traverse_impl(this);
}

template<typename T>
void Tree<T>::traverse_impl(Node<T>* node)
{
    if(node->data)
    {
        if (node->left)
        {
            traverse_impl(node->left.get());
        }
        std::cout << *(node->data) << ',';
        if (node->right)
        {
            traverse_impl(node->right.get());
        }
    }
}
