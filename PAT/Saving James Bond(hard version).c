#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INSTAND_DISTANCE 7.5
#define	ERROR -5   //�����ʾ 
typedef struct{
	int x;
	int y;
}Location;

typedef int PointLocation;


/*�ڽӾ����ʾ��ͼ*/ 

#define MaxVertexNum 101         /* ��󶥵�����Ϊ101 */
#define INFINITY 65535           /* ����Ϊ˫�ֽ��޷������������ֵ65535*/
typedef int Vertex;              /* �ö����±��ʾ����,Ϊ���� */
typedef int WeightType;          /* �ߵ�Ȩֵ��Ϊ���� */
  
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

};
typedef PtrToGNode MGraph; /* ���ڽӾ���洢��ͼ���� */

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

int distance;//��Ծ�뾶 

bool IsEdge( MGraph Graph, Vertex V, Vertex W )
{
    return Graph->G[V][W] < INFINITY ? true : false;
}


int main(void){
	MGraph Graph;
	Graph = BuildGraph();
	
	int dist[MaxVertexNum];//��S��V����̾��� 
	int path[MaxVertexNum];//��V�����·����ǰһ�����ֵ 
	
	
	int MinDist = INFINITY;
	Vertex S,D;//��ʼ����յ� 
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

//�ж��ܷ���Ծ 
bool Jump(PointLocation A,PointLocation B)
{
	return (Data[A].x-Data[B].x)*(Data[A].x-Data[B].x) + (Data[A].y-Data[B].y)*(Data[A].y-Data[B].y)
				<= distance*distance;
			    
}
//�жϸõ��Ƿ�ȫ 
bool IsSave(PointLocation A){
	return (50 - abs(Data[A].x) <= distance) || (50 -abs(Data[A].y) <= distance);
}

bool FirstJump(PointLocation A,PointLocation B){
	return (Data[A].x-Data[B].x)*(Data[A].x-Data[B].x)
			    +  (Data[A].y-Data[B].y)*(Data[A].y-Data[B].y) <= 
					(distance+INSTAND_DISTANCE)*(distance+INSTAND_DISTANCE);
}


static MGraph CreateGraph( int VertexNum )
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

static void InsertEdge( MGraph Graph, Edge E )
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
    scanf("%d",&distance); //������Ծ�뾶
    
    /* ����������Ϣ,Data�Ƕ����ȫ������*/
	for(int i=0;i<Nv;i++){
		scanf("%d %d",&Data[i].x,&Data[i].y);
	}
	//����ԭ����Ϣ 
	Data[Nv].x = 0;
	Data[Nv].y = 0;
	
	//������
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

/* �ڽӾ���洢 - ��Ȩͼ�ĵ�Դ���·�㷨 */
 
static Vertex FindMinDist( MGraph Graph, int dist[], int collected[] )
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
 
void Dijkstra( MGraph Graph, int dist[], int path[], Vertex S )
{
    int collected[MaxVertexNum];
    Vertex V, W;
 
    /* ��ʼ�����˴�Ĭ���ڽӾ����в����ڵı���INFINITY��ʾ */
    for ( V=0; V<Graph->Nv; V++ ) {
        dist[V] = Graph->G[S][V];
        path[V] = -1;
        collected[V] = false;
    }
    /* �Ƚ�������뼯�� */
    dist[S] = 0;
    collected[S] = true;
 
    while (1) {
        /* V = δ����¼������dist��С�� */
        V = FindMinDist( Graph, dist, collected );
        if ( V==ERROR ) /* ��������V������ */
            break;      /* �㷨���� */
        collected[V] = true;  /* ��¼V */
        for( W=0; W<Graph->Nv; W++ ) /* ��ͼ�е�ÿ������W */
            /* ��W��V���ڽӵ㲢��δ����¼ */
            if ( collected[W]==false && Graph->G[V][W]<INFINITY ) {
                /* ����¼Vʹ��dist[W]��С */
                if ( dist[V]+Graph->G[V][W] < dist[W] ) {
                    dist[W] = dist[V]+Graph->G[V][W]; /* ����dist[W] */
                    path[W] = V; /* ����S��W��·�� */
                }
            }
    }
}
