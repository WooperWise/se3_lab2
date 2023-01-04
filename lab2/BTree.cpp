#include "BTree.h"

struct NodeBTree
{
    int leaf;
    int numKeys;
    int keys[MAX_KEYS];
    struct NodeBTree* kids[MAX_KEYS + 1];
};

BTree BTreeCreate(void)
{
    BTree b = (BTree)malloc(sizeof(*b));
    assert(b);
    b->leaf = 1;
    b->numKeys = 0;
    return b;
}

void BTreeDestroy(BTree b)
{
    if (!b->leaf)
    {
        for (int i = 0; i < b->numKeys + 1; i++)
            BTreeDestroy(b->kids[i]);
    }
    free(b);
}

static int SearchKey(int n, const int* a, int key)
{
    int lo = -1, hi = n, mid = 0;
    while (lo + 1 < hi)
    {
        mid = (lo + hi) / 2;
        if (a[mid] == key)
            return mid;
        else if (a[mid] < key)
            lo = mid;
        else
            hi = mid;
    }
    return hi;
}

int BTreeSearch(BTree b, int key)
{
    int pos = SearchKey(b->numKeys, b->keys, key);
    if (b->numKeys == 0)
        return 0;
    if (pos < b->numKeys && b->keys[pos] == key)
        return 1;
    else
        return (!b->leaf && BTreeSearch(b->kids[pos], key));
}

static BTree BTreeInsertInternal(BTree b, int key, int* median)
{
    int pos = SearchKey(b->numKeys, b->keys, key), mid = 0;
    BTree b2;
    if (pos < b->numKeys && b->keys[pos] == key)
        return 0;
    if (b->leaf)
    {
        memmove(&b->keys[pos + 1], &b->keys[pos], sizeof(*(b->keys)) * (b->numKeys - pos));
        b->keys[pos] = key;
        b->numKeys++;
    }
    else
    {
        b2 = BTreeInsertInternal(b->kids[pos], key, &mid);
        if (b2)
        {
            memmove(&b->keys[pos + 1], &b->keys[pos], sizeof(*(b->keys)) * (b->numKeys - pos));
            memmove(&b->kids[pos + 2], &b->kids[pos + 1], sizeof(*(b->keys)) * (b->numKeys - pos));
            b->keys[pos] = mid;
            b->kids[pos + 1] = b2;
            b->numKeys++;
        }
    }
    if (b->numKeys >= MAX_KEYS)
    {
        mid = b->numKeys / 2;
        *median = b->keys[mid];
        b2 = (BTree)malloc(sizeof(*b2));
        b2->numKeys = b->numKeys - mid - 1;
        b2->leaf = b->leaf;
        memmove(b2->keys, &b->keys[mid + 1], sizeof(*(b->keys)) * b2->numKeys);
        if (!b->leaf)
            memmove(b2->kids, &b->kids[mid + 1], sizeof(*(b->kids)) * (b2->numKeys + 1));
        b->numKeys = mid;
        return b2;
    }
    else
        return 0;
}

void BTreeInsert(BTree b, int key)
{
    BTree b1;
    BTree b2;
    int median;
    b2 = BTreeInsertInternal(b, key, &median);
    if (b2)
    {
        b1 = (BTree)malloc(sizeof(*b1));
        assert(b1);
        memmove(b1, b, sizeof(*b));
        b->numKeys = 1;
        b->leaf = 0;
        b->keys[0] = median;
        b->kids[0] = b1;
        b->kids[1] = b2;
    }
}
