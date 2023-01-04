#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include "ISortedSequence.h"
#include "BackpackItems.h"

using namespace std;

class NTreeForBag
{
private:
    struct Node
    {
        Item data;
        std::vector<Node*> node;
        Node* rootNode;
        double sumWeight = 0;
        double sumCost = 0;
        size_t offSet;
    };

    Node self;
public:
    NTreeForBag();
    NTreeForBag(NTreeForBag& tree);
    ~NTreeForBag();
    void DestroyNode(Node* root);
    Item GetData() const;
    Node* GetPtrRoot();
    void TreeBag(Sequence<Item>* data, Backpack* bag);
    std::vector<Node*> PushNode(Sequence<Item>* data, Node* node, double W);
};
