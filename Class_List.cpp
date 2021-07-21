#include "Class_List.h"

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <exception>
#include <iostream> // DEBUG

template <class Type>
Node<Type>* List<Type>::_get_node_ptr(size_t index)
{
    auto search_ptr = _begin_ptr;

    for (size_t i = 0; i < index; ++i)
    {
        search_ptr = search_ptr->next;
    }

    return search_ptr;
}

template <class Type>
List<Type>::List(): _begin_ptr(0), _end_ptr(0), _length(0) { }

template <class Type>
List<Type>::List(const Type &initial_value, const size_t amount_nodes) 
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

template <class Type>
List<Type>::List(const List<Type> &right)
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

template <class Type>
List<Type>::List(const std::initializer_list<Type> initial_values)
    : _begin_ptr(0), _end_ptr(0), _length(0) 
{
    for (auto &el: initial_values) add_end(el);        
}

template <class Type>
List<Type>::~List()
{
    clear();
}

template <class Type>
List<Type>& List<Type>::operator=(const List<Type> &right) // need rewrite this method (never)
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

template <class Type>
void List<Type>::operator=(const std::initializer_list<Type> &initial_values)
{
    List<Type> temp = initial_values;

    *this = temp;
}

template <class Type>
List<Type>& List<Type>::operator+(List<Type> &term) const
{
    List<Type> *A = new List<Type>(*this);
    List<Type> *B = new List<Type>(term);

    A->_end_ptr->next = B->_begin_ptr;
    B->_begin_ptr->prev = A->_end_ptr;

    A->_end_ptr = B->_end_ptr;
    A->_length += B->_length;
    return *A;
}

template <class Type>
Type& List<Type>::operator[](const size_t index)
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

template <class Type>
void List<Type>::add_end(Type new_value) 
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

template <class Type>
void List<Type>::add_begin(Type new_value)
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

template <class Type>
void List<Type>::add_by(Type new_value, size_t index)
{
    if (index == length()) add_end(new_value);
    else 
    {

        Node<Type> *new_node = new Node<Type>;

        new_node->value = new_value;

        new_node->next = _get_node_ptr(index);
        new_node->prev = new_node->next->prev;

        new_node->next->prev = new_node;
        new_node->prev->next = new_node;
    }
    _length++;
}

template <class Type>
void List<Type>::add_list(List<Type> new_nodes, size_t index)
{
    if (!new_nodes.empty())
    {
        if (index == length())
        {
            _end_ptr->next = new_nodes._begin_ptr;
            new_nodes._begin_ptr->prev = _end_ptr;
            _end_ptr = new_nodes._end_ptr;
        }
        else if (index == 0) 
        {
            _begin_ptr->prev = new_nodes._end_ptr;
            new_nodes._end_ptr->next = _begin_ptr;
            _begin_ptr = new_nodes._begin_ptr;
        }
        else
        {
            auto *place_incert = _get_node_ptr(index);

            place_incert->prev->next = new_nodes._begin_ptr;
            new_nodes._begin_ptr->prev = place_incert->prev;
            
            place_incert->prev = new_nodes._end_ptr;
            new_nodes._end_ptr->next = place_incert;
        }
    }

    _length += new_nodes.length();
    new_nodes._begin_ptr = 0;
    new_nodes._end_ptr = 0;
}

template <class Type>
Type List<Type>::pop_end()
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

template <class Type>
Type List<Type>::pop_begin()
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

template <class Type>
Type List<Type>::pop_by(size_t index)
{
    if (empty()) throw std::logic_error("List empty");
    if (index < 0 || index >= length()) throw std::logic_error("Index out of range");

    if (index == 0) return pop_begin();
    if (index == length() - 1) return pop_end();
    
    auto pop_up_node = _get_node_ptr(index);

    Type value = pop_up_node->value;
    _length--;

    pop_up_node->prev->next = pop_up_node->next;
    pop_up_node->next->prev = pop_up_node->prev;

    delete pop_up_node;
    return value; 
}

template <class Type>
List<Type> List<Type>::pop_slice(size_t size, size_t index)
{
    if (empty()) throw std::logic_error("List empty");
    if (index < 0 || index >= length()) throw std::logic_error("Index out of range");
    if (size <= 0 || size + index > length()) throw std::logic_error("Invalid 'size'");

    List<Type> slice;

    if (size == length())
    {
        slice = *this;
        clear();
    }
    else if (index == 0)
    {
        slice._length = size;
        slice._begin_ptr = _begin_ptr;
        slice._end_ptr = _get_node_ptr(index + size - 1);

        slice._end_ptr->next->prev = slice._begin_ptr->prev;
        _length -= size;

        _begin_ptr = slice._end_ptr->next;  
        slice._end_ptr->next = NULL;
    }
    else if (index + size == length())
    {
        slice._length = size;
        slice._begin_ptr = _get_node_ptr(index);
        slice._end_ptr = _end_ptr;

        slice._begin_ptr->prev->next = slice._end_ptr->next;
        _length -= size;

        _end_ptr = slice._begin_ptr->prev;  
        slice._begin_ptr->prev = NULL; 
    }
    else
    {
        slice._length = size;
        slice._begin_ptr = _get_node_ptr(index);
        slice._end_ptr = _get_node_ptr(index + size - 1);

        slice._begin_ptr->prev->next = slice._end_ptr->next;
        slice._end_ptr->next->prev = slice._begin_ptr->prev;
        _length -= size;

        slice._begin_ptr->prev = NULL;
        slice._end_ptr->next = NULL;  
    }

    return slice;
}

template <class Type>
bool List<Type>::empty() const { return _begin_ptr == NULL && _end_ptr == NULL; }

template <class Type>
size_t List<Type>::length() const { return _length; }

template <class Type>
void List<Type>::clear()
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

template <class Type>
void List<Type>::reverse()
{
    Node<Type> *new_begin_ptr = 0;

    while (_begin_ptr != 0)
    {
        Node<Type> *current_ptr = _begin_ptr->next;
        _begin_ptr->next = new_begin_ptr;
        
        new_begin_ptr = _begin_ptr;
        _begin_ptr = current_ptr;
    }

    _begin_ptr = new_begin_ptr;
}

template <class Type>
List<Type>& List<Type>::map(Type(*mutator)(Type)) const
{
    List<Type> *result = new List<Type>;

    for (Node<Type>* i = _begin_ptr; i != NULL; i = i->next)
    {
        result->add_end(mutator(i->value));
    }

    return *result;
}

template <class Type>
void List<Type>::DEBUGprint()
{
    auto current_ptr = _begin_ptr;
    while (current_ptr != NULL) 
    {
        std::cout << current_ptr->value << ' ' << current_ptr << '\n';
        current_ptr = current_ptr->next;
    }
    std::cout << std::endl;
}