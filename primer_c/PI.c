#include <stdio.h>
#include <stdlib.h>
#include<time.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	srand((unsigned)time(NULL)); 
	double x,y,pi;
	int i=0,n=0;
	while(n<=100000000) {
		x=(double)rand()/RAND_MAX;
		y=(double)rand()/RAND_MAX;
		if (x*x+y*y<=1){
			i=i+1;
		}
		n=n+1;
	}
	pi=4.0*i/n;
	printf("PI=%lf",pi);
	return 0;
}
