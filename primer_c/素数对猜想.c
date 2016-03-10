#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

bool IsPrimerNumber(int n);

int main(void){
	int scan;
	int sum=0;
	scanf("%d",&scan);
	int pr1=2,pr2=3;
	int i;
	if(scan > 3 && scan < 5){
		printf("%d",0);
	} 
	else{
		for(i=5;i<=scan;i=i+2){
			if(IsPrimerNumber(i)){
				pr1=pr2;
				pr2=i;
				if(pr2-pr1 == 2){
					sum++;
				}
			}
		}
		printf("%d",sum);
		return 0;
	}
}

bool IsPrimerNumber(int n){
	int max;
	max=sqrt(n)+1;
	int i;
	for(i=2;i<=max;i++){
		if(n%i == 0){
			return false;
		}
	}
	return true;
}
