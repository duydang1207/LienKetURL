#pragma once
#include "header.h"
const int  HASHTABLESIZE = 29;

struct Node {
    Node* next = nullptr;
    int index = -1;
};
struct HashTable
{
    bool check = false;
    string key = "";
    Node* headNext = nullptr;
    int prev = -1;
};

int HashFunction(string url);
int CollisionResolutionInsert(HashTable* URL[], int hashValue);


