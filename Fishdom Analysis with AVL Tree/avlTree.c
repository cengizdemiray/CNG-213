//
// Created by excalıbur-pc on 25.12.2023.
//
#include "avlTree.h"
struct AvlTree *createTree(){
    return NULL;
}
struct AvlTree *makeEmptyTree(struct AvlTree *t){
    if(t!=NULL){
        makeEmptyTree(t->left);
        makeEmptyTree(t->right);
        free(t);
    }
    return NULL;
}
struct AvlTree *putElement(int weight, struct FishData *data, struct AvlTree *t){
    if(t==NULL){ //if t is null create the node and put the values in this node.
        t=(struct AvlTree *)malloc(sizeof(struct AvlTree));
        t->weight=weight;
        t->right=NULL;
        t->left=NULL;
        t->height=0;
        t->fishStatistics=data;
    }
    else if(weight>t->weight){ //if given weight is more than current node go to right subtree of AVL tree.
        t->right= putElement(weight,data,t->right);
        // after inserting element in proper location AVL tree should be controlled for rebalancing.
        // if differences of subtrees are different from them, AVL tree need rotation
        if(HeightofTree(t->right)- HeightofTree(t->left)!=1 && HeightofTree(t->right)- HeightofTree(t->left)!=0 && HeightofTree(t->right)- HeightofTree(t->left)!=-1){
           if(weight<t->right->weight){ //this means RL rotation
               t=doubleRotateRight(t);
           }
           else
               t=SingleRotateLeft(t); // RR rotation
        }
    }
    else if(weight<t->weight){
        t->left= putElement(weight,data,t->left);
        if(HeightofTree(t->right)- HeightofTree(t->left)!=1 && HeightofTree(t->right)- HeightofTree(t->left)!=0 && HeightofTree(t->right)- HeightofTree(t->left)!=-1 ){
            if(weight<t->left->weight)
                t=SingleRotateRight(t); // LL rotation
            else
                t=doubleRotateLeft(t); //LR rotation
        }
    }
    t->height=max(HeightofTree(t->left), HeightofTree(t->right))+1; //updating height
    return t;
}
int HeightofTree(struct AvlTree *t){
    if(t==NULL)
        return -1;
    else
        return t->height;
}
struct AvlTree *SingleRotateRight(struct AvlTree *b2) { //done by looking the presentation in the slides
    struct AvlTree *b1 = b2->left;
    struct AvlTree *a = b1->right;
    b1->right = b2;
    b2->left = a;
    b2->height = max(HeightofTree(b2->left), HeightofTree(b2->right)) + 1;
    b1->height = max(HeightofTree(b1->left), HeightofTree(b1->right)) + 1;
    return b1; // return the uptaded root
}

struct AvlTree *SingleRotateLeft(struct AvlTree *b1) { // done by looking at the slides
    struct AvlTree *b2 = b1->right;
    struct AvlTree *a = b2->left;
    b2->left = b1;
    b1->right = a;
    b1->height = max(HeightofTree(b1->left), HeightofTree(b1->right)) + 1;
    b2->height = max(HeightofTree(b2->left), HeightofTree(b2->right)) + 1;
    return b2;
}

struct AvlTree *doubleRotateLeft(struct AvlTree *t) { // done by looking at the slides
    t->left = SingleRotateLeft(t->left);
    return SingleRotateRight(t);
}

struct AvlTree *doubleRotateRight(struct AvlTree *t) { // done by looking at the slides
    t->right = SingleRotateRight(t->right);
    return SingleRotateLeft(t);
}

int max(int a,int b){ // this function finds greater number among two numbers.
    if(a>b)
        return a;
    else if(b>a)
        return b;
}
struct AvlTree *searchTree(int weight, struct AvlTree *t) { //this function searchs according to weight if it exist same
    //weight, returns that node, if it does not exist return null.
    if (t == NULL)
        return NULL;
    if (weight == t->weight)
        return t;
    else if (weight < t->weight)
        return searchTree(weight, t->left);
    else
        return searchTree(weight, t->right);
}
struct FishList *createFishNode(struct AvlTree *data) { //this function is used for creating node to list when we are
    //converting tree to list.
    struct FishList *node = (struct FishList *)malloc(sizeof(struct FishList));
    if (node != NULL) {
        node->weight = data->weight;
        node->data = (struct FishData *)malloc(sizeof(struct FishData));
        struct FishData *currentFishData = data->fishStatistics;
        while (currentFishData != NULL) { //this loop used for selecting the greater length as a node in the list
            // when there are more than one fish with the same weight
            strcpy(node->data->label ,currentFishData->label);
            node->data->length = currentFishData->length;
            strcpy(node->data->date , currentFishData->date);
            strcpy(node->data->city , currentFishData->city);
            node->next = NULL;
            if (currentFishData->length > node->data->length) {
                node->data = currentFishData;
            }
            currentFishData = currentFishData->next;
        }
    }
    return node;
}


// Function to concatenate two FishLists
struct FishList *concatenateLists(struct FishList *list1, struct FishList *list2) {
    if (list1 == NULL) {
        return list2;
    }

    struct FishList *current = list1;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = list2;
    return list1;
}



