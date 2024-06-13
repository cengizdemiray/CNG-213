

#include<stdlib.h>

struct FishData{
    char label[50];
    float length;
    char date[50];
    char city[50];
    struct FishData *next;
};
struct FishList{
    int weight;
    struct FishData *data;
    struct FishList *next;
};



