#include<stdio.h>
typedef struct date {
	int year;
	int month;
	int day;
}DATE;
int countday(DATE);
int runyear(int);
int main(int argc, char* argv[])
{
	DATE today;
	int totalday;
	int result;
	printf("请输入今天的日期如1997 2 10\n:");
	scanf("%d%d%d",&today.year,&today.month,&today.day );
	totalday=countday(today);
	result=totalday%5;
	if(result>0 && result<4){
		printf("今天打渔\n");
	}
	else{
		printf("今天晒网\n");
	}
	return 0;
}

int countday(DATE currentday){
	int permonth[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	int totalday=0,year,i;
	for(year=1990;year<currentday.year;year++){
		if(runyear(year))
			totalday+=366;
		else
			totalday+=365;
	}
	if(runyear(currentday.year))
		permonth[2]++;
	for(i=1;i<currentday.month;i++)
		totalday+=permonth[i];
	totalday+=currentday.day;
	return totalday;
}

int runyear(int year){
	if((year%4==0 && year%100 != 0 )||(year%400==0))
		return 1;
	else
		return 0;
}
