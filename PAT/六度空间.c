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


#define MaxVertexNum 10000    /* ��󶥵�����Ϊ10000 */
typedef int Vertex;         /* �ö����±��ʾ����,Ϊ���� */
typedef int WeightType;        /* �ߵ�Ȩֵ��Ϊ���� */
typedef char DataType;        /* ����洢������������Ϊ�ַ��� */
  
/* �ߵĶ��� */
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;      /* �����<V1, V2> */
    WeightType Weight;  /* Ȩ�� */
};
typedef PtrToENode Edge;
  
/* �ڽӵ�Ķ��� */
typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;        /* �ڽӵ��±� */
    WeightType Weight;  /* ��Ȩ�� */
    PtrToAdjVNode Next;    /* ָ����һ���ڽӵ��ָ�� */
};
  
/* �����ͷ���Ķ��� */
typedef struct Vnode{
    PtrToAdjVNode FirstEdge;/* �߱�ͷָ�� */
} AdjList[MaxVertexNum];    /* AdjList���ڽӱ����� */
  
/* ͼ���Ķ��� */
typedef struct GNode *PtrToGNode;
struct GNode{  
    int Nv;     /* ������ */
    int Ne;     /* ����   */
    AdjList G;  /* �ڽӱ� */
};
typedef PtrToGNode LGraph; /* ���ڽӱ�ʽ�洢��ͼ���� */
  
  
  
LGraph CreateGraph( int VertexNum )
{ /* ��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ */
    Vertex V;
    LGraph Graph;
      
    Graph = (LGraph)malloc( sizeof(struct GNode) ); /* ����ͼ */
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    /* ��ʼ���ڽӱ�ͷָ�� */
    /* ע�⣺����Ĭ�϶����Ŵ�0��ʼ����(Graph->Nv - 1) */
       for (V=0; V<Graph->Nv; V++)
        Graph->G[V].FirstEdge = NULL;
              
    return Graph; 
}
         
void InsertEdge( LGraph Graph, Edge E )
{
    PtrToAdjVNode NewNode;
      
    /* ����� <V1, V2> */
    /* ΪV2�����µ��ڽӵ� */
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;
    /* ��V2����V1�ı�ͷ */
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;
          
    /* ��������ͼ����Ҫ����� <V2, V1> */
    /* ΪV1�����µ��ڽӵ� */
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    NewNode->Weight = E->Weight;
    /* ��V1����V2�ı�ͷ */
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}
  
LGraph BuildGraph()
{
    LGraph Graph;
    Edge E;
    Vertex V;
    int Nv, i;
      
    scanf("%d", &Nv);   /* ���붥����� */
    Graph = CreateGraph(Nv); /* ��ʼ����Nv�����㵫û�бߵ�ͼ */ 
      
    scanf("%d", &(Graph->Ne));   /* ������� */
    if ( Graph->Ne != 0 ) { /* ����б� */ 
        E = (Edge)malloc( sizeof(struct ENode) ); /* �����߽�� */ 
        /* ����ߣ���ʽΪ"��� �յ� Ȩ��"�������ڽӾ��� */
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

/*��¼�ڵ��Ƿ񱻷��ʹ�������*/ 
bool Visited[MaxVertexNum*MaxVertexNum];


/*�������*/ 
int BFS ( LGraph Graph, Vertex V)
{   
    Queue Q;     
    PtrToAdjVNode W;
    int count = 1;
  	Vertex level = 0,last = V,tail;
    InitializeQueue(&Q);
    Visited[V] = true; /* ���V�ѷ��� */
    EnQueue(V,&Q); /* S����� */
      
    while ( !QueueIsEmpty(&Q) ) {
        DeQueue(&V,&Q);  
        for( W=Graph->G[V].FirstEdge; W; W=W->Next ){
            /* ��W��V���ڽӵ㲢��δ���ʹ� */
            if ( !Visited[W->AdjV] ) {
                /* ���ʶ���W */
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

