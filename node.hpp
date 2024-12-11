#ifndef NODE
#define NODE 

#include <string>

struct Node {
    Node* left;
    Node* right;
    Node* parent;
    std::string color;
    int value;

    Node(int& val) 
            : left{nullptr}, right{nullptr}, value{val}, color{"BLEACK"}
    {
    }
};

#endif