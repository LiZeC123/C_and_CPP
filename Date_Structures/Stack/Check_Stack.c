#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdbool.h>


typedef struct item{
	int data;
}Item;


typedef struct node{
	Item item;
	struct node * next;
}Node;

typedef struct stack{
	Node * head;
	int size;
	Node * end;
}Stack;


void InitializeStack(Stack * pstack);

bool StackIsEmpty(Stack * pstack);

bool StackIsFull(Stack * pstack);

unsigned int StackItemCount(const Stack * pstack);

bool Push(Item item,Stack * pstack);

bool Pop(Stack * pstack);

static void CopyToNode(Item item,Node * pnode);

int MAX_SIZE;   //堆栈的最大长度 

bool check(int a[],int num);

int main(void){
	int num;		//序列的长度 
	int times;		//需要验证的序列个数 
	scanf("%d%d%d",&MAX_SIZE,&num,&times);
	

	
	bool answer[times];
	int sk[num];
	for(int i=0;i<times;i++){
		for(int j=0;j<num;j++){
			scanf("%d",&sk[j]);
		} 
		answer[i] = check(sk,num);
	}
	
	//print bool
	for(int i=0;i<times-1;i++){
		if(answer[i]){
			printf("YES\n");
		}else{
			printf("NO\n");
		}
	}
	if(answer[times-1]){
		printf("YES\n");
	}else{
		printf("NO\n");
	}
}


bool check(int a[],int num){
	Stack text;
	InitializeStack(&text);
	Item temp;
	int read_edx= num;		//指示此时什么值应该被弹出 
	int arr_edx = num-1; 		//指示数组下标,数组反向读取 
	while(num--){
		if(StackIsFull(&text)){
			return false;
		}else{
			temp.data = a[arr_edx];
			Push(temp,&text);
			
			while(!(StackIsEmpty(&text)) && text.end->item.data == read_edx ){
				Pop(&text);
				read_edx--;
			}
		}
		arr_edx--;
	}
	
	if(StackIsEmpty(&text)){
		return true;
	}else{
		return false;
	}
}



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
