#ifndef _STACK_H_
#define _STACK_H_

#include <stdbool.h>

#define MAX_SIZE 5

typedef struct item{
	int data;
}Item;


typedef struct node{
	Item item;
	struct node * next;
}Node;

typedef struct stack{
	Node * head;
	int size;
	Node * end;
}Stack;


void InitializeStack(Stack * pstack);

bool StackIsEmpty(Stack * pstack);

bool StackIsFull(Stack * pstack);

unsigned int StackItemCount(const Stack * pstack);

bool Push(Item item,Stack * pstack);

bool Pop(Item * item,Stack * pstack);

#endif
