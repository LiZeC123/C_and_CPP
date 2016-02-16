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
}Quene;

void InitializeQuene(Quene * pq);

bool QueneIsFull(const Quene * pq);

bool QueneIsEmpty(const Quene * pq); 

int QueneItemCount(const Quene * pq);

bool EnQuene(Item item,Quene * pq);

bool DeQuene(Item * pitem,Quene *pq);

void EmptyTheQuene(Quene *pq);

#endif
