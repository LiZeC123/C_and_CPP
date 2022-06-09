#include <stdio.h>
#include <stdlib.h>
//堆栈头文件 
#include <stdbool.h>
#define MAX_SIZE 50 
typedef int Item;

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
Item Top(Stack * pstack);
bool Pop(Stack * pstack);
static void CopyToNode(Item item,Node * pnode);
//堆栈头文件结束 

typedef struct tree{
	char data;
	struct tree * left;
	struct tree * right;
}Tree;



void OrderToPost(int * inorder,int * preorder,int len);
int GetInputData(void);

bool flag = true;


int main(void){
	int N;
	scanf("%d",&N);
	//去除\n 
	getchar();
	int inorder[N];
	int prorder[N];
	int edx_inorder = 0;
	int edx_prorder = 0;
	
	Stack stack_x;
	InitializeStack(&stack_x);
	
	int temp;
	for(int i=0;i<2*N;i++){
		temp = GetInputData();
		if(temp != 0){
			prorder[edx_prorder] = temp;
			edx_prorder++;
			Push(temp,&stack_x);
		}
		else{
			temp = Top(&stack_x);
			inorder[edx_inorder] = temp;
			edx_inorder++;
			Pop(&stack_x);
		}
	}
	OrderToPost(inorder,prorder,N);
}
	
void OrderToPost(int * inorder,int * preorder,int len){
	if(len == 0){
		return;
	}
	
	int node_value = *preorder;
	int edx = 0;
	while(edx<len){
		if(inorder[edx] == node_value){
			break;
		}
		edx++;
	}
	//left
	OrderToPost(inorder,preorder + 1,edx);
	//right
	OrderToPost(inorder + edx + 1,preorder + edx + 1,len - (edx + 1));
	
	if(flag){
		printf("%d",node_value);
		flag = false;
	}
	else{
		printf(" %d",node_value);
	}
	
}

int GetInputData(void){
	char c;
	int x;
	getchar();
	c = getchar();
	if(c == 'o'){
		while(getchar() != '\n'){
			continue;
		}
		return 0;
	}
	else{
		scanf("sh %d",&x);
		getchar();
		return x;
	}
}



//堆栈函数
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

Item Top(Stack * pstack){
	Item temp;
	temp = pstack->end->item;
	return temp;
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
//堆栈函数结束 
