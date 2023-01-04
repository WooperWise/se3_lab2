#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "ISortedSequence.h"

using namespace std;

template <class T>
class BinaryTree {
private:

    struct Node {
    public:
        T data;
        Node* left;
        Node* right;
    };

    Node* root;
    size_t size;

    void TreeToString(Node* item, string* res)
    {
        if (item != nullptr)
        {
            *res += to_string(item->data) + " ";
            TreeToString(item->left, res);
            TreeToString(item->right, res);
        }
    }

    void TreeDestroy(Node* item)
    {
        if ((item != nullptr) && (item->left != nullptr) && (item->right != nullptr))
        {
            TreeDestroy(item->left);
            TreeDestroy(item->right);
            delete item;
        }
    }

    Node* FindNode(T item) {
        if (root->data == item)
            return root;
        return FindForNode(root, item);
    }

    Node* FindForNode(Node* node, T item) const
    {
        if (node == nullptr)
            return nullptr;
        if (item < node->data)
            return FindForNode(node->left, item);
        else if (item > node->data)
            return FindForNode(node->right, item);
        else
            return node;
    }

    void map(Node* item, int (*pt2Func1)(int))
    {
        if (item != nullptr)
        {
            item->data = (*pt2Func1)(item->data);
            map(item->left, pt2Func1);
            map(item->right, pt2Func1);
        }
    }

    void where(BinaryTree<T> tree, Node* item, bool (*pt2Func2)(int)) {
        if (item != nullptr)
        {
            if ((*pt2Func2)(item->data))
                tree.Insert(item->data);
            where(tree, item->left, pt2Func2);
            where(tree, item->right, pt2Func2);
        }
    }
public:
    BinaryTree(T key)
    {
        root = new Node;
        root->data = key;
        root->left = nullptr;
        root->right = nullptr;
        size = 1;
    }

    BinaryTree(string s)
    {
        s += '.';
        string tmp;
        vector <string> vs;
        for (int i = 0; i < s.length(); i++)
            if ((s[i] == ' ') || (s[i] == '.'))
            {
                vs.push_back(tmp);
                tmp.clear();
            }
            else
                tmp += s[i];
        root = new Node;
        root->data = stoi(vs[0]);
        root->left = nullptr;
        root->right = nullptr;
        size = 1;
        for (auto k : vs)
            Insert(stoi(k));
    }

    BinaryTree(T* arr, int count)
    {
        root = new Node;
        root->data = arr[0];
        root->left = nullptr;
        root->right = nullptr;
        size = 1;
        for (int i = 1; i < count; i++)
            Insert(arr[i]);
    }

    BinaryTree(Sequence<T>* arr)
    {
        root = new Node;
        root->data = arr->Get(0);
        root->left = nullptr;
        root->right = nullptr;
        size = 1;
        for (int i = 1; i < arr->GetLenght(); i++)
            Insert(arr->Get(i));
    }

    ~BinaryTree() { TreeDestroy(root); }

    Node* GetRoot() { return root; }

    BinaryTree<T> GetSubTree(T item)
    {
        Node* node = FindNode(item);

        BinaryTree<T> newTree(1);
        newTree.root = node;

        return newTree;
    }

    void map(int (*pt2Func1)(int)) { map(root, pt2Func1); }

    BinaryTree<T> where(BinaryTree<T> tree, bool (*pt2Func)(int))
    {
        where(tree, root, pt2Func);
        return tree;
    }

    void Insert(T key)
    {

        Node* node = root;
        while ((node != nullptr) && (node->data != key))
        {
            if ((node->data > key) && (node->left == nullptr))
            {
                node->left = new Node;
                node->left->data = key;
                node->left->left = nullptr;
                node->left->right = nullptr;
                ++size;
                return;
            }
            if ((node->data < key) && (node->right == nullptr))
            {
                node->right = new Node;
                node->right->data = key;
                node->right->left = nullptr;
                node->right->right = nullptr;
                ++size;
                return;
            }
            if (node->data > key)
                node = node->left;
            else
                node = node->right;
        }
    }

    void Erase(T key) {
        Node* node = root;
        Node* parent = nullptr;
        while ((node != nullptr) && (node->data != key))
        {
            parent = node;
            if (node->data > key)
                node = node->left;
            else
                node = node->right;
        }
        if (node == nullptr)
            return;
        if (node->left == nullptr)
        {
            if ((parent != nullptr) && (parent->left == node))
                parent->left = node->right;
            if ((parent != nullptr) && (parent->right == node))
                parent->right = node->right;
            --size;
            delete node;
            return;
        }
        if (node->right == nullptr)
        {
            if ((parent != nullptr) && (parent->left == node))
                parent->left = node->left;
            if ((parent != nullptr) && (parent->right == node))
                parent->right = node->left;
            --size;
            delete node;
            return;
        }
        Node* replace = node->right;
        while (replace->left)
            replace = replace->left;
        T replace_data = replace->data;
        Erase(replace_data);
        node->data = replace_data;
    }

    int GetSize() const { return this->size; }

    string SaveTreeToString()
    {
        string result = "";
        TreeToString(root, &result);
        return result;
    }

    bool IsTreeEntry(BinaryTree<T> tree)
    {
        return (SaveTreeToString(1).Find(tree.SaveTreeToString(1)) != std::string::npos);
    }

    bool Find(T key)
    {
        Node* node = root;
        while ((node != nullptr) && (node->data != key))
        {
            if (node->data > key)
                node = node->left;
            else
                node = node->right;
        }
        return (node != nullptr);
    }

    static bool Equals(Node* t1, Node* t2)
    {
        if (t1 == t2)
            return true;
        if ((t1 == nullptr) || (t2 == nullptr))
            return false;
        return ((t1->data == t2->data) && Equals(t1->left, t2->left) && Equals(t1->right, t2->right));
    }

    void PrettyPrint(Node* node, string const& rpref = "", string const& cpref = "", string const& lpref = "")
    {
        if (!node)
            return;
        if (node->right)
            PrettyPrint(node->right, rpref + "  ", rpref + "/-", rpref + "| ");
        cout << cpref << node->data << std::endl;
        if (node->left)
            PrettyPrint(node->left, lpref + "| ", lpref + "\\-", lpref + "  ");
    }
};

