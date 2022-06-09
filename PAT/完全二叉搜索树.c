#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int compare(const void * a,const void * b);
void slove(int Aleft,int Aright,int Troot,int A[],int T[]);
int GetLeftLength(int n);

int min(int a,int b){
	return a < b ? a : b ;
}



int main(void){
	int N;
	scanf("%d",&N);
	int A[N];
	int T[N];
	for(int i=0;i<N;i++){
		scanf("%d",&A[i]);
	}
	qsort(A,N,sizeof(int),compare);
	slove(0,N-1,0,A,T);
	for(int i=0;i<N-1;i++){
		printf("%d ",T[i]);
	}
	printf("%d",T[N-1]);
}

int compare(const void * a,const void * b){
	return *(int *)a - *(int *)b;
}



void slove(int Aleft,int Aright,int Troot,int A[],int T[]){
	int n = Aright - Aleft + 1;
	if(n == 0){
		return;
	}
	
	int L = GetLeftLength(n);
	T[Troot] = A[Aleft + L];
	int LeftTroot = 2*Troot + 1;
	int RightTroot = LeftTroot + 1;
	slove(Aleft,Aleft + L -1,LeftTroot,A,T);
	slove(Aleft + L + 1,Aright,RightTroot,A,T);
}

int GetLeftLength(int n){
	int H = 0;
	while((1<<H)-1 <= n){
		H++;
	}
	H--;
	int X = n - (1<<H) + 1;
	int answer = (1<<(H-1)) -1 + min(X,1<<(H-1));
	return answer;
}
