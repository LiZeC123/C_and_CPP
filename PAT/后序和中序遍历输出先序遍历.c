#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
void OrderToPost(int * inorder,int * preorder,int len);

int main(void){
	int N;
	scanf("%d",&N);
	int i;
	int inorder[N];
	int prorder[N];
	
	for(i=0;i<N;i++){
		scanf("%d",&prorder[i]);
	}

	for(i=0;i<N;i++){
		scanf("%d",&inorder[i]);
	}
	printf("Preorder:");
	OrderToPost(inorder,prorder,N);
}

//输入中序与后序，转化为前序 
void OrderToPost(int * inorder,int * prorder,int len){
	if(len == 0){
		return;
	}
	
	int node_value = *(prorder+(len-1));
	printf(" %d",node_value);

	int edx = len-1;
	while(edx>=0){
		if(inorder[edx] == node_value){
			break;
		}
		edx--;
	}
	//left
	OrderToPost(inorder,prorder,edx);
	//right
	OrderToPost(inorder + edx + 1,prorder + edx ,len - (edx + 1));
}

