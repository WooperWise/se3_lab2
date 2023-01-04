#include "BackpackItems.h"

Item::Item()
{
    weight = 0;
    cost = 0;
};

std::ostream& operator<<(std::ostream& os, const Item& item)
{
    return os << "Weight: " << item.GetWeight() << " ; Cost:  " << item.GetCost() << "\n";
}

std::ostream& operator<<(std::ostream& os, const Backpack& bag)
{
    std::cout << "Items:\n";
    bag.GetItems()->Print();
    return os << "Summary Weight: " << bag.GetW() << "\n"
        << "Summary Cost: " << bag.GetC() << '\n';
}

Item::Item(double w, double c)
{
    weight = w;
    cost = c;
};

Item::Item(const Item& item) {
    weight = item.weight;
    cost = item.cost;

};

Item::~Item() {};

double Item::GetWeight() const { return weight; };
double Item::GetCost() const { return cost; };

Item Item::operator=(const Item& item) {
    this->weight = item.weight;
    this->cost = item.cost;
    return *this;
};

bool Item::operator==(const Item& item) const {
    if ((this->cost == item.cost) && (this->weight == item.weight))
    {
        return 1;
    }
    else { return 0; }
};

bool Item::operator>(const Item& item) const {
    if ((this->cost / this->weight) > (item.cost / item.weight))
    {
        return true;
    }
    else { return false; }
};

bool Item::operator<(const Item& item) const {
    if ((this->cost / this->weight) < (item.cost / item.weight))
    {
        return true;
    }
    else { return false; }
};

bool Item::operator>=(const Item& item) const {
    if ((this->cost / this->weight) >= (item.cost / item.weight))
    {
        return true;
    }
    else { return false; }
};

bool Item::operator<=(const Item& item) const {
    if ((this->cost / this->weight) <= (item.cost / item.weight))
    {
        return true;
    }
    else { return false; }
};

bool Item::operator!=(const Item& item) const {
    if ((this->cost / this->weight) != (item.cost / item.weight))
    {
        return true;
    }
    else { return false; }
};

Backpack::Backpack(double W)
{
    bearingCapacity = W;
    items = new ArraySequence<Item>();
};

Backpack::Backpack(Sequence<Item>* seq, double W)
{
    items = seq;
    for (int i = 0; i < seq->GetLenght(); i++)
    {
        weight += seq->Get(i).GetWeight();
        cost += seq->Get(i).GetCost();
    }
    bearingCapacity = W;
}

Backpack::Backpack(Backpack& bag)
{
    items = bag.GetItems();
    bearingCapacity = bag.GetBC();
    weight = bag.GetW();
    cost = bag.GetC();
}

Backpack::~Backpack()
{
}

Sequence<Item>* Backpack::GetItems() const { return items; }

double Backpack::GetW() const { return weight; }

double Backpack::GetBC() const { return bearingCapacity; }

double Backpack::GetC() const { return cost; }

Backpack Backpack::operator=(const Backpack& bag) {
    this->items = bag.items;
    this->bearingCapacity = bag.bearingCapacity;
    this->weight = bag.weight;
    this->cost = bag.cost;
    return *this;
};

void Backpack::PushItem(Item* item)
{
    if (item == nullptr) { return; }
    items->Prepend(*item);
    weight += item->GetWeight();
    cost += item->GetCost();
};

