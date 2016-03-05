#ifndef LIST_H
#define LIST_H
#include <stdbool.h>

#define MAX_SIZE 45

struct element{
	char name[MAX_SIZE];
	int rating;
};

typedef struct element Item;

typedef struct node{
	Item item;
	struct node * next;
}Node;

typedef struct list{
	Node * head;
	Node * end;
}List;


void InitializeList(List * plist);

bool ListIsEmpty(List * plist);

bool ListIsFull(List * plist);

unsigned int ListItemCount(const List * plist);

bool AddItem(Item item,List * plist);

bool RandomAddItem(Item item,unsigned int location,List * plist);

void Traverse(const List * plist,void(*pfun)(Item item));

void Traverse_one(const List * plist,unsigned int location,void(*pfun)(Item item));

bool DeleteItem(List * plist,unsigned int location);

void EmptyTheList(List * plist);

#endif 
