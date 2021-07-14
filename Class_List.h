#ifndef CLASS_LIST_H_
#define CLASS_LIST_H_

#include <cstddef>
#include <iostream> // DEBUG
#include <cassert>  // DEBUG


template<typename T> struct Node
{
    T value;

    Node<T>* prev = 0;
    Node<T>* next = 0;
};

template <class Type> class List {
public:
    explicit List(): begin_ptr_(0), end_ptr_(0), length_(0) { }

    List(Type initial_value, size_t amount_nodes) 
    {
        length_ = amount_nodes;

        for (size_t i = 0; i < amount_nodes; ++i) 
        {
            if (!i) 
            {
                end_ptr_ = new Node<Type>;
                begin_ptr_ = end_ptr_;

                end_ptr_->value = initial_value;
            } 
            else 
            {
                end_ptr_->next = new Node<Type>;
                end_ptr_->next->prev = end_ptr_;
                end_ptr_ = end_ptr_->next;

                end_ptr_->value = initial_value;
            }
        }
    }

    explicit List(const List<Type> &right)
        : begin_ptr_(0), end_ptr_(0), length_(right.length_) 
    {
        Node<Type> *current_ptr = right.begin_ptr_;

        while (current_ptr != NULL) 
        {
            if (current_ptr == right.begin_ptr_) 
            {
                begin_ptr_ = new Node<Type>;
                end_ptr_ = begin_ptr_;

                begin_ptr_->value = current_ptr->value;

                current_ptr = current_ptr->next;
            } 
            else 
            {
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

    List &operator=(List<Type> &right) // need rewrite this method
    {
        if (this != &right) 
        {
            Node<Type> *curr_right_ptr = right.begin_ptr_;
            Node<Type> *curr_left_ptr = begin_ptr_;

            auto min = this->length() < right.length() ? this->length() : right.length();

            for (size_t i = 0; i < min; i++)
            {
                curr_left_ptr->value = curr_right_ptr->value;

                curr_left_ptr = curr_left_ptr->next;
                curr_right_ptr = curr_right_ptr->next;
            }

            if (this->length() > right.length()) // free memory
            {
                auto remainder = this->length() - right.length();

                end_ptr_ = curr_left_ptr->prev;
                end_ptr_->next = 0;

                for (size_t i = 0; i < remainder; ++i)
                {
                    auto temp = curr_left_ptr;
                    curr_left_ptr = temp->next;
                    delete temp;
                }
            }
            else if (this->length() < right.length()) // allocate memory
            {
                if (this->length() == 0)
                {
                    this->length_ = 1;

                    end_ptr_ = new Node<Type>;
                    begin_ptr_ = end_ptr_;

                    end_ptr_->value = curr_right_ptr->value;
                    curr_right_ptr = curr_right_ptr->next;

                }

                auto remainder = right.length() - this->length();

                for (size_t i = 0; i < remainder; ++i)
                {
                    end_ptr_->next = new Node<Type>;

                    end_ptr_->next->value = curr_right_ptr->value;
                    curr_right_ptr = curr_right_ptr->next;

                    end_ptr_->next->prev = end_ptr_;
                    end_ptr_ = end_ptr_->next;
                }
            }
            
            length_ = right.length();
        }

        return *this;
    }

    List &operator+(List<Type> &term)
    {
        List<Type> *A = new List<Type>(*this);
        List<Type> *B = new List<Type>(term);

        A->end_ptr_->next = B->begin_ptr_;
        B->begin_ptr_->prev = A->end_ptr_;

        A->end_ptr_ = B->end_ptr_;
        A->length_ += B->length_;
        return *A;
    }


    void add_end(Type new_value) 
    {
        if (end_ptr_ != NULL) 
        {
            Node<Type> *new_node = new Node<Type>;
            new_node->value = new_value;
            
            new_node->prev = end_ptr_;
            end_ptr_->next = new_node;
            
            end_ptr_ = new_node;
        } 
        else 
        {
            end_ptr_ = new Node<Type>;
            begin_ptr_ = end_ptr_;

            end_ptr_->value = new_value;
        }

        length_++;                                    
    }

    void add_begin(Type new_value)
    {
        if (begin_ptr_ != NULL) 
        {
            Node<Type> *new_node = new Node<Type>;
            new_node->value = new_value;
            
            new_node->next = begin_ptr_;
            begin_ptr_->prev = new_node;
            
            begin_ptr_ = new_node;
        } 
        else
        {
            begin_ptr_ = new Node<Type>;
            end_ptr_ = begin_ptr_;

            begin_ptr_->value = new_value;
        }

        length_++;
    }

    // void add_by(T new_value, size_t index)
    // {

    // }


    Type pop_end()
    {
        Type return_value = NULL;

        if (end_ptr_ != 0)
        {
            return_value = end_ptr_->value;

            if (end_ptr_->prev != 0)
            {
                end_ptr_ = end_ptr_->prev;
                delete end_ptr_->next;
                end_ptr_->next = 0;
            }
            else
            {
                delete end_ptr_;
                end_ptr_ = 0;
                begin_ptr_ = 0;
            }
            --length_;

            return return_value;
        }

        assert("What are you doing here?");
        return return_value;
    }

    Type pop_begin()
    {
        Type return_value = NULL;

        if (end_ptr_ != 0)
        {
            return_value = begin_ptr_->value;
            
            if (begin_ptr_->next != 0)
            {
                begin_ptr_ = begin_ptr_->next;
                delete begin_ptr_->prev;
                begin_ptr_->prev = 0;
            }
            else
            {
                delete begin_ptr_;
                end_ptr_ = 0;
                begin_ptr_ = 0;
            }

            return return_value;
        }

        assert("What are you doing here?");
        return return_value;
    }


    bool empty() { return begin_ptr_ == NULL && end_ptr_ == NULL; }

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