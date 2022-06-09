#include <stdio.h>
#include <stdlib.h>
typedef struct max{
	int left;
	int right;
	int sum;
}Max;

Max MaxSubsequenceSum(const int arr[],int num);

int main(void){
	int num;
	scanf("%d",&num);
	int arr[num];
	int i;
	int max = -1;
	for(i=0;i<num;i++){
		scanf("%d",&arr[i]);
		if(arr[i] > max){
			max = arr[i];
		}
	}
	Max answer;
	if(max != 0){
		answer = MaxSubsequenceSum(arr,num);
	}
	else{
		int edx = 0;
		while(arr[edx] != 0){
			edx++;
		}
		answer.left = edx;
		while(arr[edx] == 0){
			edx++;
		}
		answer.right = edx -1;
		answer.sum = 0;
	}
	
	printf("%d",answer.sum);
	printf(" %d",arr[answer.left]);
	printf(" %d",arr[answer.right]);
	return 0;
}


Max MaxSubsequenceSum(const int arr[],int num){
	int this_sum=0,max_sum=0,j;
	int left=0,right=0;
	int pre_left=0,pre_right=-1;
	for(j=0;j<num;j++){
		
		this_sum+=arr[j];
		pre_right++;
		if(this_sum > max_sum){
			max_sum = this_sum;
			left = pre_left;
			right = pre_right;
		}
		else if(this_sum < 0){
			this_sum = 0;
			pre_left = pre_right +1;
		}
	}
	Max answer;
	if(max_sum != 0){
		answer.left = left;
		answer.right = right;
		answer.sum = max_sum;		
	}
	else{
		answer.left = 0;
		answer.right = num-1;
		answer.sum = max_sum;
	}
	
	return answer;
}
