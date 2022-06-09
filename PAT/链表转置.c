#include <stdio.h>
#include <stdlib.h>
#define Null -1


typedef struct list{
	int data;
	int next;
}List;


int ListCount(List a[],int head);
int Reverse(List a[],int head,int k);
void ListPrint(List a[],int head);

int main(void){
	List memory[100000];
	List head;
	head.data = Null;
	int total_number;
	int k;
	scanf("%d%d%d",&head.next,&total_number,&k);
	int temp_adress;
	for(int i=0;i<total_number;i++){
		scanf("%d",&temp_adress);
		scanf("%d %d",&memory[temp_adress].data,&memory[temp_adress].next);
	}
	
	int real_number = ListCount(memory,head.next);
	int flag = 0;
	int each_head;
	while(real_number >= k){
		if(flag == 0){
			head.next = Reverse(memory,head.next,k);
			each_head = head.next;
			flag = 1;
			real_number -= k;
		}
		else{
			each_head = Reverse(memory,each_head,k);
			real_number -= k;
		}
	}
	ListPrint(memory,head.next);
		
}



int ListCount(List a[],int head){
	int count = 1;
	int node = head;
	while(a[node].next != Null){
		count++;
		node = a[node].next;		
	}
	return count;
}


int Reverse(List a[],int head,int k){
	int count = 1;
	int new_node = head;
	int old_node = a[head].next;
	int temp_node = a[old_node].next;
	
	while(count < k){
		a[old_node].next = new_node;
		new_node = old_node;
		old_node = temp_node;
		temp_node = a[old_node].next;
		count++;
	}
	a[head].next = old_node;
	
	return new_node;

}

void ListPrint(List a[],int head){
	int node = head;
	while(a[node].next != Null){
		printf("%05d %d %05d\n",node,a[node].data,a[node].next);
		node = a[node].next;
	}
	printf("%05d %d %d",node,a[node].data,a[node].next);
}
