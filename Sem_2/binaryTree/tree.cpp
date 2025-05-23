#include "tree.h"

Tree::Tree()
{
    rootNode = nullptr;
}

int Tree::isBalanced(Node *root)
{
    if (!root)
    {
        return 0;
    }
    int leftSubtreeH = isBalanced(root->left);
    int rightSubtreeH = isBalanced(root->right);
    if (leftSubtreeH == -1 || rightSubtreeH == -1 || std::abs(leftSubtreeH - rightSubtreeH) > 1)
    {
        return -1;
    }
    return 1 + std::max(leftSubtreeH, rightSubtreeH);
}

Node *Tree::addElement(double value, Node *node)
{
    if (node == nullptr)
    {
        node = new Node(value);
        if (rootNode == nullptr)
        {
            rootNode = node;
        }
    }
    else if (node->data < value)
    {
        node->right = addElement(value, node->right);
    }
    else if (node->data > value)
    {
        node->left = addElement(value, node->left);
    }
    return node;
}

Node *Tree::getMinNode(Node *node)
{
    if (node == nullptr)
    {
        node = rootNode;
    }
    if (node->left == nullptr)
    {
        return node;
    }
    else
    {
        return getMinNode(node->left);
    }
}

void Tree::inorder(Node *node, std::vector<double> &values)
{
    if (node == nullptr)
    {
        return;
    }
    inorder(node->left, values);
    values.push_back(node->data);
    inorder(node->right, values);
}

Node *Tree::balance(const std::vector<double> &values, int start, int end)
{
    if (start > end)
    {
        return nullptr;
    }
    int mid = (start + end) / 2;
    Node *node = new Node(values[mid]);
    node->left = balance(values, start, mid - 1);
    node->right = balance(values, mid + 1, end);
    return node;
}

void Tree::makeBalance()
{
    std::vector<double> values;
    inorder(rootNode, values);
    rootNode = balance(values, 0, values.size() - 1);
}

void Tree::clear(Node *node)
{
    if (node == nullptr)
    {
        return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
}

void Tree::clear()
{
    clear(rootNode);
    rootNode = nullptr;
}
