#pragma once

#include <iostream>
#include "ISortedSequence.h"
#include "ArraySequence.h"


class Item
{
private:
    double weight;
    double cost;
public:
    Item();
    Item(double w, double c);
    Item(const Item& item);
    ~Item();
    double GetWeight() const;
    double GetCost() const;
    Item operator=(const Item& item);
    bool operator==(const Item& item) const;
    bool operator>(const Item& item) const;
    bool operator<(const Item& item) const;
    bool operator>=(const Item& item) const;
    bool operator<=(const Item& item) const;
    bool operator!=(const Item& item) const;
};

std::ostream& operator<<(std::ostream& os, const Item& item);


class Backpack
{
private:
    Sequence<Item>* items = nullptr;
    double weight = 0;
    double bearingCapacity = 0;
    double cost = 0;
public:
    Backpack(double W);
    Backpack(Sequence<Item>* seq, double W);
    Backpack(Backpack& bag);
    ~Backpack();
    Sequence<Item>* GetItems() const;
    double GetW() const;
    double GetBC() const;
    double GetC() const;
    Backpack operator=(const Backpack& bag);
    void PushItem(Item* item);
};

std::ostream& operator<<(std::ostream& os, const Backpack& bag);
