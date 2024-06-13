//
// Created by excalıbur-pc on 10.12.2023.
//
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


// Creating an empty queue
void createEmptyQueue(Queue *Q)
{
    Q->front->next = NULL;
    Q->rear = Q->front;
    Q->size = 0;
}


// Checking if the queue is empty or not
int isEmptyQueue(Queue *Q)
{
    if(Q->size==0)
        return 1;
    else
        return 0;
}


// Taking the label for the priority and converting it to an integer to compare the priority levels
int assignPriority(Task *T){
    int level;
    char label;

    label = T->packet_label;
 //   printf("Current label working on: %c\n", label);    // uncomment this statement to see the label of currently processed task (enqueue/dequeue)

    switch(label){
        case 'C':
            level = 4;
            break;
        case 'H':
            level = 3;
            break;
        case 'M':
            level = 2;
            break;
        case 'N':
            level = 1;
            break;  }

    return level;
}


// Taking tasks from the list and putting them into a queue with the priorities considered (enqueue to the front, uncomment line 81 to check the priority in the front constantly)
void enqueue(Queue *Q, Task *T)
{
    // variables: 'newT_priority' represents the priority of the new/currently in the queue task, 't_priority' is the priority of the current task to be enqueued,
    int newT_priority, t_priority;

    Task *t;
    t = (Task *)malloc(sizeof(Task));
    if(t == NULL){
        printf("Memory allocation is not successful!\n");
        exit(1);  }

    // copying the content of the task to be added, T, to the temporary one to update the queue
    t->arrival_time = T->arrival_time;
    t->developer_ID = T->developer_ID;
    t->packet_label = T->packet_label;
    t->service_start_time = T->service_start_time;
    t->service_time = T->service_time;
    t->next = NULL;

    t_priority = assignPriority(t);


    if(Q->size==0)  // if the queue is currently empty
        Q->front = t;

    else
    {
        newT_priority = assignPriority(Q->front);

    //    printf("Queue->front priority:%d, and t priority(task to be added):%d\n\n",newT_priority,t_priority);   // uncomment this statement to see the priorities of the tasks mentioned
        if(t_priority>newT_priority){
            t->next = Q->front;
            Q->front = t; }

        else
        {
            int temp_priority;  // it represents the priority of Q->front to compare it with the current task to be added
            Task *temp;
            temp = (Task *)malloc(sizeof(Task));
            if(temp == NULL){
                printf("Memory allocation is not successful!\n");
                exit(1);  }
            temp = Q->front;
            temp_priority = assignPriority(temp);
            while(temp->next!=NULL && temp_priority<=t_priority){
                temp = temp->next;  }

            t->next = temp->next;
            temp->next = t;
        }
    }

    Q->size ++ ;
}


// Taking tasks from the queue to be taken care of
Task *dequeue(Queue *Q)
{
    if(isEmptyQueue(Q)){
        printf("Queue is empty!\n");
        exit(1);    }

    Task *remove;
    remove = (Task *)malloc(sizeof(Task));
    if(remove == NULL){
        printf("Memory allocation is not successful!\n");
        exit(1);  }

    remove = Q->front;
    Q->front = Q->front->next;

    if(Q->front == NULL)    // if the queue is empty now
        Q->rear = NULL;


    remove->next=NULL;

    Q->size -- ;    // decreasing the size as a task is now removed from the queue

    if(Q->size == 0)    // if the queue is empty now
        Q->rear = NULL;

    return remove;
}

