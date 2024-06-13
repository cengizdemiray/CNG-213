#ifndef queue_h
#define queue_h

// Queue definitions (Task here represents each node of the list/queue)
typedef struct Task{
    char packet_label;
    int arrival_time;
    int service_time;
    int service_start_time;
    int developer_ID;
    struct Task *next;
} Task;


typedef struct Queue{
    Task *front;
    Task *rear;
    int size;
} Queue;

#endif
