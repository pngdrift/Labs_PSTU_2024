#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <vector>

struct Node
{
    double data;
    Node *right;
    Node *left;

    Node(double key)
    {
        data = key;
        left = nullptr;
        right = nullptr;
    }
};

class Tree
{
  public:
    Tree();
    Node *rootNode;
    int isBalanced(Node *root);
    Node *addElement(double, Node *);
    Node *getMinNode(Node *node = nullptr);
    void inorder(Node *node, std::vector<double> &values);
    void makeBalance();
    void clear();

  private:
    void clear(Node *node);
    Node *balance(const std::vector<double> &values, int start, int end);
};

inline void Traverse(Node *n)
{
    if (n == nullptr)
    {
        return;
    }
    std::cout << n->data << std::endl;
    Traverse(n->left);
    Traverse(n->right);
}

#endif // TREE_H
