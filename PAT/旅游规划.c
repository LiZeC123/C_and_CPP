/*邻接矩阵表示的图*/ 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

#define MaxVertexNum 500         /* 最大顶点数设为500 */
#define INFINITY 65535           /* ∞设为双字节无符号整数的最大值65535*/
#define ERROR -5
typedef int Vertex;              /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;          /* 边的权值设为整型 */
int S,D;						/* 起点和终点 */

/* 边的定义 */
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;      /* 有向边<V1, V2> */
    WeightType len;  
    WeightType rate;
};
typedef PtrToENode Edge;
         
/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;  /* 顶点数 */
    int Ne;  /* 边数   */
    WeightType L[MaxVertexNum][MaxVertexNum];    /* 邻接矩阵路径权值 */
    WeightType R[MaxVertexNum][MaxVertexNum];	/* 邻接矩阵费用权值 */
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
            Graph->L[V][W] = INFINITY;
            Graph->R[V][W] = INFINITY;
    return Graph; 
}
         
void InsertEdge( MGraph Graph, Edge E )
{
     /* 插入边  */
     Graph->L[E->V1][E->V2] = E->len;    
     Graph->L[E->V2][E->V1] = E->len;
     Graph->R[E->V1][E->V2] = E->rate;
     Graph->R[E->V2][E->V1] = E->rate;
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
    
    scanf("%d",&S);/* 读入起点和终点 */
    scanf("%d",&D);
    if ( Graph->Ne != 0 ) { /* 如果有边 */ 
        E = (Edge)malloc(sizeof(struct ENode)); /* 建立边结点 */ 
        /* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
        for (i=0; i<Graph->Ne; i++) {
            scanf("%d %d %d %d", &E->V1, &E->V2, &E->len,&E->rate); 
            /* 注意：如果权重不是整型，Weight的读入格式要改 */
            InsertEdge( Graph, E );
        }
    } 
    
    return Graph;
}

 
/* 邻接矩阵存储 - 有权图的单源最短路算法 */
 
Vertex FindMinDist( MGraph Graph, int dist[], int collected[] )
{ /* 返回未被收录顶点中dist最小者 */
    Vertex MinV, V;
    int MinDist = INFINITY;
 
    for (V=0; V<Graph->Nv; V++) {
        if ( collected[V]==false && dist[V]<MinDist) {
            /* 若V未被收录，且dist[V]更小 */
            MinDist = dist[V]; /* 更新最小距离 */
            MinV = V; /* 更新对应顶点 */
        }
    }
    if (MinDist < INFINITY) /* 若找到最小dist */
        return MinV; /* 返回对应的顶点下标 */
    else return ERROR;  /* 若这样的顶点不存在，返回错误标记 */
}
 
bool Dijkstra( MGraph Graph, int dist[], int rate[],int path[], Vertex S )
{
    int collected[MaxVertexNum];
    Vertex V, W;
 
    /* 初始化：此处默认邻接矩阵中不存在的边用INFINITY表示 */
    for ( V=0; V<Graph->Nv; V++ ) {
        dist[V] = Graph->L[S][V];
        rate[V] = Graph->R[S][V];
        path[V] = -1;
        collected[V] = false;
    }
    /* 先将起点收入集合 */
    dist[S] = 0;
    rate[V] = 0;
    collected[S] = true;
 
    while (1) {
        /* V = 未被收录顶点中dist最小者 */
        V = FindMinDist( Graph, dist, collected );
        if ( V==ERROR ) /* 若这样的V不存在 */
            break;      /* 算法结束 */
        collected[V] = true;  /* 收录V */
        for( W=0; W<Graph->Nv; W++ ) /* 对图中的每个顶点W */
            /* 若W是V的邻接点并且未被收录 */
            if ( collected[W]==false && Graph->L[V][W]<INFINITY ) {
                if ( dist[V]+Graph->L[V][W] < dist[W] ) {
                    dist[W] = dist[V]+Graph->L[V][W]; 
                    rate[W] = rate[V]+Graph->R[V][W];
                    path[W] = V; 
                }
                else if( dist[V]+Graph->L[V][W] == dist[W] && rate[V]+Graph->R[V][W] < rate[W] ) {
                    rate[W] = rate[V]+Graph->R[V][W];
                    path[W] = V; 
				}
            }
    } /* while结束*/
    return true; /* 算法执行完毕，返回正确标记 */
}



/*但是如果有多个等价的路线，则都要输出*/
int main(void){
	MGraph Graph;
	Graph = BuildGraph();

	int dist[MaxVertexNum];//点S到V的最短距离 
	int rate[MaxVertexNum];
	int path[MaxVertexNum];//点V的最短路径上前一个点的值 
	int answer[MaxVertexNum];
	int answer_edx = 0;
	Dijkstra(Graph,dist,rate,path,S);

	printf("%d %d",dist[D],rate[D]);
	return 0;
} 


