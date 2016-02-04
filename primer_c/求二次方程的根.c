#include <stdio.h>
#include <stdlib.h>
#include<math.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	double a,b,c,m,x1,x2,ff;
	printf("请输入三个系数的值，空格隔开：") ;
	scanf("%lf %lf %lf",&a,&b,&c);
	if ( a== 0){
		if(a==b){
			printf("Not a equation\n");
		}
		else{
			x1=(double)-c/b;
			printf("x1=x2=%lf\n",x1);
		}
	}
	else{
		m=b*b-4*a*c;
		if (m>0){
			x1=(-b+sqrt(m))/(2*a);
			x2=(-b-sqrt(m))/(2*a);
			printf("x1=%lf\n x2=%lf\n",x1,x2);
		}
		else if(m==0){
			x1=-b/(2*a);
			printf("x1=x2=%lf\n",x1);
		}
		else {
			ff=-b/(2*a);
			x1=sqrt(-m)/(-2*a);
			printf("x1=%lf+%lfi\n x2=%lf-%lfi\n",ff,x1,ff,x1);
			
		}
	}
	system("pause") ;
	return 0;
	
}
