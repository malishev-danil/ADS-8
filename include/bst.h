// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>

template <typename T>
class BST {
 private:
    struct Node {
        T data;
        int count;
        Node* left;
        Node* right;

        explicit Node(const T& data)
            : data(data), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insertInternal(Node*& node, const T& data);
    void freeSubtree(Node* node);
    const Node* findNode(const Node* node, const T& value) const;
    void inOrderTraversal(const Node* node,
        std::vector<std::pair<T, int>>& frequencies) const;

 public:
    BST() : root(nullptr) {}
    ~BST();

    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    void insert(const T& data);
    int depth() const;
    int search(const T& value) const;
    void printInOrder() const;
    std::vector<std::pair<T, int>> getFrequencies() const;
};


template <typename T>
BST<T>::~BST() {
    freeSubtree(root);
}

template <typename T>
void BST<T>::freeSubtree(Node* node) {
    if (node) {
        freeSubtree(node->left);
        freeSubtree(node->right);
        delete node;
    }
}

template <typename T>
void BST<T>::insert(const T& data) {
    insertInternal(root, data);
}

template <typename T>
void BST<T>::insertInternal(Node*& node, const T& data) {
    if (!node) {
        node = new Node(data);
        return;
    }

    if (data < node->data) {
        insertInternal(node->left, data);
    } else if (data > node->data) {
        insertInternal(node->right, data);
    } else {
        node->count++;
    }
}

template <typename T>
int BST<T>::depth() const {
    if (!root) return -1;

    auto calculateDepth = [](const Node* node, auto&& self) -> int {
        if (!node) return 0;
        return 1 + std::max(self(node->left, self),
            self(node->right, self));
        };

    return calculateDepth(root, calculateDepth) - 1;
}

template <typename T>
int BST<T>::search(const T& value) const {
    const Node* result = findNode(root, value);
    return result ? result->count : 0;
}

template <typename T>
const typename BST<T>::Node* BST<T>::findNode(const Node* node, const T& value) const {
    if (!node) return nullptr;

    if (value == node->data) {
        return node;
    } else if (value < node->data) {
        return findNode(node->left, value);
    } else {
        return findNode(node->right, value);
    }
}

template <typename T>
std::vector<std::pair<T, int>> BST<T>::getFrequencies() const {
    std::vector<std::pair<T, int>> frequencies;
    inOrderTraversal(root, frequencies);
    return frequencies;
}

template <typename T>
void BST<T>::inOrderTraversal(const Node* node,
    std::vector<std::pair<T, int>>& frequencies) const {
    if (node) {
        inOrderTraversal(node->left, frequencies);
        frequencies.emplace_back(node->data, node->count);
        inOrderTraversal(node->right, frequencies);
    }
}

template <typename T>
void BST<T>::printInOrder() const {
    auto frequencies = getFrequencies();
    for (const auto& [data, count] : frequencies) {
        std::cout << data << " (" << count << ")\n";
    }
}

#endif  // INCLUDE_BST_H_
