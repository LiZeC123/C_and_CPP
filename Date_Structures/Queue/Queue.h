#ifndef QUENE_H
#define QUENE_H
#include <stdbool.h>

#define MAX_QUENE 10

/*
struct element{
	int c;
};
*/
typedef int Item;

typedef struct node{
	Item item;
	struct node * next;
}Node;

typedef struct quenu{
	Node * front;
	Node * rear;
	int items;
}Queue;

void InitializeQueue(Queue * pq);

bool QueueIsFull(const Queue * pq);

bool QueueIsEmpty(const Queue * pq); 

int QueueItemCount(const Queue * pq);

bool EnQueue(Item item,Queue * pq);

bool DeQueue(Item * pitem,Queue *pq);

void EmptyTheQueue(Queue *pq);

#endif
