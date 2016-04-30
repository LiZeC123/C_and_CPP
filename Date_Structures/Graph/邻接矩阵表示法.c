/*邻接矩阵表示的图*/ 
#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"               /*宽度优先需要提供与队列相关的函数*/
#include <stdbool.h> 

#define MaxVertexNum 100         /* 最大顶点数设为100 */
#define INFINITY 65535           /* ∞设为双字节无符号整数的最大值65535*/
typedef int Vertex;              /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;          /* 边的权值设为整型 */
typedef char DataType;           /* 顶点存储的数据类型设为字符型 */
  
/* 边的定义 */
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;      /* 有向边<V1, V2> */
    WeightType Weight;  /* 权重 */
};
typedef PtrToENode Edge;
         
/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;  /* 顶点数 */
    int Ne;  /* 边数   */
    WeightType G[MaxVertexNum][MaxVertexNum];    /* 邻接矩阵 */
    DataType Data[MaxVertexNum];                 /* 存顶点的数据 */
    /* 注意：很多情况下，顶点无数据，此时Data[]可以不用出现 */
};
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
    Vertex V;
    int Nv, i;
      
    scanf("%d", &Nv);   /* 读入顶点个数 */
    Graph = CreateGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */ 
      
    scanf("%d", &(Graph->Ne));   /* 读入边数 */
    if ( Graph->Ne != 0 ) { /* 如果有边 */ 
        E = (Edge)malloc(sizeof(struct ENode)); /* 建立边结点 */ 
        /* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
        for (i=0; i<Graph->Ne; i++) {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight); 
            /* 注意：如果权重不是整型，Weight的读入格式要改 */
            InsertEdge( Graph, E );
        }
    } 
  
    /* 如果顶点有数据的话，读入数据 */
    for (V=0; V<Graph->Nv; V++) 
        scanf(" %c", &(Graph->Data[V]));
  
    return Graph;
}



  
/*检查<V, W>是否图Graph中的一条边，即W是否V的邻接点。  */
/* 例如对有权图, 如果不存在的边被初始化为INFINITY，可判断是否小于          */
/* 对于无权图，可以判断是否为1即可, 则函数实现如下                         */ 
bool IsEdge( MGraph Graph, Vertex V, Vertex W )
{
    return Graph->G[V][W]== 1 ? true : false;
}


/*记录节点是否被访问过的数组*/ 
bool Visited[MaxVertexNum*MaxVertexNum];
/*记录节点是否被打印过的数组*/ 
bool Printed[MaxVertexNum];

/*宽度优先*/ 
void BFS ( MGraph Graph, Vertex S)
{   
    Queue Q;     
    Vertex V, W;
  
    InitializeQueue(&Q);
    /* 访问顶点S：此处可根据具体访问需要改写 */
    printf("% d",S);
    Printed[S] = true; /*本例中表示该节点已被输出*/
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
                Visited[W] = true; 
                EnQueue(W,&Q); /* W入队列 */
            }
    }
}
/*深度优先*/
void DFS( MGraph Graph, Vertex V)
{   
    Vertex W;
      
    printf("% d",V);
    Printed[V] = true;
    Visited[V] = true; 
  
    for( W=0; W<Graph->Nv ; W++) 
        if ( !Visited[W] && IsEdge(Graph, V, W))    /* 若未被访问 */
            DFS( Graph, W );    /* 则递归访问之 */
}


/*两种遍历算法的简单使用*/ 
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


