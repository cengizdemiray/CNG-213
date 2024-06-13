// Cengiz Demiray - 2526960

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "queue.c"
#include "queue.h"
#include "list.h"


void parseInput(char **, int *, int *, int *, int *);
void initialiseSimulator(Queue *, int *, int);
void newTask(Queue *, Queue *, List *, int *, int, int);
void accomplishTask(int *, int, int *, Task *, int);
void reportStatistics(Queue *, int, int *, int, int *, int);
int isAvailable(int *, int);


int main(int argc, char **argv)
{
    int no_of_tasks, no_of_developers, max_arrival, max_service;

    if(argc == 1){
        printf("No element!\n");
        exit(1);  }

    // Allocating queues to keep track of the tasks after parsing
    Queue *TaskQueue, *NewQueue;
    NewQueue = (Queue *)malloc(sizeof(Queue));

    // Validation check
    if (NewQueue == NULL){
        printf("Memory allocation of a new queue is unsuccessful!\n");
        exit(0);  }

    NewQueue->front = (Task *)malloc(sizeof(Task));
    createEmptyQueue(NewQueue);

    TaskQueue = (Queue *)malloc(sizeof(Queue));

    // Validation check
    if (TaskQueue == NULL){
        printf("Memory allocation of the task queue is unsuccessful!\n");
        exit(0);  }
    TaskQueue->front = (Task *)malloc(sizeof(Task));

    printf("\n************************************ Report ************************************\n\n");

    // Initializing a task list to keep the record after parsing the input
    List *TaskList;
    parseInput(argv,&no_of_tasks,&no_of_developers,&max_arrival,&max_service);

    int developers[no_of_developers];   // creating an integer array to keep track of available developers
    initialiseSimulator(TaskQueue,developers,no_of_developers);

    TaskList = createTaskList(max_arrival,max_service,no_of_developers,no_of_tasks);
    newTask(TaskQueue,NewQueue,TaskList,developers,no_of_developers,no_of_tasks);

    return 0;
}


// In this function, parsing the input and setting the values in this function
void parseInput(char *argv[], int *no_task, int *no_developers, int *max_arrival, int *max_service)
{
    // setting the values after converting them to integers
    if(argv[0] != NULL){
        *no_task = atoi(argv[1]);
        *no_developers = atoi(argv[2]);
        *max_arrival = atoi(argv[3]);
        *max_service = atoi(argv[4]);  }
    else {
        printf("No value in the array, please provide values to proceed!\n");
        exit(1);  }
}


// In this function, creating an empty queue and an integer array to assign all the developers as available at first
void initialiseSimulator(Queue *Q, int *developers, int no_of_developers)
{
    int i;
    createEmptyQueue(Q);
    for(i=0 ; i<no_of_developers ; i++){
        developers[i] = 1;  } // assigning all to 1 at the beginning as all the developers are available at first
}


// In this function, taking the tasks one by one considering their arrival time and adding them to a queue based on their priority
void newTask(Queue *Q1, Queue *Q2, List *L, int *developers, int no_developers, int no_tasks)
{
    // variables: 'done' is used to count the tasks finished, 'time' is used to track the current time in the program, 'i','j','ind' and 'value' are used as indexes,
    // 'counter' is used to keep checking if a currently unfinished task is done yet, 'waiting' and 'waiting_track' are used to save the total waiting time in the queue
    int done=0, time=0, j=0, i, counter=0, *waiting=0, value, ind=0, waiting_track[no_tasks];

    // variables: 'index' array is used to hold the index(es) of developers who are available at that time to randomly assign them to a new task, 'finish' array is used to
    // save the finish time of each task after they start being served, 'developer_track' array is used to count how many tasks each developer completed and 'finish_dev_track'
    // array is used to save the index(es) of developers (to refer to developers array) for each task assigned
    int index[no_developers], finish[no_tasks], developer_track[no_developers], finish_dev_track[no_tasks];

    int priority, priorities[no_tasks];

    Task *removed, *task;

    // Initially assigning all the values of the arrays below to 0 as they are created statically
    for(i=0 ; i<no_developers ; i++){
        developer_track[i] = 0; }

    for(i=0 ; i<no_tasks ; i++){
        finish[i] = 0;  }

    for(i=0 ; i<no_tasks ; i++){
        finish_dev_track[i] = 0;    }

    for(i=0 ; i<no_tasks ; i++){
        waiting_track[i] = 0;   }

    for(i=0 ; i<no_tasks ; i++){
        priorities[i] = 0;   }


    while(done != no_tasks)  // while there is still a task to complete in the Task List
    {
        if(counter != 0)
        {
            for(i=0 ; i<no_tasks ; i++)
            {
            //    printf("Finish time: %d  ", finish[i]);   // uncomment to see how/when the finish times are assigned to tasks when their time to proceed has come

            // uncomment the print statement below to check (basically to see if the priority queue works correctly) the priority of the task that is taken care of when the time comes
            //    printf("Priority of the task: %d\n", priorities[i]);
                if(finish[i] == time)   // checking if the time has come for any task to over
                {
                    developers[finish_dev_track[i]] = 1;  // making the developer available again as the task is over now
                    developer_track[finish_dev_track[i]]++ ;    // increasing the tasks completed for the corresponding developer
                    done++ ;
                }
            }
   //   printf("# of tasks done: %d\n\n", done);    // uncomment this statement together with the finish time print statement (line 120) to see how the done and finish time values are updated
        }

        // if there is at least 1 task in the TaskList, do the below
        if(!isEmptyList(L))
        {
            if(time >= L->head->next->arrival_time) // if the arrival time for any of the tasks arrived has come
            {
                if(Q1->size == 0)    // if the queue is empty
                {
                    if(isAvailable(developers,no_developers) == 0)   // if all the developers are busy at the moment
                    {
                        Task *temp;
                        temp = (Task *)malloc(sizeof(Task));
                        if (temp == NULL){
                            printf("Memory allocation of a temp task is unsuccessful!\n");
                            exit(0);  }

                        temp = updateList(Q2,L);    // updating the list and saving the element removed from the list to the variable 'temp'
                        enqueue(Q1,temp);   // adding the removed task to the queue
                    }

                    else if(isAvailable(developers,no_developers) >= 1)  // if there is at least 1 developer available
                    {
                        j=0;
                        for(i=0 ; i<no_developers ; i++) // for all the available developers, find and save their indexes
                        {
                            if(developers[i]==1)    // save the index(es) of available developer(s)
                            {
                                index[j] = i;
                                j++ ;
                            }
                        }

                        removed = updateList(Q2,L); // removing a task from the task list

                        if(j==1)    // when there is only 1 developer available, assign it directly (0th index of the index array, and 'value' will have the ID of that developer)
                            value = index[0];
                        else
                            value = index[randomiser(j-1)];  // assign a random developer for the task

                        accomplishTask(&waiting,time,developers,removed,value);

                        finish[ind] = (removed->service_start_time) + (removed->service_time);  // saving the finish time of the task when it starts getting served
                        finish_dev_track[ind] = value;  // saving the ID of assigned developer for a task
                        priority = assignPriority(removed);
                     //   printf("\nPRIOO: %d\n", priority);
                        priorities[ind] = priority; // assigning the priority of all the tasks considering the order they are being treated to check if the queue implementations are correct
                        waiting_track[ind] = waiting;   // saving the waiting time of each task to the array for further use to calculate the max waiting time
                        ind++ ;
                        counter++ ; // increasing the counter as a task is assigned to a developer now (accomplishTask)
                    }
                }

                else    // when the queue is not empty
                {
                    if(isAvailable(developers,no_developers) >= 1)  // if there is at least 1 developer available
                    {
                        task = dequeue(Q1); // dequeue the task from the queue to assign to a developer

                        j=0;
                        for(i=0 ; i<no_developers ; i++)    // for all the available developers, find and save their indexes
                        {
                            if(developers[i] == 1)  // saving the index(es) of available developer(s)
                            {
                                index[j] = i;
                                j++ ;
                            }
                        }

                        if(j==1)
                            value = index[0];
                        else
                            value = randomiser(j-1);  // assigning a random developer for the task

                        accomplishTask(&waiting,time,developers,task,value);

                        finish[ind] = (task->service_start_time) + (task->service_time);    // saving the finish time of the task when it starts getting served
                        finish_dev_track[ind] = value;  // saving the ID of assigned developer for a task
                        priority = assignPriority(task);
                        priorities[ind] = priority; // assigning the priority of all the tasks considering the order they are being treated to check if the queue implementations are correct
                        waiting_track[ind] = waiting;   // saving the waiting time of each task to the array for further use to calculate the max waiting time
                        ind++ ;
                        counter++ ; // increasing the counter as a task is assigned to a developer (accomplishTask)
                    }

                    else if(isAvailable(developers,no_developers) == 0) // if there is no available developer currently
                    {
                        Task *temp;
                        temp = (Task *)malloc(sizeof(Task));
                        if (temp == NULL){
                            printf("Memory allocation of a temp task is unsuccessful!\n");
                            exit(0);  }

                        temp = updateList(Q2,L);    // updating the list and saving the task removed from the list to the variable 'temp'
                        enqueue(Q1,temp);   // adding the task to the queue
                    }
                }
            }
        }

        else    // when the task list is empty (all the tasks are either being treated or currently in the queue)
        {
            if(Q1->size != 0) // if Q1 is not empty
            {
                if(isAvailable(developers, no_developers) >= 1) //
                {
                    task = dequeue(Q1); // dequeue the task from the queue

                    j = 0;
                    for(i = 0; i < no_developers; i++)    // for all the available developers, find and save their indexes
                    {
                        if(developers[i] == 1)  // saving the index(es) of available developer(s)
                        {
                            index[j] = i;
                            j++ ;
                        }
                    }

                    if(j == 1)
                        value = index[0];
                    else
                        value = randomiser(j - 1);  // assigning a random developer for the task

                    accomplishTask(&waiting,time,developers,task,value);
                    finish[ind] = (task->service_start_time) + (task->service_time);    // saving the finish time of the task when it starts getting served
                    finish_dev_track[ind] = value;  // saving the ID of assigned developer for a task
                    priority = assignPriority(task);
                    priorities[ind] = priority; // assigning the priority of all the tasks considering the order they are being treated to check if the queue implementations are correct
                    waiting_track[ind] = waiting;   // saving the waiting time of each task to the array for further use to calculate the max waiting time

                    ind++ ;
                    counter++ ; // increasing the counter as a task is assigned to a developer (accomplishTask)
                }
            }
        }

       // printf("Time: %d\n\n",time);  // uncomment to display the current time in each iteration
        time++ ;
    }

    // uncomment the statements below to print the assigned developers for each task at the end when all tasks are assigned & treated
   /* printf("Assigned developers for each task: \n");
    for(i=0 ; i<no_tasks ; i++){
        printf("For task %d: %d\n",i+1, finish_dev_track[i]+1); }
    */
    reportStatistics(Q2,no_tasks,developer_track,no_developers,waiting_track,time); // displaying the statistics required
}


// In this function, taking a task from the queue to be treated by a developer
void accomplishTask(int *waiting, int time, int *developers, Task *T, int index)
{
    developers[index] = 0;  // making the developer busy until the work is done
    T->service_start_time = time;   // updating the service start time as the current time
    T->developer_ID = index+1;  // updating the developer ID of the developer assigned
    *waiting = (T->service_start_time) - (T->arrival_time);
}


// In this function, reporting the statistics asked
void reportStatistics(Queue *Q, int no_of_tasks, int *developer_track, int no_of_developers, int *waiting_array, int completion_time)
{
    // variables: 'task_labels' array is used to keep track of the # of each priority level (packet label) occurred in the task list
    int task_labels[]={0,0,0,0}, priority, i , max_waiting, total_waiting=0;
    float avg_time;

    Task *temp;
    temp = (Task *)malloc(sizeof(Task));
    if(temp == NULL){
        printf("Memory allocation is not successful!\n");
        exit(1);  }
    temp = Q->front->next;

    while(temp != NULL){
        priority = assignPriority(temp);    // finding the priority level for each task
        task_labels[priority-1] ++ ;    // increasing the corresponding priority level to display later
        temp = temp->next; }

    // finding the max waiting time in the queue among all the tasks (uncomment the print statement to check them separately as well)
    max_waiting = waiting_array[0];
    for(i=0 ; i<no_of_tasks ; i++)
    {
        total_waiting += waiting_array[i];  // calculating the total waiting time spent in the queue
        if(waiting_array[i]>max_waiting)
            max_waiting=waiting_array[i];
      //  printf("Waiting for task %d: %d\n", i+1, waiting_array[i]);
    }

     printf("*The number of Developers is: %d\n", no_of_developers);
     printf("*The number of Tasks: %d\n", no_of_tasks);
     printf("*Number of Tasks for each Label:\n\tCritical: %d\n\tHigh priority: %d\n\tMedium: %d\n\tNormal: %d\n",task_labels[3],task_labels[2],task_labels[1],task_labels[0]);

     printf("*Number of Tasks for each Developer:\n");
     for(i=0 ; i<no_of_developers ; i++){
        printf("\tDeveloper %d Accomplished: %d\n", i+1, developer_track[i]);  }

    printf("*Completion time: %d\n", completion_time);

    avg_time = (float)total_waiting/no_of_tasks;
    printf("*Average time spent in the queue: %.1f\n", avg_time);

    printf("*Maximum waiting time: %d\n", max_waiting);
}


// Checking if there is/are an available developer to assign a task
int isAvailable(int *developers, int no_developers)
{
    int i, count=0;  // count variable keeps the # of available developers if there is any
    for(i=0 ; i<no_developers ; i++){
        if(developers[i] == 1)
            count++ ;   }
    return count;
}





