//! Cengiz Demiray
//! 2526960
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//! structure for the datas of fish
struct Fishdata{
    int weight;
    float verticallength;
    float diagonallength;
    float crosslength;
    float height;
    float fishlength;
    int day;
    int month;
    int year;
    char city[50];
    struct Fishdata *next;

};
//! Structure for the fish species
struct Species{
    char name[40];
    struct Species *nextbottom;
    struct Fishdata *nextright;
};
struct List{ //! structure for the linked list
    struct Species *head;
    struct Species *tail;
    int size;
};
struct List *createlist(struct List*);
void makeempty(struct List *);
struct List *initializeFishing(const char *);
struct Species *search(struct List *,char []);
void addFishData(struct List *);
void addNewSpecies(struct List *);
void deleteFish(struct List *,int);
void printStatistics(struct List *);
void searchFishData(struct List *);
void saveUptadedList(struct List *);
int main() {
    FILE *infile;
    int option,treshold,end=0;
    infile=fopen("fishingArchive.txt","r"); //! open file stream for reading fishingArchive.txt
    if(infile==NULL){
        printf("File cannot be opened");
        exit(1);
    }
    struct List *myList=initializeFishing(infile); //! function call for stroing datas in the file to the program as a variable;
    printf("The fishingArchive.txt file has been loaded successfully!\n");
    while (!end){
        printf("\n------MENU--------------\n");
        printf("1. Add Fish Data\n");
        printf("2. Delete Fish Data\n");
        printf("3. Print Fish Statistics\n");
        printf("4. Search Fish Data\n");
        printf("5. Add Species List\n");
        printf("6. Exit\n");
        printf("Enter your option:");
        scanf("%d",&option);
        if(option==1){
            addFishData(myList);
        }
        if(option==2){
            deleteFish(myList,treshold);
        }
        if(option==3){
            printStatistics(myList);
        }
        if(option==4){
            searchFishData(myList);
        }
        if(option==5){
            addNewSpecies(myList);
        }
        if(option==6){
            saveUptadedList(myList);
            end=1;
        }
    }
    return 0;
}
struct List *createlist(struct List* myList){


    myList=(struct List *)malloc(sizeof(struct List));
    if(myList==NULL){
        printf("Out of memory!");
        exit(1);
    }
    else{
        makeempty(myList);
    }
    return myList;
}

void makeempty(struct List *myList){
    myList->head=(struct Species *)malloc(sizeof(struct Species));
    if(myList->head==NULL){
        printf("Out of memory!");
        exit(1);
    }
    else{
        myList->head->nextright=NULL;
        myList->head->nextbottom=NULL;
        myList->tail=myList->head;
        myList->size=0;
    }
}
int islempty(struct List *myList){
    if(myList->size==0){
        return 1;
    }
    return 0;
}
struct Species *search(struct List *list,char name[]){
    if(list->size==0){
        printf("The list is empty!");
    }
    else{
        struct Species *tmp=list->head->nextbottom;
        while(tmp!=NULL) {
            if (strcmp(tmp->name, name) == 0) {
                return tmp;
            }
            tmp=tmp->nextbottom;
        }
        return NULL;
    }
}
struct List *initializeFishing(const char *infile){
    struct List *tmp; //! this tmp list used to store file datas into it.
    tmp = createlist(tmp); //! allocation for tmp variable;
    char name[50],city[50];
    int weight,day,month,year;
    float verticallength,diagonallength,crosslength,height,fishlength;
    if(tmp->size==0){ //!if the list is empty at first.
        struct Species *newnode; //! we set the first line datas in the file to that structure and using that link the list.
        newnode=(struct Species*)malloc(sizeof(struct Species)); //! allocation of structure
        if(newnode==NULL){
            printf("Out of memory!");
            exit(1);
        }
        //! here only the first line is read.
        fscanf(infile,"%[^;];%d;%f;%f;%f;%f;%f;%d/%d/%d;%[^\n]\n",name,&weight,&verticallength,&diagonallength,&crosslength,&height,&fishlength,&day,&month,&year,city);
        newnode->nextright=(struct Fishdata *)malloc(sizeof(struct Fishdata));
        //! newnode->nextright structure that stores information of the fish, therefore it needs also allocation.
        strcpy(newnode->name,name); //! the variables of newnode structure is assigned from 147 to 159
        newnode->nextright->weight=weight;
        newnode->nextright->verticallength=verticallength;
        newnode->nextright->diagonallength=diagonallength;
        newnode->nextright->crosslength=crosslength;
        newnode->nextright->height=height;
        newnode->nextright->fishlength=fishlength;
        newnode->nextright->day=day;
        newnode->nextright->month=month;
        newnode->nextright->year=year;
        strcpy(newnode->nextright->city,city);
        newnode->nextright->next=NULL;
        newnode->nextbottom=NULL;
        tmp->head->nextbottom=newnode; //! because this is first line and our list are empty set the first node to
        //! head->nextbottom (with dummy node, head is dummy node here.)
        tmp->tail=tmp->head->nextbottom; //! because this is the first node, last and first node should be equal.
        tmp->size++; //! adding a node to linked list increases size
    }if(tmp->size!=0){ //! if the list is not empty anymore. (After reading first line).
        //!this while used for taking the rest of datas line by line.
        while(fscanf(infile,"%[^;];%d;%f;%f;%f;%f;%f;%d/%d/%d;%[^\n]\n",name,&weight,&verticallength,&diagonallength,&crosslength,&height,&fishlength,&day,&month,&year,city)!=EOF){
            struct Species *newnode; //! this node is for taking datas in the file and insert this node into the list, then,
            //! content of the newnode uptaded with next line.
            newnode=(struct Species*)malloc(sizeof(struct Species)); //! allocation for structure
            if(newnode==NULL){
                printf("Out of memory!");
                exit(1);
            }
            newnode->nextright=(struct Fishdata *)malloc(sizeof(struct Fishdata));
            //! again newnode->nextright is another structure that holds the fish data therefore it needs allocation to.
            if(search(tmp,name)==NULL){
            //! return NULL value means in the file there are not any same species.
            //! from 181 to 193 is for assigning value of newnode structure.
                strcpy(newnode->name,name);
                newnode->nextright->weight=weight;
                newnode->nextright->verticallength=verticallength;
                newnode->nextright->diagonallength=diagonallength;
                newnode->nextright->crosslength=crosslength;
                newnode->nextright->height=height;
                newnode->nextright->fishlength=fishlength;
                newnode->nextright->day=day;
                newnode->nextright->month=month;
                newnode->nextright->year=year;
                strcpy(newnode->nextright->city,city);
                newnode->nextright->next=NULL;
                newnode->nextbottom=NULL;
                tmp->tail->nextbottom=newnode; //! if this specie is different from others in the file we need to add this
                //! node as a new species, thats why nextbottom is used.
                tmp->tail=newnode; //! uptaded tail is our newnode.
                tmp->size++; //! again when we are enter the data in the linked list size increases.
            }
             else{ //! if species in the current line in the file with any other species in the list enter this block.
                struct Species *tmp2= search(tmp,name); //! for taking specie that is the same in the list, then assigned
                //! another called tmp2 list.
                //! when there is common specie name is not needed only fish data of that specie is needed thats why
                //! fish data structure allocated.
                struct Fishdata *newdata=(struct Fishdata *)malloc(sizeof(struct Fishdata));
                if(newdata==NULL){
                    printf("Out of memory.");
                    exit(1);
                }
                //! from 211-221 assigning values of newdata structure
                newdata->weight=weight;
                newdata->verticallength=verticallength;
                newdata->diagonallength=diagonallength;
                newdata->crosslength=crosslength;
                newdata->height=height;
                newdata->fishlength=fishlength;
                newdata->day=day;
                newdata->month=month;
                newdata->year=year;
                strcpy(newdata->city,city);
                newdata->next=NULL;
                //! we kept the fish species in the list that are same with the current species in the file.
                struct Fishdata *tmp3=tmp2->nextright;
                while(tmp3->next!=NULL){ //! this while loop is determining where we should place this data fish in the specie.
                    tmp3=tmp3->next;
                }
                tmp3->next=newdata; //! if we are in the last fish data structure set next to newnode
                tmp->size++;
             }
        }
    }
    return tmp; //! at the last, I need to return all list that is read from the file.
}
void addFishData(struct List *myList){ //! this function is used to adding new fish data to existing species
    struct Species *newnode;
    newnode=(struct Species*)malloc(sizeof(struct Species));
    char name[50],city[50];
    int weight,day,month,year;
    float verticallength,diagonallength,crosslength,height,fishlength;
    printf("Species:");
    scanf("%s",name);
    if(search(myList,name)==NULL){ //! this block calls the another function to add entirely different spaces.
        printf("This species does not exist.You need to create this species.Enter species again\n");
        addNewSpecies(myList);
    }
    else { //! if entered name exits in the list assign new value to the nextright pointer of this specie.
        //! from 249-264 is used for taking input from user.
        printf("Weight of the fish in grams:");
        scanf("%d", &weight);
        printf("Vertical length in CM:");
        scanf("%f", &verticallength);
        printf("Diagonal length in CM:");
        scanf("%f", &diagonallength);
        printf("Cross length in CM:");
        scanf("%f", &crosslength);
        printf("Height in CM:");
        scanf("%f", &height);
        printf("Fish length in CM:");
        scanf("%f", &fishlength);
        printf("Fishing Date:");
        scanf("%d/%d/%d",&day,&month,&year);
        printf("City:");
        scanf("%s", city);
        strcpy(newnode->name, name);
        //! from 267-279 assiging new values of the newnode struct
        newnode->nextright = (struct Fishdata *) malloc(sizeof(struct Fishdata));
        newnode->nextright->weight = weight;
        newnode->nextright->verticallength = verticallength;
        newnode->nextright->diagonallength = diagonallength;
        newnode->nextright->crosslength = crosslength;
        newnode->nextright->height = height;
        newnode->nextright->fishlength = fishlength;
        newnode->nextright->day=day;
        newnode->nextright->month=month;
        newnode->nextright->year=year;
        strcpy(newnode->nextright->city, city);
        newnode->nextright->next = NULL;
        newnode->nextbottom = NULL;

        struct Species *currentNode = search(myList, name); //! currentNode is equal to struct species that has name string with the given name parameter
        struct Fishdata *tmp;
        tmp = currentNode->nextright; //! tmp is used for fishdata and set the nextright pointer of the current node.
        while (tmp->next != NULL) { //! this blocks used for determining where should I place this tmp
            tmp = tmp->next;
        } //! when tmp->next==NULL means that there is not any element remaining.
        tmp->next = newnode->nextright; //! set the tmp->next newnode instead of null to be connected these node succesfully.
        myList->size++;
    }
}
void addNewSpecies(struct List *myList){ //! this function adds new species.
    struct Species *newnode; //! I will assign values that are taken from user to that species structure.
    newnode=(struct Species*)malloc(sizeof(struct Species));
    char name[50],city[50],choice;
    int weight,day,month,year;
    float verticallength,diagonallength,crosslength,height,fishlength;
    printf("The New Species:");
    scanf("%s",name); //! for taking name from user.
    while(search(myList,name)!=NULL){ //! thanks to that function we control whether name that is entered by user exist in the list.
    //! if it exists display the error message and take new name from the user.
        printf("This species already exist. Enter new species!\n");
        printf("The New Species:");
        scanf("%s",name);
    }
    //! from 307-323 for taking input from user.
    printf("Weight of the fish in grams:");
    scanf("%d",&weight);
    printf("Vertical length in CM:");
    scanf("%f",&verticallength);
    printf("Diagonal length in CM:");
    scanf("%f",&diagonallength);
    printf("Cross length in CM:");
    scanf("%f",&crosslength);
    printf("Height in CM:");
    scanf("%f",&height);
    printf("Fish length in CM:");
    scanf("%f",&fishlength);
    printf("Fishing Date:");
    scanf("%d/%d/%d",&day,&month,&year);
    printf("City:");
    scanf("%s",city);
    //from 323-336 assigning values of newnode
    strcpy(newnode->name,name);
    newnode->nextright=(struct Fishdata *)malloc(sizeof(struct Fishdata));
    //! nextright pointer of newnode also need allocation because it also holds fishdata structure.
    newnode->nextright->weight=weight;
    newnode->nextright->verticallength=verticallength;
    newnode->nextright->diagonallength=diagonallength;
    newnode->nextright->crosslength=crosslength;
    newnode->nextright->height=height;
    newnode->nextright->fishlength=fishlength;
    newnode->nextright->day=day;
    newnode->nextright->month=month;
    newnode->nextright->year=year;
    strcpy(newnode->nextright->city,city);
    newnode->nextright->next=NULL;
    newnode->nextbottom=NULL;
    myList->tail->nextbottom=newnode; //! my new species should come after tail node.
    myList->tail=newnode; //! tail node needed to uptading newnode.
    myList->size++; //! adding fish increases size
    printf("Do you want to add more fish (Y/N):");
    scanf(" %c",&choice); //! for taking choice from user
    if(choice=='Y' || choice=='y'){ //! if this choice is 'y' or 'Y' user have a chance to add another species.
        addNewSpecies(myList);
    }
}
void deleteFish(struct List *myList,int treshold ){ //! this function is used for deleting Fish that is below the treshold
    int i=0;
    if(!(islempty(myList))) { //! if the list is not empty execute this if block.
        printf("Provide fish weight threshold in grams:");
        scanf("%d", &treshold); //! for taking treshold from the user.
        struct Species *currentSpecies = myList->head->nextbottom; //! we set the current species to first fish node
        struct Species *previousSpecies = NULL; //! we need to previous node to perform deleting operation.
        while (currentSpecies != NULL) {
            struct Fishdata *currentdata = currentSpecies->nextright; //! currentdata is used for taking nextright pointer of currentspecies
            struct Fishdata *previousdata = NULL;
            while (currentdata != NULL) {
                if (currentdata->weight < treshold) { //! if currentdata->weight is less than treshold enter this if block.
                    struct Fishdata *removenode = currentdata; //! when I found the currentdata->weight that is less than treshold this means we should
                    //! delete that data so currentdata is set to removenode;
                    currentdata = currentdata->next; //! update currentdata to next node
                    if (previousdata == NULL) { //! if previous data is NULL this means first data should be deleted
                        currentSpecies->nextright = currentdata; //! we uptaded currentdata and set this as a first data as a first nextright pointer of a currentspecies
                        free(removenode); //! after destorying connection, we need the fre memory for release from the memory.
                    } else { //! if previousdata exists enter this else block
                        previousdata->next = currentdata; //! previousdata comes before of the remove node and we uptaded currendata to removenode->next
                        //! thanks to this line we connect previousdata with the currentdata by passing over removenode
                        free(removenode); //! after destroying connection we need to release it from the memory by using free.

                    }
                    i++; //! after we delete we increase the number of deleted node.
                } else { //! if current data is not suitable for deleting operation make the currentnode to previousnode and update current data with the next data
                    previousdata = currentdata;
                    currentdata = currentdata->next;
                }
            }
            if (currentSpecies->nextright == NULL) { //! After the deletion process, if there is no remaining data for a species, you should also delete the node corresponding to that species.
                struct Species *removenode = currentSpecies;
                if (previousSpecies == NULL) { //! if previousspecies NULL this means that we are at beggining of the list.
                    currentSpecies = currentSpecies->nextbottom; //! we are updating currentSpecies with the next species.
                    myList->head->nextbottom = currentSpecies; //! set the first node of the list to uptaded currentspecies
                    free(removenode); //! do not forget the release this node from the memory.
                } else { //! if the previousspecies is not null enter this loop
                    currentSpecies = currentSpecies->nextbottom; //! uptade the currentspecies with the next of it.
                    previousSpecies->nextbottom = currentSpecies; //! set the previousspecies to uptaded currentspecies
                    free(removenode); //! release the node from the memory.
                }
            } else { //! if there is nothing to delete continue to list traverse
                previousSpecies = currentSpecies;
                currentSpecies = currentSpecies->nextbottom;
            }

        }
        myList->size-=i; //! at the end we subtract the how many elements deleted from list size for finding new size.
        if (myList->size == 0) { //! if my size is 0 this means our list will be empty.
            myList->head = myList->tail; //! head and tail need to be refer to same place because the list is empty.
        }
        printf("%d fish data deleted from your list.\n",i);
    }else{ //! if the list is empty at the begining of this function execute this block.
        printf("Delete operation cannot be implemented at empty list.");
    }
}
void printStatistics(struct List *mylist){
     char species[20]; //! this string will be used for taking input from the user.
     printf("Provide the species:");
     scanf("%s",species);
     int i=0;
     struct Species *tmp=mylist->head->nextbottom; //! set the tmp to first node of the list.
     while(tmp!=NULL){ //! until my tmp is NULL enter this loop.
         if(strcmp(tmp->name,species)==0){ //! this line compare every species in the list seperately with the user-input name.
             struct Fishdata *current=tmp->nextright;  //! after finding this specie we need to number of this specie so current is set to nextright of this specie
             while(current!=NULL){ //! number of nodes at the right of specie tells that how much we have this fish,
             //!so increment i until current will be null.
                 i++;
                 current=current->next;
             }
         }
         tmp=tmp->nextbottom;
     }
     if(i==0){ //! if i variable stay 0, there are no matched name which means that there are no such specie in the list.
         printf("The species that you entered is not found in this list!\n");
     }
     else{ //! for displaying number of this specie.
         printf("The number of available data is %d.\n",i);
     }
}
void searchFishData(struct List *mylist){
    char selection,city[20];
    int month;
    struct Species *node=mylist->head->nextbottom; //! set species to first node which is comes after dummy node.

    printf("Enter your search option (C for city/M for month):");
    scanf(" %c",&selection);
    while(selection!='M'&& selection!='C' && selection!='c' && selection!='m' ){ //! if user enter invalid selection take selection again from the user.
        printf("Invalid selection. Please try again!\n");
        printf("Enter your search option (C for city/M for month):");
        scanf(" %c",&selection);
    }
    if(selection=='M' || selection=='m'){ //! if user enters M or m execute this if block
        printf("Enter month:");
        scanf("%d",&month); //! for taking month from the user.
        while(month>12 || month<1){ //! for controlling validatity of input.
            printf("Wrong month! Enter again.\n");
            printf("Enter month");
            scanf("%d",&month); //! if it is not valid take input from the user again.
        }
        while(node!=NULL){ //! enter this while block until node is NULL
            struct Fishdata *current=node->nextright;  //! set the current to nextright of the current node
            while(current!=NULL){ //! untill current is equal to null execute while block
                if(current->month==month){ //! compare current fishdata month with the user-input month if they are same enter if block
                    printf("%s;%d;%f;%f;%f;%f;%f;%d/%d/%d;%s\n",node->name,current->weight,current->verticallength,current->diagonallength,current->crosslength, current->height,current->fishlength,current->day,current->month,current->year,current->city);
                }
                current=current->next; //! update the current with the next data
            }
            node=node->nextbottom; //! after finishing datas of one species update specie with the next specie.
        }
    }
    else { //! if the selection is C or c enter else block
        printf("Enter the city:");
        scanf("%s",city);
        while(node!=NULL){
            struct Fishdata *current=node->nextright; //! set the current to nextright pointer of node
            while(current!=NULL){
                if(strcmp(current->city,city)==0){ //! if current is matched with the user-input city enter if block
                    printf("%s;%d;%f;%f;%f;%f;%f;%d/%d/%d;%s\n",node->name,current->weight,current->verticallength,current->diagonallength,current->crosslength, current->height,current->fishlength,current->day,current->month,current->year,current->city);
                }
                current=current->next; //! uptade current to next data
            }
            node=node->nextbottom; //! after finishing datas of one species update specie with the next specie.
        }
    }
}
void saveUptadedList(struct List *mylist){ //! when we want to exit to print new list into the file execute this function
    FILE *outfile;
    outfile=fopen("fishingArchive.txt","w"); //! we want to uptaded list into the same file.
    struct Species *node=mylist->head->nextbottom; //! set node to first specie in the list.
    while(node!=NULL){ //! until all specie finished enter this loop.
        struct Fishdata *current=node->nextright; //! set the current to the nextright pointer of the node to print fish data into file
        while(current!=NULL){ //! untill all datas of one specie finished execute this while block
            fprintf(outfile,"%s;%d;%f;%f;%f;%f;%f;%d/%d/%d;%s\n",node->name,current->weight,current->verticallength,current->diagonallength,current->crosslength, current->height,current->fishlength,current->day,current->month,current->year,current->city);
            current=current->next; //! uptade current with the next data of specie
        }
        node=node->nextbottom; //! when all datas of one specie is finished uptade node with the next specie.
    }
    printf("The FishingArchive.txt file has been updated successfully!!");
    fclose(outfile); //! close the file stream.
}

