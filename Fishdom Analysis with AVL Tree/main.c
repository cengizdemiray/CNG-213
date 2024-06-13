#include <stdio.h>
#include <stdlib.h>
#include "avlTree.h"

struct AvlTree *readFile(char *);
struct AvlTree *insertFish(int, struct FishData *, struct AvlTree *);
void displayIndex(struct AvlTree *);
struct AvlTree *heaviestFish(struct AvlTree *);
struct FishList *makeList(struct AvlTree *);
struct FishList *longestFish(struct FishList *);
void displayMenu();

int main(int argc, char* argv[]) {
    struct FishList *list;
    int choice;
    struct AvlTree *node;
    struct FishList *longest;
    displayMenu();
    struct AvlTree *myFish = readFile(argv[1]); //for reading data from the file
    printf("Enter your option:");
    scanf("%d",&choice);
    while(choice!=4){
        if(choice==1){
            displayIndex(myFish);
        }
        else if(choice==2){
            node= heaviestFish(myFish);
            struct FishData *data =node->fishStatistics;
            while(data!=NULL){
                printf("%s %d %f %s %s\n",data->label,node->weight,data->length,data->date,data->city);
                data=data->next;
            }
        }
        else if(choice==3){
            list=NULL;
            list= makeList(myFish);
            longest= longestFish(list);
            printf("%s %d %f %s %s\n",longest->data->label,longest->weight,longest->data->length,longest->data->date,longest->data->city);
        }
        displayMenu();
        printf("Enter your option:");
        scanf("%d",&choice);
    }
    return 0;
}

struct AvlTree *readFile(char *filename) { //this function takes data from the file
    int weight;
    struct AvlTree *fishes;
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file stream");
        exit(EXIT_FAILURE);
    }

    fishes = createTree(); //creating tree
    fishes = makeEmptyTree(fishes); //initializing tree

    struct FishData *data; // structure for storing fish datas in it
    while ((data = (struct FishData *)malloc(sizeof(struct FishData))) != NULL &&
           fscanf(file, " %49[^,],%d,%f,%19[^,],%19[^\n]\n", data->label, &weight, &data->length, data->date, data->city) !=EOF) {
        data->next = NULL;
        fishes=insertFish(weight, data, fishes); //when one data is taken insert in to the AVL tree immediately
    }

    free(data); //after insert is done release data structure
    fclose(file);
    return fishes; //return the AVL tree
}
struct AvlTree *insertFish(int weight,struct FishData *data, struct AvlTree *t){
    struct AvlTree *result= searchTree(weight,t); //search tree is used for finding the same weight
    if(result!=NULL){ //if result is not full our data weight exist in the AVL tree already.
        struct FishData *tmp=result->fishStatistics;
        while(tmp->next!=NULL){
            tmp=tmp->next;
        }
        tmp->next=data;
    }

    else{ //if it is null this weight is not in the AVL tree so far, put this weight in the AVL tree.
        t=putElement(weight,data,t);

    }
    return t;
}
void displayIndex(struct AvlTree *t){ //we want to display weight in the ascending order, and my t is AVL tree, we should
    // go with the same order as inorder principle because smallest one is at left then parent, and right child is greater
    // than left and parent.
    if(t!=NULL){
        displayIndex(t->left);
        struct FishData *node=t->fishStatistics;
        while(node!=NULL){
            printf("%s %d %f %s %s\n",node->label,t->weight,node->length,node->date,node->city);
            node=node->next;
        }
        displayIndex(t->right);
    }
}
struct AvlTree *heaviestFish(struct AvlTree *t){ // t is the AVL tree that is arranged according to weights.
    // In the AVL tree greatest weight can be found at the rightmost node.
    // Complexity: O(logn) because every time we move number of nodes divides by 2 this change can be represented as a
    //logarithmic. I do not think there is a better way. It is most efficient case.
    struct AvlTree *tmp=t;
    while(tmp->right!=NULL){
        tmp=tmp->right;
    }
    return tmp;
}
struct FishList *makeList(struct AvlTree *t) { // this function is used for converting AVL tree to list.
    if (t == NULL) {
        return NULL;
    }
    struct AvlTree *tmp=t;
    struct FishList *leftList = makeList(tmp->left);
    struct FishList *nodeList = createFishNode(tmp);
    struct FishList *rightList = makeList(tmp->right);
    // Concatenate the three lists
    struct FishList *finalList = concatenateLists(leftList, nodeList);
    finalList = concatenateLists(finalList, rightList);
    return finalList;
}
struct FishList *longestFish(struct FishList *l){ // this function takes the list that we created above and find the node
    // with the maximum length
    // Complexity: I used list, we need to do search for the longest fish, if there are N fish, our complexity will be
    // O(n) for best and worst case as a best case complexity is O(1). This can be may improved by using stack.
    if(l==NULL){
        printf("Empty List !");
        exit(1);
    }
    struct FishList *tmp=l;
    struct FishList *current=l->next;
    while(current!=NULL){
        if(current->data->length>tmp->data->length){
            tmp=current;
        }
        current=current->next;
    }
    return tmp;
}
void displayMenu(){ // just for displaying menu
    printf("***********Welcome to Fishdom Analysis**********\n");
    printf("************************************************\n");
    printf("Menu\n");
    printf("1. Display the full index of fishdom.\n");
    printf("2. Display the heaviest fish.\n");
    printf("3. Display the longest fish.\n");
    printf("4. Exit\n");
}
