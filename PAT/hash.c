#include <stdio.h>

#define MAXTABLESIZE 100000 /* �������ٵ����ɢ�б����� */
typedef int ElementType;    /* �ؼ������������� */
typedef int Index;          /* ɢ�е�ַ���� */
typedef Index Position;     /* ��������λ����ɢ�е�ַ��ͬһ���� */
/* ɢ�е�Ԫ״̬���ͣ��ֱ��Ӧ���кϷ�Ԫ�ء��յ�Ԫ������ɾ��Ԫ�� */
typedef enum { Legitimate, Empty, Deleted } EntryType;
 
typedef struct HashEntry Cell; /* ɢ�б���Ԫ���� */
struct HashEntry{
    ElementType Data; /* ���Ԫ�� */
    EntryType Info;   /* ��Ԫ״̬ */
};
 
typedef struct TblNode *HashTable; /* ɢ�б����� */
struct TblNode {   /* ɢ�б���㶨�� */
    int TableSize; /* ������󳤶� */
    Cell *Cells;   /* ���ɢ�е�Ԫ���ݵ����� */
};
 
int NextPrime( int N )
{ /* ���ش���N�Ҳ�����MAXTABLESIZE����С���� */
    int i, p = (N%2)? N+2 : N+1; /*�Ӵ���N����һ��������ʼ */
 
    while( p <= MAXTABLESIZE ) {
        for( i=(int)sqrt(p); i>2; i-- )
            if ( !(p%i) ) break; /* p�������� */
        if ( i==2 ) break; /* for����������˵��p������ */
        else  p += 2; /* ������̽��һ������ */
    }
    return p;
}
 
HashTable CreateTable( int TableSize )
{
    HashTable H;
    int i;
 
    H = (HashTable)malloc(sizeof(struct TblNode));
    /* ��֤ɢ�б���󳤶������� */
    H->TableSize = NextPrime(TableSize);
    /* ������Ԫ���� */
    H->Cells = (Cell *)malloc(H->TableSize*sizeof(Cell));
    /* ��ʼ����Ԫ״̬Ϊ���յ�Ԫ�� */
    for( i=0; i<H->TableSize; i++ )
        H->Cells[i].Info = Empty;
 
    return H;
}

Position Find( HashTable H, ElementType Key )
{
    Position CurrentPos, NewPos;
    int CNum = 0; /* ��¼��ͻ���� */
 
    NewPos = CurrentPos = Hash( Key, H->TableSize ); /* ��ʼɢ��λ�� */
    /* ����λ�õĵ�Ԫ�ǿգ����Ҳ���Ҫ�ҵ�Ԫ��ʱ��������ͻ */
    while( H->Cells[NewPos].Info!=Empty && H->Cells[NewPos].Data!=Key ) {
                                           /* �ַ������͵Ĺؼ�����Ҫ strcmp ����!! */
        /* ͳ��1�γ�ͻ�����ж���ż�� */
        if( ++CNum%2 ){ /* �����γ�ͻ */
            NewPos = CurrentPos + (CNum+1)*(CNum+1)/4; /* ����Ϊ+[(CNum+1)/2]^2 */
            if ( NewPos >= H->TableSize )
                NewPos = NewPos % H->TableSize; /* ����Ϊ�Ϸ���ַ */
        }
        else { /* ż���γ�ͻ */
            NewPos = CurrentPos - CNum*CNum/4; /* ����Ϊ-(CNum/2)^2 */
            while( NewPos < 0 )
                NewPos += H->TableSize; /* ����Ϊ�Ϸ���ַ */
        }
    }
    return NewPos; /* ��ʱNewPos������Key��λ�ã�������һ���յ�Ԫ��λ�ã���ʾ�Ҳ�����*/
}
 
bool Insert( HashTable H, ElementType Key )
{
    Position Pos = Find( H, Key ); /* �ȼ��Key�Ƿ��Ѿ����� */
 
    if( H->Cells[Pos].Info != Legitimate ) { /* ��������Ԫû�б�ռ��˵��Key���Բ����ڴ� */
        H->Cells[Pos].Info = Legitimate;
        H->Cells[Pos].Data = Key;
        /*�ַ������͵Ĺؼ�����Ҫ strcpy ����!! */
        return true;
    }
    else {
        printf("��ֵ�Ѵ���");
        return false;
    }
}