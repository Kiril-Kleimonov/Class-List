#ifndef CLASS_LIST_H_
#define CLASS_LIST_H_

#include <cstddef>
#include <iostream>
#include <iterator>
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
    explicit List(): begin_ptr_(0), end_ptr_(0), length_(0) { }

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


    void add_end(T new_value)
    {
        if (end_ptr_ != NULL)
        {
            Node<T> *new_node = new Node<T>;
            new_node->value = new_value;
            new_node->prev = end_ptr_;
            end_ptr_->next = new_node;
            end_ptr_ = new_node;
        }
        else
        {
            end_ptr_ = new Node<T>;
            begin_ptr_ = end_ptr_;
            end_ptr_->value = new_value;
        }

        length_++;
    }

    void add_begin(T new_value)
    {
        if (begin_ptr_ != NULL)
        {
            Node<T> *new_node = new Node<T>;
            new_node->value = new_value;
            new_node->next = begin_ptr_;
            begin_ptr_->prev = new_node;
            begin_ptr_ = new_node;
        }
        else
        {
            begin_ptr_ = new Node<T>;
            end_ptr_ = begin_ptr_;

            begin_ptr_->value = new_value;
        }

        length_++;
    }

    // void add_by(T new_value, size_t index)
    // {

    // }


    void DEBUGprint()
    {
        auto current_ptr = begin_ptr_;
        while (current_ptr != NULL) 
        {
            std::cout << current_ptr->value << ' ' << current_ptr << '\n';
            current_ptr = current_ptr->next;
        }

        std::cout << std::endl;
    }


    size_t length() { return length_; }

private:
    Node<T> *begin_ptr_;
    Node<T> *end_ptr_;

    size_t length_;
};

#endif