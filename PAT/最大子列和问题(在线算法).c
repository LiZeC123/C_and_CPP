#include <stdio.h>
#include <stdlib.h>
int MaxSubsequenceSum(const int arr[],int num);

int main(void){
	int num;
	scanf("%d",&num);
	int arr[num];
	int i;
	for(i=0;i<num;i++){
		scanf("%d",&arr[i]);
	}
	int answer;
	answer = MaxSubsequenceSum(arr,num);
	printf("%d",answer);
}


int MaxSubsequenceSum(const int arr[],int num){
	int this_sum=0,max_sum=0,j;
	for(j=0;j<num;j++){
		this_sum+=arr[j];
		
		if(this_sum>max_sum){
			max_sum = this_sum;
		}
		else if(this_sum < 0){
			this_sum = 0;
		}
	}
	return max_sum;
}
