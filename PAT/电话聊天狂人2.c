#include <stdio.h>
#include <stdlib.h>

#define MAXTABLESIZE 1000001 /* �����ٵ����ɢ�б��� */
typedef long long int  ElementType;    /* �ؼ������������� */
typedef int Index;          /* ɢ�е�ַ���� */
typedef Index Position;     /* ��������λ����ɢ�е�ַ��ͬһ���� */
/* ɢ�е�Ԫ״̬���ͣ��ֱ��Ӧ���кϷ�Ԫ�ء��յ�Ԫ������ɾ��Ԫ�� */
typedef enum { Legitimate, Empty, Deleted } EntryType;
 
typedef struct HashEntry Cell; /* ɢ�б�Ԫ���� */
struct HashEntry{
    ElementType Data; /* ���Ԫ�� */
    EntryType Info;   /* ��Ԫ״̬ */
    int Count;		  /* ͳ�ƴ��� */
};
 
typedef struct TblNode *HashTable; /* ɢ�б����� */
struct TblNode {   /* ɢ�б��㶨�� */
    int TableSize; /* �����󳤶� */
    Cell *Cells;   /* ���ɢ�е�Ԫ���ݵ����� */
};
 
HashTable CreateTable( int TableSize )
{
    HashTable H;
    int i;
 
    H = (HashTable)malloc(sizeof(struct TblNode));
    /* ��֤ɢ�б���󳤶������� */
    H->TableSize = TableSize;
    /* ������Ԫ���� */
    H->Cells = (Cell *)malloc(H->TableSize*sizeof(Cell));
    /* ��ʼ����Ԫ״̬Ϊ���յ�Ԫ�� */
    for( i=0; i<H->TableSize; i++ )
        H->Cells[i].Info = Empty;
 
    return H;
}

Index Hash(int KeyNum,int TableSize){
	return KeyNum % TableSize;
}
 
void Insert( HashTable H, ElementType Key )
{
    Position Pos =  Hash( Key, H->TableSize ); /* ɢ��λ�� */
 
    if( H->Cells[Pos].Info != Legitimate ) { /* ��������Ԫû�б�ռ�����ʼ�� */
        H->Cells[Pos].Info = Legitimate;
        H->Cells[Pos].Data = Key;
        H->Cells[Pos].Count = 0;
    }
    else {
        H->Cells[Pos].Count++;
    }
}

int main(void){
	int TableSize = 100001;
	HashTable H;
	H = CreateTable(TableSize);
	
	int N;
	scanf("%d",&N);
	
	int phone1,phone2;
	while(N--){
		scanf("%I64d %I64d",&phone1,&phone2);
		Insert(H,phone1);
		Insert(H,phone2);
	}
	for(int i=0;i<TableSize;i++){
		if(H->Cells[i].Info != Empty){
			printf("%I64d %d\n",H->Cells[i].Data,H->Cells[i].Count);
		}
	}

	return 0;
}
