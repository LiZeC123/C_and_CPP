#include <stdio.h>
#include <stdlib.h>
#include "Quene.h"


static void CopyToNode(Item item,Node * pn);
static void CopyToItem(Node * pn,Item * pitem);

void InitializeQuene(Quene * pq){
	pq->front=NULL;
	pq->rear=NULL;
	pq->items=0; 
}

bool QueneIsFull(const Quene * pq){
	return pq->items == MAX_QUENE; 
}

bool QueneIsEmpty(const Quene * pq){
	return pq->items == 0;
}
 
 int QueneItemCount(const Quene * pq){
 	return pq->items;
 }
 
 bool EnQuene(Item item,Quene * pq){
 	Node * pnew;
 	if(QueneIsFull(pq)){
 		return false;
	 }
 	pnew = (Node *)malloc(sizeof(Node));
 	if(pnew==NULL){
 		fprintf(stderr,"Unable to allocate memory!\n");
 		exit(1);
	 }
	 
	 pnew->next = NULL;
	 CopyToNode(item,pnew);
	 if(QueneIsEmpty(pq)){
	 	pq->front=pnew;
	 }
	 else{
	 	pq->rear->next=pnew;
	 }
	 pq->rear=pnew;
	 pq->items++;
	 
	 return true;
 }
 
 bool DeQuene(Item * pitem,Quene *pq){
 	Node * psave;
 	if(QueneIsEmpty(pq)){
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
 
 void EmptyTheQuene(Quene *pq){
 	Item dummy;
 	while(!QueneIsEmpty(pq)){
 		DeQuene(&dummy,pq);
	 }
 }
 
static void CopyToNode(Item item,Node * pn){
	pn->item = item;
}

static void CopyToItem(Node * pn,Item * pitem){
	*pitem = pn->item;
}
