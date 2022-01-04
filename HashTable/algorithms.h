#pragma once
#include "dataStructure.h"

int Search(HashTable* URL[], string url); 
void Insert(HashTable* URL[], string url); 
void InsertLink(HashTable* URL[], string local, string url);
void InsertURL(HashTable* URL[], string parent);
void CheckLink(HashTable* URL[]);
bool Delete(HashTable* URL[], string url);
void GoToWeb(HashTable* URL[]);
