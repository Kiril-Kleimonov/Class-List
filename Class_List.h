#ifndef CLASS_LIST_H_
#define CLASS_LIST_H_

#include <cstddef>
#include <initializer_list>

template<typename T> struct Node
{
    T value;
    Node<T>* prev = 0;
    Node<T>* next = 0;
};

template <class Type> class List
{
private:
    Node<Type>* _get_node_ptr(size_t);

public:
    explicit List();
    explicit List(const Type&, const size_t);
    List(const List<Type>&);
    List(const std::initializer_list<Type>);
    ~List();

    List<Type>& operator=(const List<Type>&); // need rewrite this method (never)
    void operator=(const std::initializer_list<Type>&);
    List<Type>& operator+(List<Type>&) const;
    Type& operator[](const size_t);

    void add_end(Type);
    void add_begin(Type);
    void add_by(Type, size_t);
    void add_list(List<Type>, size_t);

    Type pop_end();
    Type pop_begin();
    Type pop_by(size_t);
    List<Type> pop_slice(size_t, size_t);

    List<Type>& map(Type(*)(Type)) const;
    void reverse();
    void clear();

    bool empty() const;
    size_t length() const;

    void DEBUGprint();

private:
  Node<Type> *_begin_ptr;
  Node<Type> *_end_ptr;
  size_t _length;
};

#include "Class_List.cpp"
#endif