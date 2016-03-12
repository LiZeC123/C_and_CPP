#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Stack.h"

static void CopyToNode(Item item,Node * pnode);

void InitializeStack(Stack * pstack){
	pstack->head = NULL;
	pstack->size = 0;
	pstack->end  = NULL;
}

bool StackIsEmpty(Stack * pstack){
	if(pstack->size == 0){
		return true;
	}
	else{
		return false;
	}
}
 
bool StackIsFull(Stack * pstack){
	return !(pstack->size < MAX_SIZE);	
}

unsigned int StackItemCount(const Stack * pstack){
	return pstack->size;
}

bool Push(Item item,Stack * pstack){
	if(StackIsFull(pstack)){
		return false;
	}
	
	Node * pnew;
	pnew=(Node *)malloc(sizeof(Node));

	
	CopyToNode(item,pnew);
	pnew->next=NULL;
	
	if(pstack->end == NULL){
		pstack->head = pnew;
		pstack->end =  pnew;
	}
	else{
		pstack->end->next = pnew;
		pstack->end = pnew;
	}
	pstack->size++;
	return true;
}

bool Pop(Stack * pstack){
	if(StackIsEmpty(pstack)){
		return false;
	}
	
	if(pstack->size == 1){
		free(pstack->end);
		pstack->head = NULL;
		pstack->end  = NULL;	
	}
	else{
		int max_num = StackItemCount(pstack);
		Node * this_node;
		Node * pre_node = pstack->head;
		int count=1;
	
		while(count < max_num -1){
			pre_node = pre_node->next;
			count++;
		}
		
		this_node = pre_node->next;
		free(this_node);
		pre_node->next = NULL;
		pstack->end = pre_node;
	}

	pstack->size--;
	return true;
}

static void CopyToNode(Item item,Node * pnode){
	pnode->item = item;
}
