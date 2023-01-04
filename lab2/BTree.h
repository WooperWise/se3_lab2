#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX_KEYS (1024)

typedef struct NodeBTree* BTree;

BTree BTreeCreate(void);

void BTreeDestroy(BTree t);

int BTreeSearch(BTree t, int key);

void BTreeInsert(BTree t, int key);

