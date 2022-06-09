#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxVertexNum 15    /* ��󶥵�����Ϊ100 */
#define INFINITY 65535        /* ����Ϊ˫�ֽ��޷������������ֵ65535*/
typedef int Vertex;         /* �ö����±��ʾ����,Ϊ���� */
typedef int WeightType;        /* �ߵ�Ȩֵ��Ϊ���� */
typedef char DataType;        /* ����洢������������Ϊ�ַ��� */
  
/* �ߵĶ��� */

struct ENode{
    Vertex V1, V2;      /* �����<V1, V2> */
    WeightType Weight;  /* Ȩ�� */
};
typedef struct ENode *PtrToENode;
typedef PtrToENode Edge;
         
/* ͼ���Ķ��� */

struct GNode{
    int Nv;  /* ������ */
    int Ne;  /* ����   */
    WeightType G[MaxVertexNum][MaxVertexNum]; /* �ڽӾ��� */
    DataType Data[MaxVertexNum];      /* �涥������� */
    /* ע�⣺�ܶ�����£����������ݣ���ʱData[]���Բ��ó��� */
};
typedef struct GNode *PtrToGNode;

typedef PtrToGNode MGraph; /* ���ڽӾ���洢��ͼ���� */
  
  
  
MGraph CreateGraph( int VertexNum )
{ /* ��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ */
    Vertex V, W;
    MGraph Graph;
      
    Graph = (MGraph)malloc(sizeof(struct GNode)); /* ����ͼ */
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    /* ��ʼ���ڽӾ��� */
    /* ע�⣺����Ĭ�϶����Ŵ�0��ʼ����(Graph->Nv - 1) */
    for (V=0; V<Graph->Nv; V++)
        for (W=0; W<Graph->Nv; W++)  
            Graph->G[V][W] = INFINITY;
              
    return Graph; 
}
         
void InsertEdge( MGraph Graph, Edge E )
{
     /* ����� <V1, V2> */
     Graph->G[E->V1][E->V2] = E->Weight;    
     /* ��������ͼ����Ҫ�����<V2, V1> */
     Graph->G[E->V2][E->V1] = E->Weight;
}
  
MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    int Nv, i;
      
    scanf("%d", &Nv);   /* ���붥����� */
    Graph = CreateGraph(Nv); /* ��ʼ����Nv�����㵫û�бߵ�ͼ */ 
     
    scanf("%d", &(Graph->Ne));   /* ������� */
    if ( Graph->Ne != 0 ) { /* ����б� */ 
        E = (Edge)malloc(sizeof(struct ENode)); /* �����߽�� */         
        E->Weight = 1;
        /* ����ߣ���ʽΪ"��� �յ�"�������ڽӾ��� */
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

/* �ڽӾ���洢��ͼ - BFS */
  
/* IsEdge(Graph, V, W)���<V, W>�Ƿ�ͼGraph�е�һ���ߣ���W�Ƿ�V���ڽӵ㡣  */
/* �˺�������ͼ�Ĳ�ͬ����Ҫ����ͬ��ʵ�֣��ؼ�ȡ���ڶԲ����ڵıߵı�ʾ������*/
/* �������Ȩͼ, ��������ڵı߱���ʼ��ΪINFINITY, ����ʵ������:         */
bool IsEdge( MGraph Graph, Vertex V, Vertex W )
{
    return Graph->G[V][W] == 1 ? true : false;
}
  
/* Visited[]Ϊȫ�ֱ������Ѿ���ʼ��Ϊfalse */
void BFS ( MGraph Graph, Vertex S)
{   /* ��SΪ��������ڽӾ���洢��ͼGraph����BFS���� */
    Queue Q;     
    Vertex V, W;
  
    InitializeQueue(&Q);
    /* ���ʶ���S���˴��ɸ��ݾ��������Ҫ��д */
    printf("% d",S);
    Printed[S] = true; 
    Visited[S] = true; /* ���S�ѷ��� */
    EnQueue(S,&Q); /* S����� */
      
    while ( !QueueIsEmpty(&Q) ) {
        DeQueue(&V,&Q);  /* ����V */
        for( W=0; W<Graph->Nv; W++ ) /* ��ͼ�е�ÿ������W */
            /* ��W��V���ڽӵ㲢��δ���ʹ� */
            if ( !Visited[W] && IsEdge(Graph, V, W) ) {
                /* ���ʶ���W */
                printf("% d",W);
                Printed[W] = true; 
                Visited[W] = true; /* ���W�ѷ��� */
                EnQueue(W,&Q); /* W����� */
            }
    }
}

void DFS( MGraph Graph, Vertex V)
{   /* ��VΪ��������ڽӱ�洢��ͼGraph����DFS���� */
    Vertex W;
      
    printf("% d",V);
    Printed[V] = true;
    Visited[V] = true; /* ���V�ѷ��� */
  
    for( W=0; W<Graph->Nv ; W++) 
        if ( !Visited[W] && IsEdge(Graph, V, W))    /* ��δ������ */
            DFS( Graph, W );    /* ��ݹ����֮ */
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




