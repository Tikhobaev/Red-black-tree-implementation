//
// Created by Илья on 024 24.10.19.
//

#ifndef RED_BLACK_TREE_NODE_H
#define RED_BLACK_TREE_NODE_H

enum NodeColor{ RED, BLACK };

class Node {
public:
    int Data;
    NodeColor Color;
    Node* Left;
    Node* Right;
    Node* Parent;
    Node(int);
    static void Insert(int, Node**, Node**);
    static void Remove(int, Node**);
private:
    static void InsertCase1(Node* n);
    static void InsertCase2(Node* n);
    static void InsertCase3(Node* n);
    static void InsertCase4(Node* n);
    static void InsertCase5(Node* n);
    static void RotateLeft(Node* n);
    static void RotateRight(Node* n);
    static Node* Grandparent(Node* n);
    static Node* Uncle(Node* n);
    static Node* Sibling(Node* n);
    static void ReplaceNode(Node* n, Node* child);
    static void DeleteOneChild(Node* n);
    static void DeleteCase1(Node* n);
    static void DeleteCase2(Node* n);
    static void DeleteCase3(Node* n);
    static void DeleteCase4(Node* n);
    static void DeleteCase5(Node* n);
    static void DeleteCase6(Node* n);
};

#endif //RED_BLACK_TREE_NODE_H
