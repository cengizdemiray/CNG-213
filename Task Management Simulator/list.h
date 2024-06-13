#include "queue.h"

typedef struct List {
    Task *head;
    Task *tail;
    int size;
} List;


// Checking if the task list is empty or not
int isEmptyList(List *L)
{

    if(L->size == 0)
        return 1;
    else
        return 0;
}


// Adding the tasks to the list (TODO list in Table 2) considering their arrival time
void insertNode(List *L, Task *T)
{
    if(L->size == 0){
        L->head->next = T;
        L->tail = T;    }
    else   {
        Task *temp;
        temp = (Task *)malloc(sizeof(Task));
        if(temp == NULL){
            printf("Memory allocation is not successful!\n");
            exit(1);   }
        temp = L->head;
        while(temp->next!=NULL && temp->next->arrival_time<=T->arrival_time){
            temp = temp->next;  }
        if(temp->next == NULL){
            L->tail->next = T;
            L->tail = T;   }
        else{
            T->next = temp->next;
            temp->next = T;  }  }
    L->size ++ ;
}


// Taking a max value as an integer and generating&returning a random number between 0 and the value taken
int randomiser(int max_limit)
{
    int output;
    output = rand()%(max_limit);
    return output;
}


// Randomly creating the task list based on the given input and storing them into a linked list based on their arrival time
List *createTaskList(int max_arrival, int max_service, int no_of_developers, int no_of_tasks)
{
    int i, type;    // type is used to keep the randomly generated number for priority assignment/packet label
    char labels[] = {'C', 'H', 'M', 'N'};  // defining packet labels to use for the priority assignment

    // creation and memory allocation of the necessary data structures
    List *L;
    Task *temp, *new_task;
    new_task = (Task *)malloc(sizeof(Task));
    if(new_task == NULL){
        printf("Memory allocation is unsuccessful!\n");
        exit(1);  }

    L = (List *)malloc(sizeof(List));
    L->head = (Task *)malloc(sizeof(Task));
    if(L->head == NULL){
        printf("Memory allocation is unsuccessful!\n");
        exit(1);  }

    L->head->next = NULL;
    L->tail = L->head;
    L->size = 0;
    srand(time(NULL));

    // memory allocation for all the tasks
    for(i=0 ; i<no_of_tasks ; i++){
        temp = (Task *)malloc(sizeof(Task));
        if(temp == NULL){
            printf("Memory allocation is not successful!\n");
            exit(1);  }
        type = randomiser(4);   // 4 as there are 4 priority levels

        // assigning packet labels with randomly generated priorities
        switch(type){
            case 0:
                temp->packet_label = labels[0];
                break;
            case 1:
                temp->packet_label = labels[1];
                break;
            case 2:
                temp->packet_label = labels[2];
                break;
            case 3:
                temp->packet_label = labels[3];
                break;  }
        temp->arrival_time = randomiser(max_arrival);
        temp->service_time = randomiser(max_service);
        temp->service_start_time = 0;
        temp->developer_ID = 0;
        temp->next = NULL;
        insertNode(L,temp);  }

    new_task = L->head->next;

    // printing all the generated&given values as a table (as in Table 2 in the pdf) at the beginning of the program to check if it works correctly
    printf("Packet Label   Arrival Time   Service Time   Service Start Time   Developer ID\n");
    while(new_task != NULL){
        printf("%6c%16d%16d%16d%16d\n", new_task->packet_label, new_task->arrival_time, new_task->service_time, new_task->service_start_time, new_task->developer_ID);
        new_task = new_task->next;  }
    printf("\n\n");

    return L;
}


// Updating the list after removing the task from the list when the time comes
Task *updateList(Queue *Q, List *L)
{
    Task *hold; // this holder task represents the task that the update will be performed on, it will be removed from the list as its turn has come
    hold = (Task *)malloc(sizeof(Task));
    if(!isEmptyList(L)){
        Task *removed;
        removed = (Task *)malloc(sizeof(Task));
        if(removed == NULL){
            printf("Memory allocation is not successful!\n");
            exit(1);  }
        removed = L->head->next;

        // copying the content of 'removed' task in the list, to remove, to the 'hold' task to cut the connection of it to the list to update
        hold->packet_label = removed->packet_label;
        hold->arrival_time = removed->arrival_time;
        hold->service_time = removed->service_time;
        hold->service_start_time = removed->service_start_time;
        hold->developer_ID = removed->developer_ID;
        hold->next = NULL;

        Q->rear->next = hold;
        Q->rear = hold;
        Q->size ++ ;

        L->head->next = removed->next;
        free(removed);
        L->size -- ;

        if(L->size == 0)
            L->tail = L->head;  }
    else {
        printf("No task to remove from the list! It is already empty, please add tasks to remove!\n");
        exit(1);  }
    return hold;    // return to the task that will be taken care of
}



