#include <stdio.h>
#include <stdlib.h>

int main(void){
	int NUM,shift;
	scanf("%d %d",&NUM,&shift);
	shift =shift % NUM;
	int arr[NUM+1];
	int i;
	for(i=1;i<=NUM;i++){
		if(i<=shift){
			scanf("%d",&arr[i+NUM-shift]);
		}	
		else{
			scanf("%d",&arr[i-shift]);
		}		
	}
	for(i=1;i<=NUM;i++){
		if(i == NUM){
			printf("%d",arr[i]);
		}
		else{
			printf("%d ",arr[i]);
		}
	} 
	return 0;
}

