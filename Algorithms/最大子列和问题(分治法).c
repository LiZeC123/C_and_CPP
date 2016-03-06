#include <stdio.h>
#include <stdlib.h>
int MaxSubsequenceSum(const int arr[],int left,int right);
int max3(int a,int b,int c);

int main(void){
	int num;
	scanf("%d",&num);
	int arr[num];
	int i;
	for(i=0;i<num;i++){
		scanf("%d",&arr[i]);
	}
	int answer;
	answer = MaxSubsequenceSum(arr,0,num-1);
	printf("%d",answer);
}


int MaxSubsequenceSum(const int arr[],int left,int right){	
	if(left == right){
		if(arr[left] > 0){
			return arr[left];
		}
		else{
			return 0;
		}
	}
	
	int center = (left+right)/2;
	int max_left_sum,max_right_sum;
	max_left_sum  = MaxSubsequenceSum(arr,left,center);
	max_right_sum = MaxSubsequenceSum(arr,center+1,right);
	
	int max_left_border_sum = 0,left_border_sum = 0;
	int i;
	for(i=center;i>=left;i--){
		left_border_sum += arr[i];
		if(left_border_sum > max_left_border_sum){
			max_left_border_sum = left_border_sum;
		}
	}
	int max_right_border_sum = 0,right_border_sum = 0;
	for(i=center+1;i<=right;i++){
		right_border_sum += arr[i];
		if(right_border_sum > max_right_border_sum){
			max_right_border_sum = right_border_sum;
		}
	}
	
	return max3(max_left_sum,max_right_sum,max_left_border_sum+max_right_border_sum);
}


int max3(int a,int b,int c){
	int max =0;
	if(a > max){
		max = a;
	}
	if(b > max){
		max = b;
	}
	if(c > max){
		max = c;
	}
	return max;
	
}
