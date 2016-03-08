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
	unsigned int count = 0;
	Node * pnode = plist->head;
	while(pnode != NULL){
		count++;
		pnode = pnode->next;
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


void EmptyTheList(List * plist){
	Node * psave;
	while(plist->head != NULL){
		psave=plist->head->next;
		free(plist->head);
		plist->head = psave;
	}
	
}


bool DeleteItem(List * plist,unsigned int location){
	int max_num = ListItemCount(plist);
	Node * this_node;
	Node * pre_node = plist->head;
	int count=1;
	//处于中间的情况直接删除即可 
	if(location > 1 && location < max_num){
		while(count < location -1){
			pre_node = pre_node->next;
			count++;
		}
		this_node = pre_node->next;
		pre_node->next = this_node->next;
		free(this_node);
		return true;
	}
	//删除第一个项目需要调整头指针指向 
	if(location == 1){
		plist->head = plist->head->next;
		return true;
	}
	//删除最后一个项目需要调整末尾指针指向 
	if(location == max_num){
		while(count < location -1){
			pre_node = pre_node->next;
			count++;
		}
		this_node = pre_node->next;
		free(this_node);
		pre_node->next = NULL;
		plist->end = pre_node;
		return true;
	}
	
	//否则数值不再有效范围内 
	fprintf(stderr,"location should less than %u and bigger than zero\n",max_num+1);
	return false;
}


bool RandomAddItem(Item item,unsigned int location,List * plist){
	Node * pnew;
	pnew=(Node *)malloc(sizeof(Node));
	if(pnew==NULL){
		fprintf(stderr,"The memory is full");
		return false;
	}
	CopyToNode(item,pnew);
	
	
	int max_num = ListItemCount(plist);
	Node * this_node;
	Node * pre_node = plist->head;
	int count=1;
	if(location > 1 && location <= max_num){
		while(count < location -1){
			pre_node = pre_node->next;
			count++;
		}
		this_node = pre_node->next;
		pre_node->next = pnew;
		pnew->next = this_node;
		return true;
	}
	if(location == 1){
		pnew->next = plist->head;
		plist->head = pnew;
		return true;
	}
	
	//位置选择错误，释放创建的内存块 
	free(pnew); 
	fprintf(stderr,"location should less than %u and bigger than zero\n",max_num+1);
	return false;
}



static void CopyToNode(Item item,Node * pnode){
	pnode->item = item;
}

