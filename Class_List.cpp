// #include "Class_List.h"
// #include <cstddef>
// #include <iostream>

// template<typename T>
// List<T>::List(size_t amount_nodes, T initial_value)
// {
//     length_ = amount_nodes;
//     item_.value = initial_value;
//     begin_ = &item_;
//     end_ = &item_;

//     for (int i = 0; i < amount_nodes; ++i)
//     {
//         Node<T> temp = new Node<T>;
//         temp.value = initial_value;
//         temp.prev = end_;
//         temp.prev_->next = &temp;
//         end_ = &temp;
//     }
// }

// template<typename T>
// List<T>::~List()
// {
//     std::cout << "lol kek";
// }