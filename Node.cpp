//
// Created by Илья on 028 28.10.19.
//
#include "Node.h"

Node::Node(int data){
    Data = data;
    Left = nullptr;
    Right = nullptr;
    Parent = nullptr;
    Color = RED;
}


void Node::RotateLeft(Node* n){
    Node* pivot = n->Right;
    pivot->Parent = n->Parent;
    if(n->Parent != nullptr){  // If n isn't root
        if(pivot->Parent->Left == n){
            pivot->Parent->Left = pivot;
        }
        else{
            pivot->Parent->Right = pivot;
        }
    }

    if(pivot->Left)
        pivot->Left->Parent = n;
    n->Right = pivot->Left;

    pivot->Left = n;
    n->Parent = pivot;
}


void Node::RotateRight(Node* n){
    Node* pivot = n->Left;
    pivot->Parent = n->Parent;
    if(n->Parent != nullptr){  // If n isn't root
        if(pivot->Parent->Left == n){
            pivot->Parent->Left = pivot;
        }
        else{
            pivot->Parent->Right = pivot;
        }
    }

    if(pivot->Right)
        pivot->Right->Parent = n;
    n->Left = pivot->Right;

    pivot->Right = n;
    n->Parent = pivot;
}


Node* Node::Grandparent(Node *n){
    if (n && n->Parent){
        return n->Parent->Parent;
    }
    else{
        return nullptr;
    }
}


Node* Node::Uncle(Node *n){
    Node* g = Grandparent(n);
    if (g){
        if (n->Parent == g->Left){
            return g->Right;
        }
        else{
            return g->Left;
        }
    }
    else{
        return nullptr;
    }
}


void Node::Insert(int val, Node** root, Node** parent){
    if (*root == nullptr){
        *root = new Node(val);
        if(parent)
            (*root)->Parent = *parent;
        InsertCase1(*root);
    }
    else {
        if (val > (*root)->Data){
            Insert(val, &((*root)->Right), root);
        }
        if (val <= (*root)->Data){
            Insert(val, &((*root)->Left), root);
        }
    }
}


void Node::InsertCase1(Node *n) {
    if (n->Parent == nullptr){
        n->Color = BLACK;
    }
    else{
        InsertCase2(n);
    }
}


void Node::InsertCase2(Node *n) {
    if (n->Parent->Color == BLACK){
        return;  // The tree is correct
    }
    else{
        InsertCase3(n);
    }
}


void Node::InsertCase3(Node *n) {
    Node* uncle = Uncle(n);
    if (uncle && uncle->Color == RED){
        n->Parent->Color = BLACK;
        uncle->Color = BLACK;
        uncle->Parent->Color = RED;
        InsertCase1(Grandparent(n));
    }
    else{
        InsertCase4(n);
    }
}


void Node::InsertCase4(Node *n) {
    Node* g = Grandparent(n);
    if( n == n->Parent->Right && g->Left == n->Parent){
        RotateLeft(n->Parent);
        n = n->Left;
    }
    else{
        if (n == n->Parent->Left && g->Right == n->Parent){
            RotateRight(n->Parent);
            n = n->Right;
        }
    }
    InsertCase5(n);
}


void Node::InsertCase5(Node *n) {
    Node* g = Grandparent(n);
    n->Parent->Color = BLACK;
    g->Color = RED;
    if (n == n->Parent->Left && n->Parent == g->Left){
        RotateRight(g);
    }
    else{
        RotateLeft(g);
    }
}


void Node::Remove(int val, Node**root){
    if (*root == nullptr){
        return;
    }
    else {
        if (val > (*root)->Data){
            Remove(val, &((*root)->Right));
        }
        if (val < (*root)->Data){
            Remove(val, &((*root)->Left));
        }
        if (val == (*root)->Data){
            if ((*root)->Left == nullptr && (*root)->Right == nullptr){
                if ((*root)->Parent->Left == (*root)){
                    (*root)->Parent->Left = nullptr;
                }
                else{
                    (*root)->Parent->Right = nullptr;
                }
                delete[] (*root);
                return;
            }
            if ((*root)->Left && (*root)->Right){
                if ((*root)->Right->Left == nullptr){
                    Node* right = (*root)->Right;
                    (*root)->Data = (*root)->Right->Data;
                    (*root)->Right = (*root)->Right->Right;
                    delete[] right;
                }
                else{
                    (*root)->Data = (*root)->Right->Left->Data;
                    Remove((*root)->Data, &((*root)->Right->Left));
                }
            }
            else{
                if((*root)->Right){
                    Node* right = (*root)->Right;
                    (*root)->Data = (*root)->Right->Data;
                    (*root)->Left = (*root)->Right->Left;
                    (*root)->Right = (*root)->Right->Right;
                    delete[] right;
                }
                if((*root)->Left){
                    Node* left = (*root)->Left;
                    (*root)->Data = (*root)->Left->Data;
                    (*root)->Right = (*root)->Left->Right;
                    (*root)->Left = (*root)->Left->Left;
                    delete[] left;
                }
            }
        }
    }
}


Node* Node::Sibling(Node *n) {
    if (n->Parent){  // If n isn't root
        if(n == n->Parent->Left){
            return n->Parent->Right;
        }
        else{
            return n->Parent->Left;
        }
    }
    return nullptr;
}


void Node::ReplaceNode(Node* n, Node* child){
    child->Parent = n->Parent;
    if (n->Parent->Left == n){
        n->Parent->Left = child;
    }
    else{
        n->Parent->Right = child;
    }
}

void Node::DeleteOneChild(Node *n) {
    Node* child = n->Left == nullptr ? n->Right : n->Left;
    ReplaceNode(n, child);
    if(n->Color == BLACK){
        if (child->Color == RED)
            child->Color = BLACK;
        else
            DeleteCase1(child);
    }
    delete[] n;
}

void Node::DeleteCase1(Node *n) {

}
