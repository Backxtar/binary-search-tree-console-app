//
// Created by joerg on 01.07.2021.
//

#ifndef P5_CLION_NODE_H
#define P5_CLION_NODE_H
#include <iostream>

template<typename T>
class Node
{
public:
    T           data;
    Node<T>*    parent;
    Node<T>*    c_left;
    Node<T>*    c_right;
    long        key;

    // Constructor
    Node()
    {
        data    = NULL;
        parent  = nullptr;
        c_left  = nullptr;
        c_right = nullptr;
        key     = NULL;
    }

    // Destructor
    ~Node() = default;
private:
};

#endif //P5_CLION_NODE_H
