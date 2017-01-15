#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <string>

using namespace std;
struct Node{
    string str;
    Node* left;
    Node* right;
};
class AVL
{
    public:
        AVL();
        virtual ~AVL();
        void insert(string str);
        void Preorder();
        bool checkBalance(Node* cur);
        bool search(string str);
        void findSimilar(string prefix,string&result);
    private:
        void rotateRight(Node* &node);
        void rotateLeft(Node* &node);
        Node* root;
};

#endif // AVL_H
