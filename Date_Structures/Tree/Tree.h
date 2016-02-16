#ifndef _TREE_H_
#define _TREE_H_
#include <stdbool.h>

#define MAX_NAME  20
#define MAX_ITEMS 10

typedef struct item{
	char petname[MAX_NAME];
	char petkind[MAX_NAME];
}Item;

typedef struct node{
	Item item;
	struct node * left;
	struct node * right;
}Node;

typedef struct tree{
	Node *root;
	int size;
}Tree;

void InitializeTree(Tree * ptree);

bool TreeIsEmpty(const Tree * ptree);

bool TreeIsFull(const Tree * ptree);

int TreeItemCount(const Tree * ptree);

bool AddItem(const Item * pi,Tree * ptree);

bool InTree(const Item * pi,const Tree * ptree);

bool DeleteItem(const Item * pi,Tree * ptree);

void Traverse(const Tree * ptree,void (*pfun)(Item item));

void DeletaAll(Tree * ptree);

#endif

