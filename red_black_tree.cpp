#include <iostream>
#include "red_black_tree.hpp"
#include <queue>

// Ctor
red_black_tree::red_black_tree() : root{nullptr} { 
    balancing_tree(root);
}

// Ctor 
red_black_tree::red_black_tree(int val) {
    root = new Node(val);
    balancing_tree(root);
}

// Copy Ctor
red_black_tree::red_black_tree(const red_black_tree& other) {
    root = copy_tree(other.root);
}

// Copy assignment Operator
red_black_tree& red_black_tree::operator=(const red_black_tree& other) {
    if(&other != this) {
        destroy_tree(this->root);
        root = copy_tree(other.root);
    }

    return *this;
}

// Move Ctor
red_black_tree::red_black_tree(red_black_tree&& other) {
    destroy_tree(root);
    root = other.root;
    other.root = nullptr;
}

// Move Assignment Operator
red_black_tree& red_black_tree::operator=(red_black_tree&& other) {
    if(this != &other) {
        destroy_tree(this->root);
        root = other.root;
        other.root = nullptr;
    }

    return *this;
}

red_black_tree::~red_black_tree() {
    destroy_tree(root);
}

void red_black_tree::destroy_tree(Node* root) {
    if(root) {
        destroy_tree(root->left);
        destroy_tree(root->right);
        delete root;
    }  
}

void red_black_tree::preorder() const {
    preorder(root);
}

void red_black_tree::inorder() const {
    inorder(root);
}

void red_black_tree::postorder() const {
    postorder(root);
}

void red_black_tree::preorder(Node* node) const {
    if(!node) {
        return;
    }

    std::cout << node->value << " " << node->color << std::endl;
    preorder(node->left);
    preorder(node->right);
}

void red_black_tree::inorder(Node* node) const {
    if(!node) {
        return;
    }

    inorder(node->left);
    std::cout << node->value << " " << node->color << std::endl;
    inorder(node->right);
}

void red_black_tree::postorder(Node* node) const {
    if(!node) {
        return;
    }

    postorder(node->left);
    postorder(node->right);
    std::cout << node->value << " " << node->color << std::endl;
}

void red_black_tree::level_order() const {
    if(!root) {
        return;
    }

    std::queue<Node*> q;
    q.push(root);
    while(!q.empty()) {
        Node* current = q.front();
        q.pop();

        std::cout << current->value << " ";

        if(current->left) {
            q.push(current->left);
        }

        if(current->right) {
            q.push(current->right);
        }
    }
}


