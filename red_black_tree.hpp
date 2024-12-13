#ifndef RBT
#define RBT

#include "node.hpp"

class red_black_tree {
private:
    Node* root;

    void destroy_tree(Node* root);
    void balancing_tree(Node*& root);
    Node* copy_tree(Node* root);

    bool search(Node* node, int val);
    Node* get_min(Node* node);
    Node* get_max(Node* node);
    int get_height(Node* node);
    // Node* insert(Node* node, int val);
    // Node* delete_node(Node* node, int key);

    void preorder(Node* node) const;
    void inorder(Node* node) const;
    void postorder(Node* node) const;

    // int balancing_factor(Node* node); 
    // bool is_balanced(Node* node);
    void left_rotate(Node*& node);
    void right_rotate(Node*& node);

public:
    red_black_tree();
    red_black_tree(int val);

    red_black_tree(const red_black_tree& other);
    red_black_tree& operator=(const red_black_tree& other);

    red_black_tree(red_black_tree&& other);
    red_black_tree& operator=(red_black_tree&& other);

    ~red_black_tree();

    Node* get_root();
    bool search(int val);
    int get_min();

    int get_max();
    // int get_successor(const int& key) const;
    // int get_predecessor(const int& key) const;
    int get_height();
    // void insert(int val);   
    // void delete_node(int key);

    void preorder() const;
    void inorder() const;
    void postorder() const;
    void level_order() const;

    // bool balancing_factor();
    // int get_balancing_factor(Node* node);
    bool is_empty() const;
    // bool validate_rbt_properties() const;
};

#endif