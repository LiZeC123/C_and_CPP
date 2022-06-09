#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXPWD 17

typedef struct{
	int QQnum;
	char QQpwd[MAXPWD];
}User;


typedef int Index;                     /* 散列地址类型 */
/******** 以下是单链表的定义 ********/
typedef struct LNode *PtrToLNode;
struct LNode {
    User Data;
    PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;
/******** 以上是单链表的定义 ********/
 
typedef struct TblNode *HashTable; /* 散列表类型 */
struct TblNode {   /* 散列表结点定义 */
    int TableSize; /* 表的最大长度 */
    List Heads;    /* 指向链表头结点的数组 */
};



HashTable CreateTable( int TableSize )
{
    HashTable H;
    int i;
 
    H = (HashTable)malloc(sizeof(struct TblNode));
    /* 保证散列表最大长度是素数*/
    H->TableSize = TableSize;
 
    /* 以下分配链表头结点数组 */
    H->Heads = (List)malloc(H->TableSize*sizeof(struct LNode));
    /* 初始化表头结点 */
    User temp;
    temp.QQnum = 0;
    for(i=0;i<MAXPWD;i++){
    	temp.QQpwd[i] = '\0';
	}
    for( i=0; i<H->TableSize; i++ ) {
         H->Heads[i].Data = temp;
         H->Heads[i].Next = NULL;
    }
 
    return H;
}

Index Hash(User Key,int TableSize){
	return Key.QQnum % TableSize;
}

Position Find( HashTable H, User Key )
{
    Position P;
    Index Pos;
     
    Pos = Hash( Key, H->TableSize ); /* 初始散列位置 */
    P = H->Heads[Pos].Next; /* 从该链表的第1个结点开始 */
    /* 当未到表尾，并且Key未找到时 */ 
    while( P && (P->Data.QQnum != Key.QQnum) )
        P = P->Next;
 
    return P; /* 此时P或者指向找到的结点，或者为NULL */
}

bool Insert( HashTable H, User Key )
{
    Position P, NewCell;
    Index Pos;
     
    P = Find( H, Key );
    if ( !P ) { /* 关键词未找到，可以插入 */
        NewCell = (Position)malloc(sizeof(struct LNode));
        NewCell->Data.QQnum = Key.QQnum;
        strcpy(NewCell->Data.QQpwd, Key.QQpwd);
        Pos = Hash( Key, H->TableSize ); /* 初始散列位置 */
        /* 将NewCell插入为H->Heads[Pos]链表的第1个结点 */
        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell; 
        return true;
    }
    else { 
        return false;
    }
}

int main(void){
	int TableSize = 20001;
	HashTable H;
	H = CreateTable(TableSize);
	
	int N;
	scanf("%d",&N);
	
	const int MaxPwd = 17;
	char cmd;
	User user;
	Position P;
	
	getchar();
	while(N--){
		cmd = getchar();
		for(int i=0;i<MaxPwd;i++){
    		user.QQpwd[i] = '\0';
		}
		switch (cmd){
			case 'N':
				scanf("%d %s",&user.QQnum,user.QQpwd);
				getchar();
				if(!Insert(H,user)){
					printf("ERROR: Exist\n");
					break;
				}
				else{
					printf("New: OK\n");
					break;
				}
			case 'L':
				scanf("%d %s",&user.QQnum,user.QQpwd);
				getchar();
				P = Find(H,user);
				if(P == NULL){
					printf("ERROR: Not Exist\n");
				}
				else if(!strcmp(P->Data.QQpwd,user.QQpwd)){
					printf("Login: OK\n");
				}
				else{
					printf("ERROR: Wrong PW\n");
				}	
		}		
	}
	
}
