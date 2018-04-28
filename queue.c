#include <util.h>
typedef Data char;


typedef struct{
    Data data;
    Node next;
} Node;

typedef struct{
    unsigned int size;
    Node front; 
} Queue;

Queue new_Queue(){
    return malloc(sizeof(Queue));
}

bool 

