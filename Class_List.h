#ifndef CLASS_LIST_H_
#define CLASS_LIST_H_

#include <cstddef>
#include <iostream> // DEBUG


template<typename T> struct Node
{
    T value;

    Node<T>* prev = 0;
    Node<T>* next = 0;
};

template <typename Type> class List {
public:
    explicit List(): begin_ptr_(0), end_ptr_(0), length_(0) { }

    explicit List(Type initial_value, size_t amount_nodes) {
      length_ = amount_nodes;

      for (size_t i = 0; i < amount_nodes; ++i) {
        if (!i) {
          end_ptr_ = new Node<Type>;
          begin_ptr_ = end_ptr_;

          end_ptr_->value = initial_value;
        } else {
          end_ptr_->next = new Node<Type>;
          end_ptr_->next->prev = end_ptr_;
          end_ptr_ = end_ptr_->next;

          end_ptr_->value = initial_value;
        }
      }
    }

    List(const List<Type> &other)
        : begin_ptr_(0), end_ptr_(0), length_(other.length_) {
      Node<Type> *current_ptr = other.begin_ptr_;

      while (current_ptr != NULL) {
        if (current_ptr == other.begin_ptr_) {
          begin_ptr_ = new Node<Type>;
          end_ptr_ = begin_ptr_;

          begin_ptr_->value = current_ptr->value;

          current_ptr = current_ptr->next;
        } else {
          end_ptr_->next = new Node<Type>;
          end_ptr_->next->prev = end_ptr_;
          end_ptr_ = end_ptr_->next;

          end_ptr_->value = current_ptr->value;

          current_ptr = current_ptr->next;
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


    // List operator+ (List<T> &term)
    // {

    // }

    void add_end(Type new_value) {
      if (end_ptr_ != NULL) {
        Node<Type> *new_node = new Node<Type>;
        new_node->value = new_value;
        new_node->prev = end_ptr_;
        end_ptr_->next = new_node;
        end_ptr_ = new_node;
      } else {
        end_ptr_ = new Node<Type>;
        begin_ptr_ = end_ptr_;
        end_ptr_->value = new_value;
      }

      length_++;
    }

    void add_begin(Type new_value) {
      if (begin_ptr_ != NULL) {
        Node<Type> *new_node = new Node<Type>;
        new_node->value = new_value;
        new_node->next = begin_ptr_;
        begin_ptr_->prev = new_node;
        begin_ptr_ = new_node;
      } else {
        begin_ptr_ = new Node<Type>;
        end_ptr_ = begin_ptr_;

        begin_ptr_->value = new_value;
      }

      length_++;
    }

    // void add_by(T new_value, size_t index)
    // {

    // }


    size_t length() { return length_; }

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

private:
  Node<Type> *begin_ptr_;
  Node<Type> *end_ptr_;

  size_t length_;
};

#endif