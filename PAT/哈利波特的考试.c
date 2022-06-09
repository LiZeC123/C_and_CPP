/*�ڽӾ����ʾ��ͼ*/ 
#include <stdio.h>
#include <stdlib.h>
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
    int Nv, i;
      
    scanf("%d", &Nv);   /* ���붥����� */
    Graph = CreateGraph(Nv); /* ��ʼ����Nv�����㵫û�бߵ�ͼ */ 
      
    scanf("%d", &(Graph->Ne));   /* ������� */
    if ( Graph->Ne != 0 ) { /* ����б� */ 
        E = (Edge)malloc(sizeof(struct ENode)); /* �����߽�� */ 
        /* ����ߣ���ʽΪ"��� �յ� Ȩ��"�������ڽӾ��� */
        for (i=0; i<Graph->Ne; i++) {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight); 
            //���ݴ洢��0��ʼ 
            E->V1--;
            E->V2--;
            InsertEdge( Graph, E );
        }
    } 
  
    return Graph;
}



  
/*���<V, W>�Ƿ�ͼGraph�е�һ���ߣ���W�Ƿ�V���ڽӵ㡣  */
/* �������Ȩͼ, ��������ڵı߱���ʼ��ΪINFINITY�����ж��Ƿ�С��          */
/* ������Ȩͼ�������ж��Ƿ�Ϊ1����, ����ʵ������                         */ 
bool IsEdge( MGraph Graph, Vertex V, Vertex W )
{
    return Graph->G[V][W] < INFINITY ? true : false;
}

/* �ڽӾ���洢 - ��Դ���·�㷨 */
 
void Floyd( MGraph Graph, WeightType D[][MaxVertexNum] )
{
    Vertex i, j, k;
 
    /* ��ʼ�� */
    for ( i=0; i<Graph->Nv; i++ )
        for( j=0; j<Graph->Nv; j++ ) {
            D[i][j] = Graph->G[i][j];
        }
 
    for( k=0; k<Graph->Nv; k++ )
        for( i=0; i<Graph->Nv; i++ )
            for( j=0; j<Graph->Nv; j++ )
                if( D[i][k] + D[k][j] < D[i][j] ) {
                    D[i][j] = D[i][k] + D[k][j];
                }
}

WeightType FindMaxDist(WeightType D[][MaxVertexNum],Vertex i,int N)
{
	WeightType MaxDist;
	Vertex j;
	
	MaxDist = 0;
	for(j=0;j<N;j++){
		if( i!=j && D[i][j] > MaxDist)
			MaxDist = D[i][j];
	}
	return MaxDist;
}


void FindAnimal(MGraph Graph)
{	WeightType D[MaxVertexNum][MaxVertexNum];
	WeightType MaxDist,MinDist;
	Vertex Animal;
	
	Floyd(Graph,D);
	
	MinDist = INFINITY;
	for(Vertex i=0;i<Graph->Nv;i++){
		MaxDist = FindMaxDist(D,i,Graph->Nv);
		if(MaxDist == INFINITY){
			printf("0\n");
			return;
		} 
		
		if(MinDist > MaxDist){
			MinDist = MaxDist;
			Animal = i+1;  //�����һ��ʼ��� 
		}
	}
	printf("%d %d\n",Animal,MinDist);
} 


int main(void){
	MGraph Graph;
	Graph = BuildGraph();
	
	FindAnimal( Graph );

	return 0;
} 


