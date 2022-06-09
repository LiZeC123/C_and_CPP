#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Null -1
#define MAX_QUENE  20

typedef struct tree{
	char data;
	int left;
	int right;
}Tree;

typedef Tree Item;

typedef struct node{
	Item item;
	struct node * next;
}Node;

typedef struct quenu{
	Node * front;
	Node * rear;
	int items;
}Quene;

void InitializeQuene(Quene * pq);

bool QueneIsFull(const Quene * pq);

bool QueneIsEmpty(const Quene * pq); 

int QueneItemCount(const Quene * pq);

bool EnQuene(Item item,Quene * pq);

bool DeQuene(Item * pitem,Quene *pq);

void EmptyTheQuene(Quene *pq);


int BuildTree(Tree a [],int size);
bool Isomorphic(Tree a[],Tree b[],int roota,int rootb);

int main(void){
	int size;
	int root;
	scanf("%d",&size);
	Tree a[size];
	root = BuildTree(a,size); 
	int answer[size];
	for(int i=0;i<size;i++){
		answer[i] = Null;
	}
	
	Quene leaf;
	InitializeQuene(&leaf);
	Item temp;
	EnQuene(a[root],&leaf);
	int edx = 0;
	while(!QueneIsEmpty(&leaf)){
		DeQuene(&temp,&leaf);
		if(temp.left != Null){
			EnQuene(a[temp.left],&leaf);
		}
		if(temp.right != Null){
			EnQuene(a[temp.right],&leaf);
		}
		if(temp.left == Null && temp.right == Null){
			answer[edx] = temp.data;
			edx++;
		}
	}
	
	if(answer[0] != Null){
		printf("%d",answer[0]);
	}
	for(int i=1;i<size;i++){
		if(answer[i] != Null){
			printf(" %d",answer[i]);
		}
		else{
			break;
		}
	}
	return 0;
}


int BuildTree(Tree a [],int size){
	char cl,cr;
	bool check[size];
	for(int i=0;i<size;i++){
		check[i] = true;
	}
	
	for(int i=0;i<size;i++){
		a[i].data = i;
		scanf("\n%c %c",&cl,&cr);
		if(cl != '-'){
			a[i].left = cl - '0';
			check[a[i].left] = false;
		}
		else{
			a[i].left = Null;
		}
		
		if(cr != '-'){
			a[i].right = cr - '0';
			check[a[i].right] = false;
		}
		else{
			a[i].right = Null;
		}
	}
	int root;
	for(int i=0;i<size;i++){
		if(check[i] == true){
			root = i;
			break;
		}
	}
	
	return root;
	
}







/*                               以下部分是quene                        */

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
