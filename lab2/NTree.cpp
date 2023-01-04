#include "NTree.h"

NTreeForBag::NTreeForBag(NTreeForBag& tree) { self = tree.self; };

NTreeForBag::~NTreeForBag()
{
    DestroyNode(&self);
    if (self.node.size() > 0) { delete self.node[0]; };
};

void NTreeForBag::DestroyNode(Node* root) {
    if (root->node.size() != 0) {
        for (auto k : root->node)
        {
            DestroyNode(k);
            if (root != nullptr) delete root;
        }
    }
}

Item NTreeForBag::GetData() const {
    return self.data;
};

NTreeForBag::Node* NTreeForBag::GetPtrRoot() {
    return self.rootNode;
};

void NTreeForBag::TreeBag(Sequence<Item>* data, Backpack* bag)
{
    if (data == nullptr) return;
    for (int i = 0; i < data->GetLenght(); i++) {
        if (data->Get(i).GetWeight() <= bag->GetBC())
        {
            self.rootNode = nullptr;
            self.data = data->Get(i);
            self.offSet = i;
            self.sumCost = data->Get(i).GetCost();
            self.sumWeight = data->Get(i).GetWeight();
            break;
        }
        else if (i == data->GetLenght() - 1)
        {
            return;
        }
    }

    int flag = 1;
    std::vector<Node*> currentLevel;
    currentLevel.push_back(&self);
    std::vector<Node*> nextLevel;
    std::vector<Node*> ansArr;

    while (flag != 0)
    {
        for (auto i : currentLevel)
        {
            auto tmp = PushNode(data, i, bag->GetBC());

            if (tmp.empty())
            {
                ansArr.push_back(i);
            }
            else
            {
                for (auto j : tmp)
                {
                    nextLevel.push_back(j);
                }
            }

        }
        if (nextLevel.empty())
        {
            flag = 0;
        }

        currentLevel.clear();
        currentLevel = nextLevel;
        nextLevel.clear();
    }

    Node* ansNode = ansArr[0];

    for (auto k : ansArr)
    {
        if (ansNode->sumCost <= k->sumCost)
        {
            ansNode = k;
        };
    }

    while (true)
    {
        if (ansNode->rootNode != nullptr)
        {
            bag->PushItem(&(ansNode->data));
            ansNode = ansNode->rootNode;
        }
        else
        {
            bag->PushItem(&(self.data));
            break;
        }
    }
}

std::vector<NTreeForBag::Node*> NTreeForBag::PushNode(Sequence<Item>* data, NTreeForBag::Node* node, double W)
{
    std::vector<Node*> ansVector;
    if (node->offSet == data->GetLenght() - 1) { return ansVector; };
    for (int i = node->offSet + 1; i < data->GetLenght(); i++)
    {
        Node* tmp = new Node;
        tmp->data = data->Get(i);
        tmp->offSet = i;
        tmp->sumWeight = node->sumWeight + data->Get(i).GetWeight();
        tmp->sumCost = node->sumCost + data->Get(i).GetCost();
        tmp->rootNode = node;
        if (tmp->sumWeight <= W) { ansVector.push_back(tmp); }
        else { delete tmp; }
    }
    return ansVector;
}

NTreeForBag::NTreeForBag() { };
