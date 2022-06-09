#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxVertexNum 15    /* 最大顶点数设为100 */
#define INFINITY 65535        /* ∞设为双字节无符号整数的最大值65535*/
typedef int Vertex;         /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;        /* 边的权值设为整型 */
typedef char DataType;        /* 顶点存储的数据类型设为字符型 */
  
/* 边的定义 */

struct ENode{
    Vertex V1, V2;      /* 有向边<V1, V2> */
    WeightType Weight;  /* 权重 */
};
typedef struct ENode *PtrToENode;
typedef PtrToENode Edge;
         
/* 图结点的定义 */

struct GNode{
    int Nv;  /* 顶点数 */
    int Ne;  /* 边数   */
    WeightType G[MaxVertexNum][MaxVertexNum]; /* 邻接矩阵 */
    DataType Data[MaxVertexNum];      /* 存顶点的数据 */
    /* 注意：很多情况下，顶点无数据，此时Data[]可以不用出现 */
};
typedef struct GNode *PtrToGNode;

typedef PtrToGNode MGraph; /* 以邻接矩阵存储的图类型 */
  
  
  
MGraph CreateGraph( int VertexNum )
{ /* 初始化一个有VertexNum个顶点但没有边的图 */
    Vertex V, W;
    MGraph Graph;
      
    Graph = (MGraph)malloc(sizeof(struct GNode)); /* 建立图 */
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    /* 初始化邻接矩阵 */
    /* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
    for (V=0; V<Graph->Nv; V++)
        for (W=0; W<Graph->Nv; W++)  
            Graph->G[V][W] = INFINITY;
              
    return Graph; 
}
         
void InsertEdge( MGraph Graph, Edge E )
{
     /* 插入边 <V1, V2> */
     Graph->G[E->V1][E->V2] = E->Weight;    
     /* 若是无向图，还要插入边<V2, V1> */
     Graph->G[E->V2][E->V1] = E->Weight;
}
  
MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    int Nv, i;
      
    scanf("%d", &Nv);   /* 读入顶点个数 */
    Graph = CreateGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */ 
     
    scanf("%d", &(Graph->Ne));   /* 读入边数 */
    if ( Graph->Ne != 0 ) { /* 如果有边 */ 
        E = (Edge)malloc(sizeof(struct ENode)); /* 建立边结点 */         
        E->Weight = 1;
        /* 读入边，格式为"起点 终点"，插入邻接矩阵 */
        for (i=0; i<Graph->Ne; i++) {
            scanf("%d %d", &E->V1, &E->V2); 
            InsertEdge( Graph, E );
        }
    } 
  
    return Graph;
}


/*#################################################QUENE#####################*/
#define MAX_QUENE 100
typedef int Item;
typedef struct node{
	Item item;
	struct node * next;
}Node;

typedef struct quenu{
	Node * front;
	Node * rear;
	int items;
}Queue;
void InitializeQueue(Queue * pq);
bool QueueIsFull(const Queue * pq);
bool QueueIsEmpty(const Queue * pq); 
int QueueItemCount(const Queue * pq);
bool EnQueue(Item item,Queue * pq);
bool DeQueue(Item * pitem,Queue *pq);
void EmptyTheQueue(Queue *pq);
static void CopyToNode(Item item,Node * pn);
static void CopyToItem(Node * pn,Item * pitem);
void InitializeQueue(Queue * pq){
	pq->front=NULL;
	pq->rear=NULL;
	pq->items=0; 
}

bool QueueIsFull(const Queue * pq){
	return pq->items == MAX_QUENE; 
}

bool QueueIsEmpty(const Queue * pq){
	return pq->items == 0;
}
 
 int QueueItemCount(const Queue * pq){
 	return pq->items;
 }
 
 bool EnQueue(Item item,Queue * pq){
 	Node * pnew;
 	if(QueueIsFull(pq)){
 		return false;
	 }
 	pnew = (Node *)malloc(sizeof(Node));
 	if(pnew==NULL){
 		fprintf(stderr,"Unable to allocate memory!\n");
 		exit(1);
	 }
	 
	 pnew->next = NULL;
	 CopyToNode(item,pnew);
	 if(QueueIsEmpty(pq)){
	 	pq->front=pnew;
	 }
	 else{
	 	pq->rear->next=pnew;
	 }
	 pq->rear=pnew;
	 pq->items++;
	 
	 return true;
 }
 
 bool DeQueue(Item * pitem,Queue *pq){
 	Node * psave;
 	if(QueueIsEmpty(pq)){
 		return false;
	 }
	 CopyToItem(pq->front ,pitem);
	 psave=pq->front ;
	 pq->front =pq->front->next;
	 free(psave);
	 pq->items--;
	 if(pq->items == 0){
	 	pq->rear = NULL;
	 }
	 return true;
 }
 
 void EmptyTheQueue(Queue *pq){
 	Item dummy;
 	while(!QueueIsEmpty(pq)){
 		DeQueue(&dummy,pq);
	 }
 }
 
static void CopyToNode(Item item,Node * pn){
	pn->item = item;
}

static void CopyToItem(Node * pn,Item * pitem){
	*pitem = pn->item;
}

/*#################################################QUENE#####################*/



bool Visited[MaxVertexNum*MaxVertexNum];
bool Printed[MaxVertexNum];

/* 邻接矩阵存储的图 - BFS */
  
/* IsEdge(Graph, V, W)检查<V, W>是否图Graph中的一条边，即W是否V的邻接点。  */
/* 此函数根据图的不同类型要做不同的实现，关键取决于对不存在的边的表示方法。*/
/* 例如对有权图, 如果不存在的边被初始化为INFINITY, 则函数实现如下:         */
bool IsEdge( MGraph Graph, Vertex V, Vertex W )
{
    return Graph->G[V][W] == 1 ? true : false;
}
  
/* Visited[]为全局变量，已经初始化为false */
void BFS ( MGraph Graph, Vertex S)
{   /* 以S为出发点对邻接矩阵存储的图Graph进行BFS搜索 */
    Queue Q;     
    Vertex V, W;
  
    InitializeQueue(&Q);
    /* 访问顶点S：此处可根据具体访问需要改写 */
    printf("% d",S);
    Printed[S] = true; 
    Visited[S] = true; /* 标记S已访问 */
    EnQueue(S,&Q); /* S入队列 */
      
    while ( !QueueIsEmpty(&Q) ) {
        DeQueue(&V,&Q);  /* 弹出V */
        for( W=0; W<Graph->Nv; W++ ) /* 对图中的每个顶点W */
            /* 若W是V的邻接点并且未访问过 */
            if ( !Visited[W] && IsEdge(Graph, V, W) ) {
                /* 访问顶点W */
                printf("% d",W);
                Printed[W] = true; 
                Visited[W] = true; /* 标记W已访问 */
                EnQueue(W,&Q); /* W入队列 */
            }
    }
}

void DFS( MGraph Graph, Vertex V)
{   /* 以V为出发点对邻接表存储的图Graph进行DFS搜索 */
    Vertex W;
      
    printf("% d",V);
    Printed[V] = true;
    Visited[V] = true; /* 标记V已访问 */
  
    for( W=0; W<Graph->Nv ; W++) 
        if ( !Visited[W] && IsEdge(Graph, V, W))    /* 若未被访问 */
            DFS( Graph, W );    /* 则递归访问之 */
}


int main(void){
	MGraph Graph;
	Graph = BuildGraph();
	for(int i=0;i<MaxVertexNum;i++){
		Printed[i] = false;
	}
	for(int S=0;S<Graph->Nv;S++){
		if(!Printed[S]){
			for(int i=0;i<MaxVertexNum*MaxVertexNum;i++){
				Visited[i] = false;
			}
			putchar('{');
			DFS(Graph,S);
			printf(" }\n");
		}
	}	
	for(int i=0;i<MaxVertexNum;i++){
		Printed[i] = false;
	}
	for(int S=0;S<Graph->Nv;S++){
		if(!Printed[S]){
			for(int i=0;i<MaxVertexNum*MaxVertexNum;i++){
				Visited[i] = false;
			}
			putchar('{');
			BFS(Graph,S);
			printf(" }\n");
		}
	}	
	return 0;
} 




