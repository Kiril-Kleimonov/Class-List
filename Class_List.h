#ifndef CLASS_LIST_H_
#define CLASS_LIST_H_

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <exception>
#include <iostream> // DEBUG


template<typename T> struct Node
{
    T value;

    Node<T>* prev = 0;
    Node<T>* next = 0;
};

template <class Type> class List {
public:
    explicit List(): _begin_ptr(0), _end_ptr(0), _length(0) { }

    explicit List(const Type &initial_value, const size_t amount_nodes) 
    {
        _length = amount_nodes;

        for (size_t i = 0; i < amount_nodes; ++i) 
        {
            if (!i) 
            {
                _end_ptr = new Node<Type>;
                _begin_ptr = _end_ptr;

                _end_ptr->value = initial_value;
            } 
            else 
            {
                _end_ptr->next = new Node<Type>;
                _end_ptr->next->prev = _end_ptr;
                _end_ptr = _end_ptr->next;

                _end_ptr->value = initial_value;
            }
        }
    }

    explicit List(const List<Type> &right)
        : _begin_ptr(0), _end_ptr(0), _length(right._length) 
    {
        Node<Type> *current_ptr = right._begin_ptr;

        while (current_ptr != NULL) 
        {
            if (current_ptr == right._begin_ptr) 
            {
                _begin_ptr = new Node<Type>;
                _end_ptr = _begin_ptr;

                _begin_ptr->value = current_ptr->value;

                current_ptr = current_ptr->next;
            } 
            else 
            {
                _end_ptr->next = new Node<Type>;
                _end_ptr->next->prev = _end_ptr;
                _end_ptr = _end_ptr->next;

                _end_ptr->value = current_ptr->value;

                current_ptr = current_ptr->next;
            }
        }
    }

     List(const std::initializer_list<Type> initial_values)
        : _begin_ptr(0), _end_ptr(0), _length(0) 
    {
        for (auto &el: initial_values) add_end(el);        
    }

    ~List()
    {
        clear();
    }

    List& operator=(const List<Type> &right) // need rewrite this method (never)
    {
        if (this != &right) 
        {
            Node<Type> *curr_right_ptr = right._begin_ptr;
            Node<Type> *curr_left_ptr = _begin_ptr;

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

                _end_ptr = curr_left_ptr->prev;
                _end_ptr->next = 0;

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
                    this->_length = 1;

                    _end_ptr = new Node<Type>;
                    _begin_ptr = _end_ptr;

                    _end_ptr->value = curr_right_ptr->value;
                    curr_right_ptr = curr_right_ptr->next;

                }

                auto remainder = right.length() - this->length();

                for (size_t i = 0; i < remainder; ++i)
                {
                    _end_ptr->next = new Node<Type>;

                    _end_ptr->next->value = curr_right_ptr->value;
                    curr_right_ptr = curr_right_ptr->next;

                    _end_ptr->next->prev = _end_ptr;
                    _end_ptr = _end_ptr->next;
                }
            }
            
            _length = right.length();
        }

        return *this;
    }

    void operator=(const std::initializer_list<Type> &initial_values)
    {
        List<Type> temp = initial_values;

        *this = temp;
    }

    List& operator+(List<Type> &term) const
    {
        List<Type> *A = new List<Type>(*this);
        List<Type> *B = new List<Type>(term);

        A->_end_ptr->next = B->_begin_ptr;
        B->_begin_ptr->prev = A->_end_ptr;

        A->_end_ptr = B->_end_ptr;
        A->_length += B->_length;
        return *A;
    }

    Type& operator[](const size_t index)
    {
        if (index >= length()) throw std::invalid_argument("index is invalid");

        Node<Type> *search_ptr;
        if (index < length() - index)
        {
            search_ptr = _begin_ptr;
            for (size_t i = 0; i < index; ++i)
            {
                search_ptr = search_ptr->next;
            }
        }
        else
        {
            search_ptr = _end_ptr;
            for (size_t i = 1; i < length() - index; ++i)
            {
                search_ptr = search_ptr->prev;
            }

        }

        return search_ptr->value;
    }

    void add_end(Type new_value) 
    {
        if (_end_ptr != NULL) 
        {
            Node<Type> *new_node = new Node<Type>;
            new_node->value = new_value;
            
            new_node->prev = _end_ptr;
            _end_ptr->next = new_node;
            
            _end_ptr = new_node;
        } 
        else 
        {
            _end_ptr = new Node<Type>;
            _begin_ptr = _end_ptr;

            _end_ptr->value = new_value;
        }

        _length++;                                    
    }

    void add_begin(Type new_value)
    {
        if (_begin_ptr != NULL) 
        {
            Node<Type> *new_node = new Node<Type>;
            new_node->value = new_value;
            
            new_node->next = _begin_ptr;
            _begin_ptr->prev = new_node;
            
            _begin_ptr = new_node;
        } 
        else
        {
            _begin_ptr = new Node<Type>;
            _end_ptr = _begin_ptr;

            _begin_ptr->value = new_value;
        }

        _length++;
    }

    // void add_by(T new_value, size_t index)
    // {

    // }


    Type pop_end()
    {
        if (empty()) throw std::logic_error("List empty");

        Type return_value;
        return_value = _end_ptr->value;

        if (_end_ptr->prev != 0)
        {
            _end_ptr = _end_ptr->prev;
            delete _end_ptr->next;
            _end_ptr->next = 0;
        }
        else
        {
            delete _end_ptr;
            _end_ptr = 0;
            _begin_ptr = 0;
        }

        _length--;

        return return_value;
    }

    Type pop_begin()
    {
        if (empty()) throw std::logic_error("List empty");
        
        Type return_value;
        return_value = _begin_ptr->value;
        
        if (_begin_ptr->next != 0)
        {
            _begin_ptr = _begin_ptr->next;
            delete _begin_ptr->prev;
            _begin_ptr->prev = 0;
        }
        else
        {
            delete _begin_ptr;
            _end_ptr = 0;
            _begin_ptr = 0;
        }

        _length--;

        return return_value;
    }


    bool empty() const { return _begin_ptr == NULL && _end_ptr == NULL; }

    size_t length() const { return _length; }

    void clear()
    {
        while (_end_ptr != _begin_ptr)
        {
            _end_ptr = _end_ptr->prev;
            delete _end_ptr->next;
        }
        delete _begin_ptr;

        _length = 0;
        _begin_ptr = 0;
        _end_ptr = 0;
    }


    void DEBUGprint()
    {
        auto current_ptr = _begin_ptr;
        while (current_ptr != NULL) 
        {
            std::cout << current_ptr->value << ' ' << current_ptr << '\n';
            current_ptr = current_ptr->next;
        }

        std::cout << std::endl;
    }

private:
  Node<Type> *_begin_ptr;
  Node<Type> *_end_ptr;

  size_t _length;
};

#endif