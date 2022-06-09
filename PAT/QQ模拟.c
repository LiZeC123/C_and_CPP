#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXPWD 17

typedef struct{
	int QQnum;
	char QQpwd[MAXPWD];
}User;


typedef int Index;                     /* ɢ�е�ַ���� */
/******** �����ǵ�����Ķ��� ********/
typedef struct LNode *PtrToLNode;
struct LNode {
    User Data;
    PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;
/******** �����ǵ�����Ķ��� ********/
 
typedef struct TblNode *HashTable; /* ɢ�б����� */
struct TblNode {   /* ɢ�б��㶨�� */
    int TableSize; /* �����󳤶� */
    List Heads;    /* ָ������ͷ�������� */
};



HashTable CreateTable( int TableSize )
{
    HashTable H;
    int i;
 
    H = (HashTable)malloc(sizeof(struct TblNode));
    /* ��֤ɢ�б���󳤶�������*/
    H->TableSize = TableSize;
 
    /* ���·�������ͷ������� */
    H->Heads = (List)malloc(H->TableSize*sizeof(struct LNode));
    /* ��ʼ����ͷ��� */
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
     
    Pos = Hash( Key, H->TableSize ); /* ��ʼɢ��λ�� */
    P = H->Heads[Pos].Next; /* �Ӹ�����ĵ�1����㿪ʼ */
    /* ��δ����β������Keyδ�ҵ�ʱ */ 
    while( P && (P->Data.QQnum != Key.QQnum) )
        P = P->Next;
 
    return P; /* ��ʱP����ָ���ҵ��Ľ�㣬����ΪNULL */
}

bool Insert( HashTable H, User Key )
{
    Position P, NewCell;
    Index Pos;
     
    P = Find( H, Key );
    if ( !P ) { /* �ؼ���δ�ҵ������Բ��� */
        NewCell = (Position)malloc(sizeof(struct LNode));
        NewCell->Data.QQnum = Key.QQnum;
        strcpy(NewCell->Data.QQpwd, Key.QQpwd);
        Pos = Hash( Key, H->TableSize ); /* ��ʼɢ��λ�� */
        /* ��NewCell����ΪH->Heads[Pos]����ĵ�1����� */
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
