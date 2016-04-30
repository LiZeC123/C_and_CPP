/*�ڽӾ����ʾ��ͼ*/ 
#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"               /*���������Ҫ�ṩ�������صĺ���*/
#include <stdbool.h> 

#define MaxVertexNum 100         /* ��󶥵�����Ϊ100 */
#define INFINITY 65535           /* ����Ϊ˫�ֽ��޷������������ֵ65535*/
typedef int Vertex;              /* �ö����±��ʾ����,Ϊ���� */
typedef int WeightType;          /* �ߵ�Ȩֵ��Ϊ���� */
typedef char DataType;           /* ����洢������������Ϊ�ַ��� */
  
/* �ߵĶ��� */
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;      /* �����<V1, V2> */
    WeightType Weight;  /* Ȩ�� */
};
typedef PtrToENode Edge;
         
/* ͼ���Ķ��� */
typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;  /* ������ */
    int Ne;  /* ����   */
    WeightType G[MaxVertexNum][MaxVertexNum];    /* �ڽӾ��� */
    DataType Data[MaxVertexNum];                 /* �涥������� */
    /* ע�⣺�ܶ�����£����������ݣ���ʱData[]���Բ��ó��� */
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
    Vertex V;
    int Nv, i;
      
    scanf("%d", &Nv);   /* ���붥����� */
    Graph = CreateGraph(Nv); /* ��ʼ����Nv�����㵫û�бߵ�ͼ */ 
      
    scanf("%d", &(Graph->Ne));   /* ������� */
    if ( Graph->Ne != 0 ) { /* ����б� */ 
        E = (Edge)malloc(sizeof(struct ENode)); /* �����߽�� */ 
        /* ����ߣ���ʽΪ"��� �յ� Ȩ��"�������ڽӾ��� */
        for (i=0; i<Graph->Ne; i++) {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight); 
            /* ע�⣺���Ȩ�ز������ͣ�Weight�Ķ����ʽҪ�� */
            InsertEdge( Graph, E );
        }
    } 
  
    /* ������������ݵĻ����������� */
    for (V=0; V<Graph->Nv; V++) 
        scanf(" %c", &(Graph->Data[V]));
  
    return Graph;
}



  
/*���<V, W>�Ƿ�ͼGraph�е�һ���ߣ���W�Ƿ�V���ڽӵ㡣  */
/* �������Ȩͼ, ��������ڵı߱���ʼ��ΪINFINITY�����ж��Ƿ�С��          */
/* ������Ȩͼ�������ж��Ƿ�Ϊ1����, ����ʵ������                         */ 
bool IsEdge( MGraph Graph, Vertex V, Vertex W )
{
    return Graph->G[V][W]== 1 ? true : false;
}


/*��¼�ڵ��Ƿ񱻷��ʹ�������*/ 
bool Visited[MaxVertexNum*MaxVertexNum];
/*��¼�ڵ��Ƿ񱻴�ӡ��������*/ 
bool Printed[MaxVertexNum];

/*�������*/ 
void BFS ( MGraph Graph, Vertex S)
{   
    Queue Q;     
    Vertex V, W;
  
    InitializeQueue(&Q);
    /* ���ʶ���S���˴��ɸ��ݾ��������Ҫ��д */
    printf("% d",S);
    Printed[S] = true; /*�����б�ʾ�ýڵ��ѱ����*/
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
                Visited[W] = true; 
                EnQueue(W,&Q); /* W����� */
            }
    }
}
/*�������*/
void DFS( MGraph Graph, Vertex V)
{   
    Vertex W;
      
    printf("% d",V);
    Printed[V] = true;
    Visited[V] = true; 
  
    for( W=0; W<Graph->Nv ; W++) 
        if ( !Visited[W] && IsEdge(Graph, V, W))    /* ��δ������ */
            DFS( Graph, W );    /* ��ݹ����֮ */
}


/*���ֱ����㷨�ļ�ʹ��*/ 
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


