/*�ڽӾ����ʾ��ͼ*/ 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

#define MaxVertexNum 500         /* ��󶥵�����Ϊ500 */
#define INFINITY 65535           /* ����Ϊ˫�ֽ��޷������������ֵ65535*/
#define ERROR -5
typedef int Vertex;              /* �ö����±��ʾ����,Ϊ���� */
typedef int WeightType;          /* �ߵ�Ȩֵ��Ϊ���� */
int S,D;						/* �����յ� */

/* �ߵĶ��� */
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;      /* �����<V1, V2> */
    WeightType len;  
    WeightType rate;
};
typedef PtrToENode Edge;
         
/* ͼ���Ķ��� */
typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;  /* ������ */
    int Ne;  /* ����   */
    WeightType L[MaxVertexNum][MaxVertexNum];    /* �ڽӾ���·��Ȩֵ */
    WeightType R[MaxVertexNum][MaxVertexNum];	/* �ڽӾ������Ȩֵ */
};
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
            Graph->L[V][W] = INFINITY;
            Graph->R[V][W] = INFINITY;
    return Graph; 
}
         
void InsertEdge( MGraph Graph, Edge E )
{
     /* �����  */
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
      
    scanf("%d", &Nv);   /* ���붥����� */
    Graph = CreateGraph(Nv); /* ��ʼ����Nv�����㵫û�бߵ�ͼ */ 
      
    scanf("%d", &(Graph->Ne));   /* ������� */
    
    scanf("%d",&S);/* ���������յ� */
    scanf("%d",&D);
    if ( Graph->Ne != 0 ) { /* ����б� */ 
        E = (Edge)malloc(sizeof(struct ENode)); /* �����߽�� */ 
        /* ����ߣ���ʽΪ"��� �յ� Ȩ��"�������ڽӾ��� */
        for (i=0; i<Graph->Ne; i++) {
            scanf("%d %d %d %d", &E->V1, &E->V2, &E->len,&E->rate); 
            /* ע�⣺���Ȩ�ز������ͣ�Weight�Ķ����ʽҪ�� */
            InsertEdge( Graph, E );
        }
    } 
    
    return Graph;
}

 
/* �ڽӾ���洢 - ��Ȩͼ�ĵ�Դ���·�㷨 */
 
Vertex FindMinDist( MGraph Graph, int dist[], int collected[] )
{ /* ����δ����¼������dist��С�� */
    Vertex MinV, V;
    int MinDist = INFINITY;
 
    for (V=0; V<Graph->Nv; V++) {
        if ( collected[V]==false && dist[V]<MinDist) {
            /* ��Vδ����¼����dist[V]��С */
            MinDist = dist[V]; /* ������С���� */
            MinV = V; /* ���¶�Ӧ���� */
        }
    }
    if (MinDist < INFINITY) /* ���ҵ���Сdist */
        return MinV; /* ���ض�Ӧ�Ķ����±� */
    else return ERROR;  /* �������Ķ��㲻���ڣ����ش����� */
}
 
bool Dijkstra( MGraph Graph, int dist[], int rate[],int path[], Vertex S )
{
    int collected[MaxVertexNum];
    Vertex V, W;
 
    /* ��ʼ�����˴�Ĭ���ڽӾ����в����ڵı���INFINITY��ʾ */
    for ( V=0; V<Graph->Nv; V++ ) {
        dist[V] = Graph->L[S][V];
        rate[V] = Graph->R[S][V];
        path[V] = -1;
        collected[V] = false;
    }
    /* �Ƚ�������뼯�� */
    dist[S] = 0;
    rate[V] = 0;
    collected[S] = true;
 
    while (1) {
        /* V = δ����¼������dist��С�� */
        V = FindMinDist( Graph, dist, collected );
        if ( V==ERROR ) /* ��������V������ */
            break;      /* �㷨���� */
        collected[V] = true;  /* ��¼V */
        for( W=0; W<Graph->Nv; W++ ) /* ��ͼ�е�ÿ������W */
            /* ��W��V���ڽӵ㲢��δ����¼ */
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
    } /* while����*/
    return true; /* �㷨ִ����ϣ�������ȷ��� */
}



/*��������ж���ȼ۵�·�ߣ���Ҫ���*/
int main(void){
	MGraph Graph;
	Graph = BuildGraph();

	int dist[MaxVertexNum];//��S��V����̾��� 
	int rate[MaxVertexNum];
	int path[MaxVertexNum];//��V�����·����ǰһ�����ֵ 
	int answer[MaxVertexNum];
	int answer_edx = 0;
	Dijkstra(Graph,dist,rate,path,S);

	printf("%d %d",dist[D],rate[D]);
	return 0;
} 


