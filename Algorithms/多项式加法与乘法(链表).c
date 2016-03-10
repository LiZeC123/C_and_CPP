#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct element{
	int coe;	//系数 
	int exp;	//指数 
}Item;


typedef struct node{
	Item item;
	struct node * next;
}Node;

typedef struct list{
	Node * head;
	Node * end;
}List;

void InitializeList(List * plist);
void GetNumber(List * plist);
bool AddItem(Item item,List * plist);
static void CopyToNode(Item item,Node * pnode);
void AndPoly(List * plista,List * plistb,List * plistc);
unsigned int ListItemCount(const List * plist);
void Traverse(const List * plist,void(*pfun)(Item item));
void showmovies(Item item);
void PrintPoly(List * plist);

void MutilPoly(List * plista,List * plistb,List * plistc);
void MutilItem(List * plist,Item item,List * answer);
void MutilAdd(List * plista,List * plistb); 


void EmptyTheList(List * plist);



int main(void){
	
	List poly1;
	List poly2;
	List poly_and;
	List poly_mutil;
	
	InitializeList(&poly1);
	InitializeList(&poly2);
	InitializeList(&poly_and);
	InitializeList(&poly_mutil);
	
	GetNumber(&poly1);
	GetNumber(&poly2);
	
	AndPoly(&poly1,&poly2,&poly_and);
	MutilPoly(&poly1,&poly2,&poly_mutil);
	
	PrintPoly(&poly_mutil);
	printf("\n");
	PrintPoly(&poly_and);
	
}

void GetNumber(List * plist){
	int sum;
	scanf("%d",&sum);
	
	Item temp;
	while(sum--){
		scanf("%d%d",&temp.coe,&temp.exp);
		AddItem(temp,plist);
	}	
}

void AndPoly(List * plista,List * plistb,List * plistc){
	Node * pha = plista->head;
	Node * phb = plistb->head;
	Item temp;
	InitializeList(plistc);
	while(pha != NULL && phb != NULL){
		if(pha->item.exp == phb->item.exp){
			temp.exp = pha->item.exp;
			temp.coe = pha->item.coe + phb->item.coe;
			AddItem(temp,plistc);
			pha = pha->next;
			phb = phb->next;
		}
		else if(pha->item.exp > phb->item.exp){
			temp.exp = pha->item.exp;
			temp.coe = pha->item.coe;
			AddItem(temp,plistc);
			pha = pha->next;
		}
		else{
			temp.exp = phb->item.exp;
			temp.coe = phb->item.coe;
			AddItem(temp,plistc);
			phb = phb->next;
		}
	}
	
	while(pha != NULL){
		temp.exp = pha->item.exp;
		temp.coe = pha->item.coe;
		AddItem(temp,plistc);
		pha = pha->next;
	}
	while(phb != NULL){
		temp.exp = phb->item.exp;
		temp.coe = phb->item.coe;
		AddItem(temp,plistc);
		phb = phb->next;	
	}
}

void MutilPoly(List * plista,List * plistb,List * plistc){
	Node * pha = plista->head;
	Node * phb = plistb->head;
	Item temp;
	InitializeList(plistc);
	unsigned int total;
	total = ListItemCount(plistb);
	List mutiltemp[total];
	//将b中的元素逐个与a相乘 
	for(int i=0;i<total;i++){
		MutilItem(plista,phb->item,&mutiltemp[i]);
		phb = phb->next;
	}
	
	for(int i=1;i<total;i++){
		MutilAdd(&mutiltemp[i-1],&mutiltemp[i]);
	} 
	//将plistc与最后结果再执行一次mutiladd即可得到最后答案 
	
	MutilAdd(&mutiltemp[total-1],plistc) ;
}


void MutilItem(List * plist,Item item,List * answer){
	Node * pnode = plist->head;
	Item temp;
	InitializeList(answer);
	while(pnode != NULL){
		temp.coe = pnode->item.coe * item.coe;
		temp.exp = pnode->item.exp + item.exp;
		AddItem(temp,answer);
		pnode = pnode->next;
	}	
}

//将两个链表相加，将结果定向到plistb指向的位置，并将多余空间释放 
void MutilAdd(List * plista,List * plistb){
	List temp;
	InitializeList(&temp);
	AndPoly(plista,plistb,&temp);
	EmptyTheList(plista);
	EmptyTheList(plistb);
	plistb->head = temp.head;
	plistb->end  = temp.end;
}

void PrintPoly(List * plist){
	int count;
	Node * pnode = plist->head;
	while(pnode != NULL){
		count += pnode->item.coe;
		pnode = pnode->next;
	}
	if(count == 0){
		printf("0 0");
	}
	else{
		pnode = plist->head;
		while(pnode->item.coe == 0){
			pnode = pnode->next;
		}
		printf("%d %d",pnode->item.coe,pnode->item.exp);
		pnode = pnode->next;
		while(pnode != NULL){
			if(pnode->item.coe != 0){
				printf(" %d %d",pnode->item.coe,pnode->item.exp);
			}
			pnode = pnode->next;
		}

	}
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

void InitializeList(List * plist){
	plist->head = NULL;
	plist->end  = NULL; 
}

static void CopyToNode(Item item,Node * pnode){
	
	pnode->item = item;
}

void Traverse(const List * plist,void(*pfun)(Item item)){
	Node * pnode = plist->head;
	while(pnode != NULL){
		(*pfun)(pnode->item);
		pnode = pnode->next;
	}
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

void EmptyTheList(List * plist){
	Node * psave;
	while(plist->head != NULL){
		psave=plist->head->next;
		free(plist->head);
		plist->head = psave;
	}
	
}


