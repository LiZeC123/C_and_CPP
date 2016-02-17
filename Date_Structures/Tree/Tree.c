#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"


typedef struct pair{
	Node * parent;
	Node * child;
}Pair;


static Node * MakeNode(const Item * pi);
static void AddNode(Node * new_node,Node * root);
static bool ToLeft(const Item * i1,const Item * i2); 
static bool ToRight(const Item * i1,const Item * i2);
static Pair SeekItem(const Item * pi,const Tree * ptree);		//���ؽṹ�ĺ��� 
static void DeleteNode(Node **ptr);
static void InOrdor(const Node * root,void (*pfun)(Item item));
static void DeleteAllNodes(Node * root);


void InitializeTree(Tree * ptree){
	ptree->size = 0;
	ptree->root = NULL;
}


bool TreeIsEmpty(const Tree * ptree){
	return ptree->size == 0;
}


bool TreeIsFull(const Tree * ptree){
	return ptree->size == MAX_ITEMS;
}


int TreeItemCount(const Tree * ptree){
	return ptree->size;
}


bool AddItem(const Item * pi,Tree * ptree){
	Node * new_node;
	
	if(TreeIsFull(ptree)){
		fprintf(stderr,"Tree is Full\n");
		return false;
	}
	if(SeekItem(pi,ptree).child != NULL){
		fprintf(stderr,"Attempted to add duplicate item\n");
		return false;
	}
	new_node = MakeNode(pi);
	if(new_node == NULL){
		fprintf(stderr,"Couldn't create node\n");
		return false;
	} 
	ptree->size++;
	if(ptree->root == NULL){
		ptree->root=new_node;
	}
	else{
		AddNode(new_node,ptree->root);
	}
	return true;
}


bool InTree(const Item * pi,const Tree * ptree){
	return (SeekItem(pi,ptree).child == NULL)?false:true;
	//�����������ɥ�Ĳ��񰡣� 
} 


bool DeleteItem(const Item * pi,Tree * ptree){
	Pair look;
	look=SeekItem(pi,ptree);
	if(look.child == NULL){
		return false;
	}
	if(look.parent == NULL){
		DeleteNode(&ptree->root);
	}
	else if(look.parent->left == look.child){
		DeleteNode(&look.parent->left);
	}
	else if(look.parent->right == look.child){
		DeleteNode(&look.parent->right);
	}
	return true;
}


void Traverse(const Tree * ptree,void (*pfun)(Item item)){
	if(ptree != NULL){
		InOrdor(ptree->root,pfun);
	}
}


void DeleteAll(Tree * ptree){
	if(ptree != NULL){
		DeleteAllNodes(ptree->root);
	}
	ptree->root = NULL;
	ptree->size = 0;
}
 
 
 static void DeleteAllNodes(Node * root){
 	Node * pright;
 	if(root != NULL){
 		pright = root->right;
 		//�ȱ������ҽڵ�ĵ�ַ���Ա�ýڵ㱻ɾ���Ժ󣬻���֪���ҽڵ��λ�� 
 		DeleteAllNodes(root->left);
 		free(root);
 		DeleteAllNodes(pright);
	 }
 }

static void InOrdor(const Node * root,void (*pfun)(Item item)){
	//����ڵ㣬����Ŀ�����ҽڵ㣬��������ĸ˳�� 
	if(root != NULL){
		InOrdor(root->left,pfun);
		(*pfun)(root->item);
		InOrdor(root->right,pfun);
	}
}


static void DeleteNode(Node **ptr){
	//ptr��ָ��Ŀ��ڵ�ĸ��ڵ���ָ��Ŀ��ڵ��ָ���Ա�ĵ�ַ
	//����*ptr��ָ��Ŀ��ڵ��ָ�� 
	Node  * temp;
	//��һ�������һ���ڵ�Ϊ�գ����ǿսڵ���������ɾ���ڵ�ԭ����λ�� 
	if((*ptr)->left == NULL){
		temp = *ptr;
		*ptr = (*ptr)->right;
		free(temp);
	} 
	else if((*ptr)->right == NULL){
		temp = *ptr;
		*ptr = (*ptr)->left;
		free(temp);
	}
	//�ڶ������������ڵ���������ɾ���ڵ�ԭ����λ�ã��ҽڵ��Դ�����Ѱ�� 
	else{
		for(temp = (*ptr)->left;temp->right != NULL;temp=temp->right){			
			continue;  //��Ҫɾ���Ľڵ����������ʼ����Ѱ�ҿ�Ϊ�յĽڵ� 
		}
		temp->right = (*ptr) ->right;
		temp = *ptr;
		*ptr = (*ptr)->left;
		free(temp); 
	}
}


static Node * MakeNode(const Item * pi){
	Node * new_node;
	
	new_node=(Node *)malloc(sizeof(Node));
	if(new_node != NULL){
		new_node->item  = *pi;
		new_node->left  = NULL;
		new_node->right = NULL;
	}
	return new_node;
}


//root�ǵ�ǰ״̬�µĸ��ڵ� 
//ʹ�õݹ麯���ҵ�������ӵĽڵ� 
static void AddNode(Node * new_node,Node * root){
	if(ToLeft(&new_node->item,&root->item)){
		if(root->left == NULL){
			root->left = new_node;
		}
		else{
			AddNode(new_node,root->left);
		}
	}
	else if(ToRight(&new_node->item,&root->item)){
		if(root->right == NULL){
			root->right = new_node;
		}
		else{
			AddNode(new_node,root->right);
		}
	}
	else{
		fprintf(stderr,"location error in AddNode()\n");
		exit(1);
	}
}


static bool ToLeft(const Item * i1,const Item * i2){
	int comp1;
	
	//�ȱȽ����������������ͬ�ٱȽ����� 
	if((comp1=strcmp(i1->petname ,i2->petname ))<0){
		return true;
	}
	else if(comp1 == 0 && (strcmp(i1->petkind ,i2->petkind )<0) ){
		return true;
	}
	else{
		return false;
	}
}


static bool ToRight(const Item * i1,const Item * i2){
	int comp1;
	
	if((comp1=strcmp(i1->petname ,i2->petname ))>0){
		return true;
	}
	else if(comp1 == 0 && (strcmp(i1->petkind ,i2->petkind )>0) ){
		return true;
	}
	else{
		return false;
	}
}


static Pair SeekItem(const Item * pi,const Tree * ptree){
	//������Ѱ��ָ������Ŀ������¼�ýڵ㼰�丸�ڵ�ĵ�ַ 
	Pair look;
	look.parent = NULL;
	look.child  = ptree->root;
	
	if(look.child == NULL){
		return look;
	}
	while(look.child != NULL){
		if(ToLeft(pi,&(look.child ->item))){
			look.parent = look.child ;
			look.child  = look.child ->left;
		}
		else if(ToRight(pi,&(look.child ->item))){
			look.parent = look.child;
			look.child  = look.child ->right;
		}
		else{
			break;
			//��ʱ�ض�Ϊ������Ŀ��ͬ 
		}
	}
	
	return look;
	//Ҫôchild�������NULL����ʾû���ҵ���Ҫô��break��ѭ������ʾ�ҵ���Ŀ 
}


