#include <stdio.h>
#include <stdlib.h>


typedef int Index;                     /* ɢ�е�ַ���� */
/******** �����ǵ�����Ķ��� ********/
typedef struct LNode *PtrToLNode;
struct LNode {
    int KetNum;
    int Count;
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

    for( i=0; i<H->TableSize; i++ ) {
         H->Heads[i].Count = 0;
         H->Heads[i].KetNum = 0;
         H->Heads[i].Next = NULL;
    }
 
    return H;
}

Index Hash(int KeyNum,int TableSize){
	return KeyNum % TableSize;
}

Position Find( HashTable H, int KeyNum )
{
    Position P;
    Index Pos;
     
    Pos = Hash( KeyNum, H->TableSize ); /* ��ʼɢ��λ�� */
    P = H->Heads[Pos].Next; /* �Ӹ�����ĵ�1����㿪ʼ */
    /* ��δ����β������Keyδ�ҵ�ʱ */ 
    while( P && (P->KetNum != KeyNum) )
        P = P->Next;
 
    return P; /* ��ʱP����ָ���ҵ��Ľ�㣬����ΪNULL */
}

void Insert( HashTable H, int KeyNum )
{
    Position P, NewCell;
    Index Pos;
     
    P = Find( H,KeyNum );
    if ( !P ) { /* �ؼ���δ�ҵ������Բ��� */
        NewCell = (Position)malloc(sizeof(struct LNode));
        NewCell->KetNum = KeyNum;
        NewCell->Count = 1;
        Pos = Hash( KeyNum , H->TableSize ); /* ��ʼɢ��λ�� */
        /* ��NewCell����ΪH->Heads[Pos]����ĵ�1����� */
        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell; 
    }
    else { 
        P->Count++;
    }
}

typedef struct{
	int Phone;
	int Count;
};


int main(void){
	int TableSize = 100001;
	HashTable H;
	H = CreateTable(TableSize);
	
	int N;
	scanf("%d",&N);
	
	int Phone1,Phone2;
	while(N--){
		scanf("%d %d",&phone1,&phone2);
		Insert(H,phone1);
		Insert(H,phone2);
	}
	
	
	
	
	
	return 0;
}
