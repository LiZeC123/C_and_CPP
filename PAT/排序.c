#include <stdio.h>
#include <stdlib.h> 

int compare(const void * a,const void * b){
	return *(int *)a - *(int *)b;
}


int main(void){
	int N;
	scanf("%d",&N);
	int A[N];
	int i;
	for( i = 0; i < N ; i++ ){
		scanf("%d",&A[i]);
	}
	qsort(A,N,sizeof(int),compare);
	
	for( i = 0; i < N - 1 ; i++ ){
		printf("%d ",A[i]);
	}
	printf("%d",A[N-1]);
}
