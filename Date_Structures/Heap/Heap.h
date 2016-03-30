#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdbool.h>

typedef int ElementType ;
typedef struct HNode *Heap; /* 堆的类型定义 */
struct HNode {
    ElementType *Data; /* 存储元素的数组 */
    int Size;          /* 堆中当前元素个数 */
    int Capacity;      /* 堆的最大容量 */
};
typedef Heap MaxHeap; /* 最大堆 */
typedef Heap MinHeap; /* 最小堆 */
 
#define MAXDATA 10001  /* 该值应根据具体情况定义为大于堆中所有可能元素的值 */
#define MINDATA -10001
#define ERROR -999999 /* 错误标识应根据具体情况定义为堆中不可能出现的元素值 */

//创建堆 
MaxHeap CreateMaxHeap( int MaxSize );
MinHeap CreateMinHeap( int MaxSize );

bool IsFull( Heap H );
bool IsEmpty( Heap H );

//向堆中插入 
bool MaxInsert( MaxHeap H, ElementType X );
bool MinInsert( MinHeap H, ElementType X);

//删除堆中的根节点 
ElementType DeleteMax( MaxHeap H );
ElementType DeleteMin( MinHeap H );

//将一个完全二叉树变成一个最大堆 
void MaxPercDown( MaxHeap H, int p );
void BuildMaxHeap( MaxHeap H );

// 将一个完全二叉树变成一个最小堆 
void MinPercDown( MinHeap H, int p );
void BuildMinHeap( MaxHeap H );
#endif
