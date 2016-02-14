#include <stdio.h>
#include <stdlib.h>
#include "List.h"

static void CopyToNode(Item item,Node * pnode);

void InitializeList(List * plist){
	plist->head = NULL;
	plist->end  = NULL; 
}

bool ListIsEmpty(List * plist){
	if(plist->head==NULL){
		return true;
	}
	else{
		return false;
	}
}

bool ListIsFull(List * plist){
	Node * pt;
	bool full;
	pt=(Node *)malloc(sizeof(Node));
	if(pt==NULL){
		full= true;
	}
	else{
		full=false;
	}
	free(pt);
	return full;
}

unsigned int ListItemCount(const List * plist){
	unsigned int count=0;
	Node * pt;
	if(plist->head != NULL){
		count = plist->end->edx;
		count++ ; //edx´ÓÁã¿ªÊ¼ 
	}
	return count;
}

bool AddItem(Item item,List * plist){
	Node * pnew;
	pnew=(Node *)malloc(sizeof(Node));
	if(pnew==NULL){
		fprintf(stderr,"The memory is full");
		return false;
	}
	
	CopyToNode(item,pnew);
	pnew->next=NULL;
	
	if(plist->head == NULL){
		pnew->edx = 0;
		plist->head = pnew;
		plist->end =  pnew;
	}
	else{
		plist->end->next = pnew;
		pnew->edx = (plist->end->edx + 1);
		plist->end = pnew;
	}
	return true;
}

void Traverse(const List * plist,void(*pfun)(Item item)){
	Node * pnode = plist->head;
	while(pnode != NULL){
		(*pfun)(pnode->item);
		pnode = pnode->next;
	}
}

void EmptyTheList(List * plist){
	Node * psave;
	while(plist->head != NULL){
		psave=plist->head->next;
		free(plist->head);
		plist->head = psave;
	}
	
}

static void CopyToNode(Item item,Node * pnode){
	pnode->item = item;
}








