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
	Node * pnode = plist->head;
	while(pnode->next != NULL){
		count++;
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
		plist->head = pnew;
		plist->end =  pnew;
	}
	else{
		plist->end->next = pnew;
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

void Traverse_one(const List * plist,unsigned int location,void(*pfun)(Item item)){
	Node * pnode = plist->head;
	bool get=false;
	unsigned int count=0;
	while(pnode->next != NULL){
		if(count == location){
			get = true;
			break;
		}
		count++;
		pnode=pnode->next;
	}
	if(get){
		(*pfun)(pnode->item);
	}
	else{
		fprintf(stderr,"threr are not so much items\n");
	}
}

bool RandomAddItem(Item item,List * plist,unsigned int location){
	if(location == -1){
		return AddItem(item,plist);
	}
	
	Node * pnew;
	Node * pnode=plist->head;
	pnew=(Node *)malloc(sizeof(Node));
	if(pnew==NULL){
		fprintf(stderr,"The memory is full\n");
		return false;
	}
	CopyToNode(item,pnew);

	if(location == 0){
		pnew->next = plist->head;
		plist->head = pnew;
		return true;
	}
	
	bool get=false;
	unsigned int count=0;
	unsigned int pre_location = location - 1;
	while(pnode->next != NULL){
		if(count == pre_location){
			get = true;
			break;
		}
		count++;
		pnode=pnode->next;
	}
	if(get){
		pnew->next=pnode->next;
		pnode->next=pnew;
		return true;
	}
	else{
		fprintf(stderr,"threr are not so much items\n");
		return false;
	}
}

bool DeleteItem(List * plist,unsigned int location){
	Node * pnode = plist->head;
	if( location < 0 ){
		fprintf(stderr," parameter error:location should greet than zero \n");
		return false;
	}
	else if(location == 0){
		plist->head = pnode->next;
		free(pnode);
		return true;
	}
	
	bool get=false;
	unsigned int count=0;
	unsigned int pre_location = location - 1;
	while(pnode->next != NULL){
		if(count == pre_location){
			get = true;
			break;
		}
		count++;
		pnode=pnode->next;
	}
	if(get){
		Node * psave = pnode->next;
		pnode->next = psave->next;
		free(psave);
		return true;
	}
	else{
		fprintf(stderr,"location should less than the limit of the list\n");
		return false;
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

