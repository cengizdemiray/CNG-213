#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

struct AvlTree{
    int weight;
    int height;
    struct FishData *fishStatistics;
    struct AvlTree *left;
    struct AvlTree *right;
};


struct AvlTree *createTree();
struct AvlTree *makeEmptyTree(struct AvlTree*);
struct AvlTree *putElement(int , struct FishData *, struct AvlTree *);
int HeightofTree(struct AvlTree *);
int max(int a, int b);
struct AvlTree * SingleRotateRight(struct AvlTree *);
struct AvlTree * SingleRotateLeft(struct AvlTree *);
struct AvlTree * doubleRotateRight(struct AvlTree *);
struct AvlTree *doubleRotateLeft(struct AvlTree *);
struct AvlTree *searchTree(int , struct AvlTree *);
struct FishList *createFishNode(struct AvlTree *);
struct FishList *concatenateLists(struct FishList *, struct FishList *);
