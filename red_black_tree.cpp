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

    std::cout << node->value << " - " << node->color << std::endl;
    preorder(node->left);
    preorder(node->right);
}

void red_black_tree::inorder(Node* node) const {
    if(!node) {
        return;
    }

    inorder(node->left);
    std::cout << node->value << " - " << node->color << std::endl;
    inorder(node->right);
}

void red_black_tree::postorder(Node* node) const {
    if(!node) {
        return;
    }

    postorder(node->left);
    postorder(node->right);
    std::cout << node->value << " - " << node->color << std::endl;
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

Node* red_black_tree::copy_tree(Node* node) {
    if(!node) {
        return nullptr;
    }

    Node* new_node = new Node(node->value);
    new_node->color = node->color;
    new_node->left = copy_tree(node->left);
    new_node->right = copy_tree(node->right);

    return new_node;
}

bool red_black_tree::search(Node* node, int val) {
    if(!node) {
        return false;
    }

    if(node->value == val) {
        return true;
    } else if(node->value < val) {
        return search(node->right, val);
    } else {
        return search(node->left, val);
    }
}

bool red_black_tree::search(int val) {
    if(!root) {
        return false;
    }

    return search(root, val);
}

Node* red_black_tree::get_min(Node* node) {
    while(node->left) {
        node = node->left;
    }

    return node;
}

int red_black_tree::get_min() {
    Node* tmp = get_min(root);
    return tmp->value;
}

Node* red_black_tree::get_max(Node* node) {
    while(node->right) {
        node = node->right;
    }

    return node;
}

int red_black_tree::get_max() {
    Node* tmp = get_max(root);
    return tmp->value;
}

Node* red_black_tree::get_root() {
    return root;
}

bool red_black_tree::is_empty() const {
    if(!root) {
        return true;
    }

    return false;
}

int red_black_tree::get_height(Node* node) {
    if(!node) {
        return -1;
    }

    int left_height = get_height(node->left);
    int right_height = get_height(node->right);

    return std::max(left_height, right_height) + 1;
}

int red_black_tree::get_height() {
    return get_height(root);
}

void red_black_tree::balancing_tree(Node*& root) {
    Node* parent = nullptr;
    Node* grandparent = nullptr;

    while (root != this->root && root->color == "RED" && root->parent->color == "RED") {
        parent = root->parent;
        grandparent = parent->parent;

        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;

            if (uncle != nullptr && uncle->color == "RED") {
                grandparent->color = "RED";
                parent->color = "BLACK";
                uncle->color = "BLACK";
                root = grandparent;
            } else {
                if (root == parent->right) {
                    root = parent;
                    left_rotate(root);
                }

                parent->color = "BLACK";
                grandparent->color = "RED";
                right_rotate(grandparent);
            }
        } else { 
            Node* uncle = grandparent->left;

            if (uncle != nullptr && uncle->color == "RED") {
                grandparent->color = "RED";
                parent->color = "BLACK";
                uncle->color = "BLACK";
                root = grandparent;
            } else {
                if (root == parent->left) {
                    root = parent;
                    right_rotate(root);
                }

                parent->color = "BLACK";
                grandparent->color = "RED";
                left_rotate(grandparent);
            }
        }
    }

    this->root->color = "BLACK"; 
}

void red_black_tree::left_rotate(Node*& node) {
    Node* right_child = node->right;
    node->right = right_child->left;

    if (right_child->left != nullptr) {
        right_child->left->parent = node;
    }

    right_child->parent = node->parent;

    if (node->parent == nullptr) {
        this->root = right_child;
    } else if (node == node->parent->left) {
        node->parent->left = right_child;
    } else {
        node->parent->right = right_child;
    }

    right_child->left = node;
    node->parent = right_child;
}

void red_black_tree::right_rotate(Node*& node) {
    Node* left_child = node->left;
    node->left = left_child->right;

    if (left_child->right != nullptr) {
        left_child->right->parent = node;
    }

    left_child->parent = node->parent;

    if (node->parent == nullptr) {
        this->root = left_child;
    } else if (node == node->parent->left) {
        node->parent->left = left_child;
    } else {
        node->parent->right = left_child;
    }

    left_child->right = node;
    node->parent = left_child;
}


