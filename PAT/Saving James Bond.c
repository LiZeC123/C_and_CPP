#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define MAX_NUM 101
#define INSTAND_DISTANCE 7.5
typedef struct{
	int x;
	int y;
}Location;

typedef int PointLocation;

bool Jump(PointLocation A,PointLocation B);
bool FirstJump(PointLocation A,PointLocation B);
bool IsSave(PointLocation A);
bool DFS(PointLocation A);
Location Data[MAX_NUM];
bool Visit[MAX_NUM];
	int num,distance;

int main(void){
	scanf("%d %d",&num,&distance);
	
	for(int i=0;i<num;i++){
		scanf("%d %d",&Data[i].x,&Data[i].y);
		Visit[i] = false;
	}
	
	Data[num].x = 0;
	Data[num].y = 0;
	bool answer;
	for(int i=0;i<num;i++){
		if(!Visit[i] && FirstJump(num,i)){
			answer = DFS(i);
		}
	}
	
	if(answer){
		printf("Yes");
	}
	else{
		printf("No");
	}
	
	return 0;
}


bool Jump(PointLocation A,PointLocation B){
	return (Data[A].x-Data[B].x)*(Data[A].x-Data[B].x)
			    +  (Data[A].y-Data[B].y)*(Data[A].y-Data[B].y) <= distance*distance;
}

bool FirstJump(PointLocation A,PointLocation B){
	return (Data[A].x-Data[B].x)*(Data[A].x-Data[B].x)
			    +  (Data[A].y-Data[B].y)*(Data[A].y-Data[B].y) <= 
					(distance+INSTAND_DISTANCE)*(distance+INSTAND_DISTANCE);
}


bool IsSave(PointLocation A){
	return (50 - abs(Data[A].x) <= distance) || (50 -abs(Data[A].y) <= distance);
}

bool DFS(PointLocation A){
	bool answer = false;
	Visit[A] = true;
	if(IsSave(A)){
		return true ;
	}
	
	for(int i=0;i<num;i++){
		if(!Visit[i] && Jump(A,i)){
			answer = DFS(i);
		}
	}
	
	return answer;
}
