#include <stdio.h>
#include <stdlib.h>
#include "List.h"

//结构不能直接比较大小，需要一个函数来比较
 
static bool IsEqual(Item item1,Item item2);

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


bool RandomAddItem(Item item,unsigned int location,List * plist){
	int max_node = ListItemCount(plist);
	if(location > max_node+1){
		fprintf(stderr,"\nerror : there are only %u item(s)\n",max_node);
		return false;	
	}
	else if(location < 1){
		fprintf(stderr,"\nerror : location shuold great than zero\n");
		return false;
	}

	
	Node * pnew;
	pnew=(Node *)malloc(sizeof(Node));
	if(pnew==NULL){
		fprintf(stderr,"The memory is full\n");
		return false;
	}
	CopyToNode(item,pnew);

	

	Node * pnode=plist->head;
	
	//如果链表为空 
	if(pnode == NULL){
		plist->head = pnew;
		plist->end =  pnew;
		return true ;
	}
	
	
	unsigned int count=1;
	unsigned int pre_location = location - 1;
	while(pnode->next != NULL && count != pre_location){
		count++;
		pnode=pnode->next;
	}
	
	pnew->next=pnode->next;
	pnode->next=pnew;
	return true;
}


bool DeleteItem(List * plist,unsigned int location){
	Node * pnode = plist->head;
	int max_node = ListItemCount(plist);
	if( location < 1 ){
		fprintf(stderr," parameter error:location should greet than zero \n");
		return false;
	}
	else if(location < max_node){
		fprintf(stderr,"location should less than the limit of the list\n");
		return false;
	}
 	if(location == 1){
		plist->head = pnode->next;
		free(pnode);
		return true;
	}
	
	unsigned int count=1;
	unsigned int pre_location = location - 1;
	while(pnode->next != NULL && count != pre_location){
		count++;
		pnode=pnode->next;
	}
	Node * psave = pnode->next;
	pnode->next = psave->next;
	free(psave);
	return true;
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

