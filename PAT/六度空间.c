#include <stdbool.h>
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
/*#############################################Queue.h##############################################3*/
#include <stdio.h>
#include <stdlib.h>


#define MaxVertexNum 10000    /* 最大顶点数设为10000 */
typedef int Vertex;         /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;        /* 边的权值设为整型 */
typedef char DataType;        /* 顶点存储的数据类型设为字符型 */
  
/* 边的定义 */
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;      /* 有向边<V1, V2> */
    WeightType Weight;  /* 权重 */
};
typedef PtrToENode Edge;
  
/* 邻接点的定义 */
typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;        /* 邻接点下标 */
    WeightType Weight;  /* 边权重 */
    PtrToAdjVNode Next;    /* 指向下一个邻接点的指针 */
};
  
/* 顶点表头结点的定义 */
typedef struct Vnode{
    PtrToAdjVNode FirstEdge;/* 边表头指针 */
} AdjList[MaxVertexNum];    /* AdjList是邻接表类型 */
  
/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode{  
    int Nv;     /* 顶点数 */
    int Ne;     /* 边数   */
    AdjList G;  /* 邻接表 */
};
typedef PtrToGNode LGraph; /* 以邻接表方式存储的图类型 */
  
  
  
LGraph CreateGraph( int VertexNum )
{ /* 初始化一个有VertexNum个顶点但没有边的图 */
    Vertex V;
    LGraph Graph;
      
    Graph = (LGraph)malloc( sizeof(struct GNode) ); /* 建立图 */
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    /* 初始化邻接表头指针 */
    /* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
       for (V=0; V<Graph->Nv; V++)
        Graph->G[V].FirstEdge = NULL;
              
    return Graph; 
}
         
void InsertEdge( LGraph Graph, Edge E )
{
    PtrToAdjVNode NewNode;
      
    /* 插入边 <V1, V2> */
    /* 为V2建立新的邻接点 */
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;
    /* 将V2插入V1的表头 */
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;
          
    /* 若是无向图，还要插入边 <V2, V1> */
    /* 为V1建立新的邻接点 */
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    NewNode->Weight = E->Weight;
    /* 将V1插入V2的表头 */
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}
  
LGraph BuildGraph()
{
    LGraph Graph;
    Edge E;
    Vertex V;
    int Nv, i;
      
    scanf("%d", &Nv);   /* 读入顶点个数 */
    Graph = CreateGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */ 
      
    scanf("%d", &(Graph->Ne));   /* 读入边数 */
    if ( Graph->Ne != 0 ) { /* 如果有边 */ 
        E = (Edge)malloc( sizeof(struct ENode) ); /* 建立边结点 */ 
        /* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
        for (i=0; i<Graph->Ne; i++) {
            scanf("%d %d", &E->V1, &E->V2); 
            E->V1--;
            E->V2--;
            E->Weight = 1;
            InsertEdge( Graph, E );
        }
    } 
  
    return Graph;
}

/*记录节点是否被访问过的数组*/ 
bool Visited[MaxVertexNum*MaxVertexNum];


/*宽度优先*/ 
int BFS ( LGraph Graph, Vertex V)
{   
    Queue Q;     
    PtrToAdjVNode W;
    int count = 1;
  	Vertex level = 0,last = V,tail;
    InitializeQueue(&Q);
    Visited[V] = true; /* 标记V已访问 */
    EnQueue(V,&Q); /* S入队列 */
      
    while ( !QueueIsEmpty(&Q) ) {
        DeQueue(&V,&Q);  
        for( W=Graph->G[V].FirstEdge; W; W=W->Next ){
            /* 若W是V的邻接点并且未访问过 */
            if ( !Visited[W->AdjV] ) {
                /* 访问顶点W */
                Visited[W->AdjV] = true;
				count++; 
                EnQueue(W->AdjV,&Q); 
                tail = W->AdjV;
            }
        }
        if(V == last){
        	level++;
        	last = tail;
		}
		if(level == 6){
			break;
		}
		
    }
    return count;
}




int main(void){
	LGraph Graph;
	Graph = BuildGraph();
	int count;
	double rate;
	for(int S=0;S<Graph->Nv;S++){
		
		for(int i=0;i<MaxVertexNum*MaxVertexNum;i++){
			Visited[i] = false;
		}
		count =BFS(Graph,S);
		rate = ((double)count / Graph->Nv) * 100;
		printf("%d: %.2f%%%\n",S+1,rate);
	}	
} 



/*###############################################QUEUE.c#############################*/
void InitializeQueue(Queue * pq){
	pq->front=NULL;
	pq->rear=NULL;
	pq->items=0; 
}

bool QueueIsFull(const Queue * pq){
	return false; 
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

