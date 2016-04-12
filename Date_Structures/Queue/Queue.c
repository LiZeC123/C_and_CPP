#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"


static void CopyToNode(Item item,Node * pn);
static void CopyToItem(Node * pn,Item * pitem);

void InitializeQueue(Queue * pq){
	pq->front=NULL;
	pq->rear=NULL;
	pq->items=0; 
}

bool QueueIsFull(const Queue * pq){
	return pq->items == MAX_QUENE; 
}

bool QueueIsEmpty(const Queue * pq){
	return pq->items == 0;
}
 
 int QueueItemCount(const Queue * pq){
 	return pq->items;
 }
 
 bool EnQueue(Item item,Queue * pq){
 	Node * pnew;
 	if(QueueIsFull(pq)){
 		return false;
	 }
 	pnew = (Node *)malloc(sizeof(Node));
 	if(pnew==NULL){
 		fprintf(stderr,"Unable to allocate memory!\n");
 		exit(1);
	 }
	 
	 pnew->next = NULL;
	 CopyToNode(item,pnew);
	 if(QueueIsEmpty(pq)){
	 	pq->front=pnew;
	 }
	 else{
	 	pq->rear->next=pnew;
	 }
	 pq->rear=pnew;
	 pq->items++;
	 
	 return true;
 }
 
 bool DeQueue(Item * pitem,Queue *pq){
 	Node * psave;
 	if(QueueIsEmpty(pq)){
 		return false;
	 }
	 CopyToItem(pq->front ,pitem);
	 psave=pq->front ;
	 pq->front =pq->front->next;
	 free(psave);
	 pq->items--;
	 if(pq->items == 0){
	 	pq->rear = NULL;
	 }
	 return true;
 }
 
 void EmptyTheQueue(Queue *pq){
 	Item dummy;
 	while(!QueueIsEmpty(pq)){
 		DeQueue(&dummy,pq);
	 }
 }
 
static void CopyToNode(Item item,Node * pn){
	pn->item = item;
}

static void CopyToItem(Node * pn,Item * pitem){
	*pitem = pn->item;
}
