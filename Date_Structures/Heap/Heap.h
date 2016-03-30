#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdbool.h>

typedef int ElementType ;
typedef struct HNode *Heap; /* �ѵ����Ͷ��� */
struct HNode {
    ElementType *Data; /* �洢Ԫ�ص����� */
    int Size;          /* ���е�ǰԪ�ظ��� */
    int Capacity;      /* �ѵ�������� */
};
typedef Heap MaxHeap; /* ���� */
typedef Heap MinHeap; /* ��С�� */
 
#define MAXDATA 10001  /* ��ֵӦ���ݾ����������Ϊ���ڶ������п���Ԫ�ص�ֵ */
#define MINDATA -10001
#define ERROR -999999 /* �����ʶӦ���ݾ����������Ϊ���в����ܳ��ֵ�Ԫ��ֵ */

//������ 
MaxHeap CreateMaxHeap( int MaxSize );
MinHeap CreateMinHeap( int MaxSize );

bool IsFull( Heap H );
bool IsEmpty( Heap H );

//����в��� 
bool MaxInsert( MaxHeap H, ElementType X );
bool MinInsert( MinHeap H, ElementType X);

//ɾ�����еĸ��ڵ� 
ElementType DeleteMax( MaxHeap H );
ElementType DeleteMin( MinHeap H );

//��һ����ȫ���������һ������ 
void MaxPercDown( MaxHeap H, int p );
void BuildMaxHeap( MaxHeap H );

// ��һ����ȫ���������һ����С�� 
void MinPercDown( MinHeap H, int p );
void BuildMinHeap( MaxHeap H );
#endif
