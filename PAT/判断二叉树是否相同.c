#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Item;

typedef struct tree{
	Item item;
	struct tree * left;
	struct tree * right;
	bool flag;
}Tree; 

Tree * MakeTree(int n);
bool AddItem(const Item * pi,Tree ** ptree);
static Tree * MakeNode(const Item * pi);
static void AddNode(Tree * new_node,Tree * root);
bool Judge(Tree * root,int N);
bool check(Tree * root,Item v);
void Reset(Tree * root);
void FreeTree(Tree * root);



int main(void){
	int N,L;
	Tree * T;
	scanf("%d",&N);
	while(N != 0){
		scanf("%d",&L);
		T =  MakeTree(N);
		for(int i=0;i<L;i++){
			if(Judge(T,N)){
				printf("Yes\n");
			}
			else{
				printf("No\n");
			}
			Reset(T);	
		}
		FreeTree(T);
		scanf("%d",&N);
	}
	return 0;
}

Tree * MakeTree(int n){
	Tree * root = NULL;
	int temp;
	while(n--){
		scanf("%d",&temp);
		AddItem(&temp,&root);
	}
	
	return root;
}

bool check(Tree * root,Item v){
	if(root->flag != true){
		if(root->item == v){
			root->flag = true;
			return true;
		}
		else{
			return false;
		}
	}
	else{
		if(root->item > v){
			return check(root->left,v);
		}
		else if(root->item < v){
			return check(root->right,v);
		}
		else{
			return false;
		}
	}
}

bool Judge(Tree * root,int N){
	int temp;
	bool answer = true;
	for(int i=0;i<N;i++){
		scanf("%d",&temp);
		//���answerΪtrue����ô��ִ��check
		//���checkΪture���������һ��
		//����answer��Ϊfalse ���´�ѭ��ʱ������ִ��check 
		if((answer == true) && (check(root,temp) == false)){
			answer = false;
			//Ϊ�˱�֤��������ݿ���������ȡ
			//���Լ�ʹ�����⣬Ҳ���������˳� 
		}
	}
	return answer;
}

void Reset(Tree * root){
	if(root->left != NULL){
		Reset(root->left);
	} 
	
	if(root->right != NULL){
		Reset(root->right);
	}
	
	root->flag = false;
} 

void FreeTree(Tree * root){
	if(root->left != NULL){
		FreeTree(root->left);
	} 
	
	if(root->right != NULL){
		FreeTree(root->right);
	}
	
	free(root);
}


bool AddItem(const Item * pi,Tree ** ptree){
	Tree * new_node;
	
	new_node = MakeNode(pi);
	//��Ϊ�գ���ֱ����� 
	if(*ptree == NULL){
		*ptree = new_node;
	}
	//�����нڵ㣬��ݹ��Ѱ�ҿ�����ӵĽڵ� 
	else{
		AddNode(new_node,*ptree);
	}
	return true;
}

static Tree * MakeNode(const Item * pi){
	Tree * new_node;
	
	new_node=(Tree *)malloc(sizeof(Tree));
	if(new_node != NULL){
		new_node->item  = *pi;
		new_node->left  = NULL;
		new_node->right = NULL;
		new_node->flag  = false;
	}
	return new_node;
}


static void AddNode(Tree * new_node,Tree * root){
	if(new_node->item < root->item){
		if(root->left == NULL){
			root->left = new_node;
		}
		else{
			AddNode(new_node,root->left);
		}
	}
	else if(new_node->item > root->item){
		if(root->right == NULL){
			root->right = new_node;
		}
		else{
			AddNode(new_node,root->right);
		}
	}
}
