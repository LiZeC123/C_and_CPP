#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct element{
	int coe;	//ϵ�� 
	int exp;	//ָ�� 
}Element;
void print_and(Element pi[],int Max);

int main (){
	unsigned int sum1;
	scanf("%u",&sum1);
	Element poly1[sum1];
	int i;
	for(i=0;i<sum1;i++){
		scanf("%d",&poly1[i].coe);
		scanf("%d",&poly1[i].exp);
	}
	
	unsigned int sum2;
	scanf("%u",&sum2);
	Element poly2[sum2];
	for(i=0;i<sum2;i++){
		scanf("%d",&poly2[i].coe);
		scanf("%d",&poly2[i].exp);
	}	


	//and
	//����������ͽ�������鲢��ʼ�� 
	Element poly_and[sum1+sum2];
	for(i=0;i<sum1+sum2;i++){
		poly_and[i].coe = 0;
		poly_and[i].exp = 0;
	}
	
	int j=0,k=0;
	i=0;
	while(j<sum1 && k <sum2){
		if(poly1[j].exp == poly2[k].exp){
			poly_and[i].exp = poly1[j].exp;
			poly_and[i].coe = poly1[j].coe+ poly2[k].coe;
			i++;
			j++;
			k++;
		}
		else if(poly1[j].exp > poly2[k].exp){
			poly_and[i].exp = poly1[j].exp;
			poly_and[i].coe = poly1[j].coe;
			i++;
			j++;
		}
		else{
			poly_and[i].exp = poly2[k].exp;
			poly_and[i].coe = poly2[k].coe;
			i++;
			k++;
		}
	}
	
	
	//ʣ�ಿ��ֱ�Ӽ��� 
	while(j<sum1-1){
		poly_and[i].exp = poly1[j].exp;
		poly_and[i].coe = poly1[j].coe;
		i++;
		j++;
	}
	while(k <sum2-1){
		poly_and[i].exp = poly2[k].exp;
		poly_and[i].coe = poly2[k].coe;
		i++;
		j++;
	}
	print_and(poly_and,i);
	
	
	
	
	//�˷�
	Element poly_multi[sum1*sum2];
	for(i=0;i<sum1*sum2;i++){
		poly_multi[i].coe = 0;
		poly_multi[i].exp = 0;
	}
	
	
	 
	
	
	
	return 0;
}


Element poly_add()




void print_and(Element pi[],int Max){
	int count=0;
	int i;
	for(i=0;i<Max;i++){
		if(pi[i].coe == 0){
			count++;
		}
	}
	if(count == Max-1){
		printf("0 0");
	}
	else{
		printf("%d %d",pi[0].coe,pi[0].exp);
		for(i=1;i<Max;i++){
			printf(" %d %d",pi[i].coe,pi[i].exp);
		}
	}
}
