#include <stdio.h>
#include <stdlib.h>


typedef int Index;                     /* 散列地址类型 */
/******** 以下是单链表的定义 ********/
typedef struct LNode *PtrToLNode;
struct LNode {
    int KetNum;
    int Count;
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
     
    Pos = Hash( KeyNum, H->TableSize ); /* 初始散列位置 */
    P = H->Heads[Pos].Next; /* 从该链表的第1个结点开始 */
    /* 当未到表尾，并且Key未找到时 */ 
    while( P && (P->KetNum != KeyNum) )
        P = P->Next;
 
    return P; /* 此时P或者指向找到的结点，或者为NULL */
}

void Insert( HashTable H, int KeyNum )
{
    Position P, NewCell;
    Index Pos;
     
    P = Find( H,KeyNum );
    if ( !P ) { /* 关键词未找到，可以插入 */
        NewCell = (Position)malloc(sizeof(struct LNode));
        NewCell->KetNum = KeyNum;
        NewCell->Count = 1;
        Pos = Hash( KeyNum , H->TableSize ); /* 初始散列位置 */
        /* 将NewCell插入为H->Heads[Pos]链表的第1个结点 */
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
