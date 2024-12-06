#ifndef NODE
#define NODE 

enum Color {
    RED,
    BLEACK
};

struct Node {
    Node* left;
    Node* right;
    Node* parent;
    Color color;
    int value;

    Node(int& val) 
            : left{nullptr}, right{nullptr}, value{val}, color{BLEACK}
    {
    }
};

#endif