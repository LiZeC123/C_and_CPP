#ifndef LIST_H
#define LIST_H
#include <stdbool.h>

#define MAX_SIZE 45
#define EOL  -1		//表示列表末尾 

struct element{
	char name[MAX_SIZE];
	int age;
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

void Traverse(const List * plist,void(*pfun)(Item item));

void Traverse_one(const List * plist,unsigned int location,void(*pfun)(Item item));

bool RandomAddItem(Item item,List * plist,unsigned int location);

bool DeleteItem(List * plist,unsigned int location);

void EmptyTheList(List * plist);

#endif 
