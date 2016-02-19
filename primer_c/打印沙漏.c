#include <stdio.h>
#include <stdlib.h>

#define SPACE '\040'
void print(char ch,int n);


int main(int argc, char *argv[]) {
	int sum;
	int n;

	char point;
	scanf("%d %c",&sum,&point); 
	n=1;  
	while( (2*n*n-1) <= sum)   //注意到恰好相等的情况 
		n++;
	n--;
	sum-=2*n*n-1;
	int i,j,k;
	for(i=1;i<=(2*n-1);i++){
		if(i<n){
			print(SPACE,i-1);
			print(point,2*n-2*i+1);
			putchar('\n');
		}
		else{
			print(SPACE,2*n-i-1);
			print(point,2*i-2*n+1);
			putchar('\n');
		}
	}
	printf("%d",sum);
	
	return 0;
}

void print(char ch,int n){
	int i;
	for(i=0;i<n;i++){
		putchar(ch);
	} 
}
