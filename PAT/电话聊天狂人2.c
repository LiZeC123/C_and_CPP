#include <stdio.h>
#include <stdlib.h>

#define MAXTABLESIZE 1000001 /* 允许开辟的最大散列表长度 */
typedef long long int  ElementType;    /* 关键词类型用整型 */
typedef int Index;          /* 散列地址类型 */
typedef Index Position;     /* 数据所在位置与散列地址是同一类型 */
/* 散列单元状态类型，分别对应：有合法元素、空单元、有已删除元素 */
typedef enum { Legitimate, Empty, Deleted } EntryType;
 
typedef struct HashEntry Cell; /* 散列表单元类型 */
struct HashEntry{
    ElementType Data; /* 存放元素 */
    EntryType Info;   /* 单元状态 */
    int Count;		  /* 统计次数 */
};
 
typedef struct TblNode *HashTable; /* 散列表类型 */
struct TblNode {   /* 散列表结点定义 */
    int TableSize; /* 表的最大长度 */
    Cell *Cells;   /* 存放散列单元数据的数组 */
};
 
HashTable CreateTable( int TableSize )
{
    HashTable H;
    int i;
 
    H = (HashTable)malloc(sizeof(struct TblNode));
    /* 保证散列表最大长度是素数 */
    H->TableSize = TableSize;
    /* 声明单元数组 */
    H->Cells = (Cell *)malloc(H->TableSize*sizeof(Cell));
    /* 初始化单元状态为“空单元” */
    for( i=0; i<H->TableSize; i++ )
        H->Cells[i].Info = Empty;
 
    return H;
}

Index Hash(int KeyNum,int TableSize){
	return KeyNum % TableSize;
}
 
void Insert( HashTable H, ElementType Key )
{
    Position Pos =  Hash( Key, H->TableSize ); /* 散列位置 */
 
    if( H->Cells[Pos].Info != Legitimate ) { /* 如果这个单元没有被占，则初始化 */
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
