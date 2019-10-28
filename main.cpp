#include <iostream>
#include "Node.h"
int main() {
    Node* root = nullptr;
    Node::Insert(13, &root, nullptr);
    Node::Insert(8, &root, nullptr);
    Node::Insert(17, &root, nullptr);
    Node::Insert(1, &root, nullptr);
    Node::Insert(11, &root, nullptr);
    Node::Insert(15, &root, nullptr);
    Node::Insert(25, &root, nullptr);
    Node::Insert(6, &root, nullptr);
    Node::Insert(22, &root, nullptr);
    Node::Insert(27, &root, nullptr);
    return 0;
}