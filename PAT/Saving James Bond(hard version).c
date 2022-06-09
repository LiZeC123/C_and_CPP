#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INSTAND_DISTANCE 7.5
#define	ERROR -5   //错误表示 
typedef struct{
	int x;
	int y;
}Location;

typedef int PointLocation;


/*邻接矩阵表示的图*/ 

#define MaxVertexNum 101         /* 最大顶点数设为101 */
#define INFINITY 65535           /* ∞设为双字节无符号整数的最大值65535*/
typedef int Vertex;              /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;          /* 边的权值设为整型 */
  
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

};
typedef PtrToGNode MGraph; /* 以邻接矩阵存储的图类型 */

static Vertex FindMinDist( MGraph Graph, int dist[], int collected[] );
void Dijkstra( MGraph Graph, int dist[], int path[], Vertex S );
  
static MGraph CreateGraph( int VertexNum );      
static void InsertEdge( MGraph Graph, Edge E );
MGraph BuildGraph();


bool Jump(PointLocation A,PointLocation B);
bool FirstJump(PointLocation A,PointLocation B);
bool IsSave(PointLocation A);
Location Data[MaxVertexNum];
bool SaveList[MaxVertexNum];

int distance;//跳跃半径 

bool IsEdge( MGraph Graph, Vertex V, Vertex W )
{
    return Graph->G[V][W] < INFINITY ? true : false;
}


int main(void){
	MGraph Graph;
	Graph = BuildGraph();
	
	int dist[MaxVertexNum];//点S到V的最短距离 
	int path[MaxVertexNum];//点V的最短路径上前一个点的值 
	
	
	int MinDist = INFINITY;
	Vertex S,D;//起始点和终点 
	for(Vertex i=0;i<Graph->Nv;i++){
		if(FirstJump(i,Graph->Nv)){
			Dijkstra(Graph,dist,path,i);
			for(Vertex j=0;j<Graph->Nv;j++){
				if(SaveList[j] && dist[j]<MinDist){
					MinDist = dist[j];
					S = i;
					D = j; 
				} 		
			}
		} 
	} 
	if(distance > 42.5){
		printf("1");
		return 0;
	}
	if(MinDist != INFINITY){
		printf("%d\n",MinDist+2);
	
		Dijkstra(Graph,dist,path,S);
	
		int answer[MaxVertexNum];
		int edx = 0;
		int DtoS = D;
		while(DtoS != -1){
			answer[edx] = DtoS;
			edx++;
			DtoS = path[DtoS];
		}
		printf("%d %d\n",Data[S].x,Data[S].y);
		
		while(edx--){
			printf("%d %d\n",Data[answer[edx]].x,Data[answer[edx]].y);
		}
	}
	else{
		printf("0");
	}
	return 0;
}

//判断能否跳跃 
bool Jump(PointLocation A,PointLocation B)
{
	return (Data[A].x-Data[B].x)*(Data[A].x-Data[B].x) + (Data[A].y-Data[B].y)*(Data[A].y-Data[B].y)
				<= distance*distance;
			    
}
//判断该点是否安全 
bool IsSave(PointLocation A){
	return (50 - abs(Data[A].x) <= distance) || (50 -abs(Data[A].y) <= distance);
}

bool FirstJump(PointLocation A,PointLocation B){
	return (Data[A].x-Data[B].x)*(Data[A].x-Data[B].x)
			    +  (Data[A].y-Data[B].y)*(Data[A].y-Data[B].y) <= 
					(distance+INSTAND_DISTANCE)*(distance+INSTAND_DISTANCE);
}


static MGraph CreateGraph( int VertexNum )
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

static void InsertEdge( MGraph Graph, Edge E )
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
    scanf("%d",&distance); //读入跳跃半径
    
    /* 读入坐标信息,Data是定义的全局数组*/
	for(int i=0;i<Nv;i++){
		scanf("%d %d",&Data[i].x,&Data[i].y);
	}
	//保存原点信息 
	Data[Nv].x = 0;
	Data[Nv].y = 0;
	
	//创建边
	E = (PtrToENode)malloc(sizeof(struct ENode));
    
    for(int i=0;i<Nv;i++){
    	for(int j=0;j<Nv;j++){
    		if(i!=j && Jump(i,j)){
    			E->V1 = i;
    			E->V2 = j;
    			E->Weight = 1;
    			InsertEdge( Graph, E );
			}
		}
		
		if(IsSave(i))
			SaveList[i] = true;
		else
			SaveList[i] = false;
	}
	
    return Graph;
}

/* 邻接矩阵存储 - 有权图的单源最短路算法 */
 
static Vertex FindMinDist( MGraph Graph, int dist[], int collected[] )
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
 
void Dijkstra( MGraph Graph, int dist[], int path[], Vertex S )
{
    int collected[MaxVertexNum];
    Vertex V, W;
 
    /* 初始化：此处默认邻接矩阵中不存在的边用INFINITY表示 */
    for ( V=0; V<Graph->Nv; V++ ) {
        dist[V] = Graph->G[S][V];
        path[V] = -1;
        collected[V] = false;
    }
    /* 先将起点收入集合 */
    dist[S] = 0;
    collected[S] = true;
 
    while (1) {
        /* V = 未被收录顶点中dist最小者 */
        V = FindMinDist( Graph, dist, collected );
        if ( V==ERROR ) /* 若这样的V不存在 */
            break;      /* 算法结束 */
        collected[V] = true;  /* 收录V */
        for( W=0; W<Graph->Nv; W++ ) /* 对图中的每个顶点W */
            /* 若W是V的邻接点并且未被收录 */
            if ( collected[W]==false && Graph->G[V][W]<INFINITY ) {
                /* 若收录V使得dist[W]变小 */
                if ( dist[V]+Graph->G[V][W] < dist[W] ) {
                    dist[W] = dist[V]+Graph->G[V][W]; /* 更新dist[W] */
                    path[W] = V; /* 更新S到W的路径 */
                }
            }
    }
}
