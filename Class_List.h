#ifndef CLASS_LIST_H_
#define CLASS_LIST_H_

#include <cstddef>
#include <iostream>
#include <ostream>


template<typename T> struct Node
{
    T value;

    Node<T>* prev = 0;
    Node<T>* next = 0;
};


template<typename T> class List
{
public:
    explicit List(T initial_value, size_t amount_nodes)
    {
        length_ = amount_nodes;

        for (size_t i = 0; i < amount_nodes; ++i)
        {
            if (!i)
            {
                end_ptr_ = new Node<T>;
                begin_ptr_ = end_ptr_;

                end_ptr_->value = initial_value;
            }
            else
            {
                end_ptr_->next = new Node<T>;
                end_ptr_->next->prev = end_ptr_;
                end_ptr_ = end_ptr_->next;
                
                end_ptr_->value = initial_value;
            }
        }
    }

    ~List()
    {
        while (end_ptr_ != begin_ptr_)
        {
            end_ptr_ = end_ptr_->prev;
            delete end_ptr_->next;
        }
        delete begin_ptr_;
    }

    void DEBUGprint()
    {
        auto current_ptr = begin_ptr_;
        while (current_ptr != 0) 
        {
            std::cout << current_ptr->value << ' ' << current_ptr << '\n';
            current_ptr = current_ptr->next;
        }

        std::cout << std::endl;
    }

    size_t length() { return length; }

private:
    Node<T> *begin_ptr_;
    Node<T> *end_ptr_;

    size_t length_;
};

#endif