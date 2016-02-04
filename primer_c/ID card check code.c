#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int a[18];
	char c = '0';
	int i,power=2,sum=0;
	printf("please input your ID number without the last one:");
	for(i=1;i<18;i++){
		a[i]=getchar();    //过度输入会产生缓冲区溢出 
		a[i]-=c;
	}
	for(i=17;i>0;i--){
		power=power%11;
		a[i]=(a[i]*power)%11;
		sum=sum+a[i];
		power=power*2;
	}
	sum=sum%11;
	printf("\n");
	if(sum==1){
		sum=0;
	} 
	if(sum==0){
		sum=1;
	}
	else{
		sum=12-sum;
	}
	if(sum==10){
		printf("X");
	}
	else{
		printf("%d",sum);
	}
	
	return 0;
}
