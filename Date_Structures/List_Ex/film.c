#include <stdio.h>
#include <stdlib.h>
#include "List.h"

void showmovies(Item item);


inline void eatline(){			//ʹ�������������������������ַ� 
	while(getchar() != '\n')
		continue;
}					

int main(void){
	List movies;
	Item temp;
	
	//��ʼ�� 
	InitializeList(&movies);
	if(ListIsFull(&movies)){
		fprintf(stderr,"No memory available!");
		exit(1);
	}
	
	//�ռ������� 
	puts("Enter first movie title:");
	while(gets(temp.name ) != NULL && temp.name [0] != '\0' ){
		puts("Enter your rating <0-10>:");
		scanf("%d",&temp.age );
		while(getchar()!='\n'){
			continue;
		}
		if(AddItem(temp,&movies)==false){
			fprintf(stderr,"Problem allocating memory\n");
			break;
		}
		if(ListIsFull(&movies)){
			puts("The list is full.");
			break; 
		}
		puts("Enter next movie title(empty line to stop))");
	}
	
	//��ʾ 
	if(ListIsEmpty(&movies)){
		printf("No data entered.");
	}
	else{
		printf("Here is the movie list:\n");
		Traverse(&movies,showmovies);
	}

	
	
	//�����Ӻ�ɾ��
	puts("Enter first movie title:");
	while(gets(temp.name ) != NULL && temp.name [0] != '\0' ){
		puts("Enter your rating <0-10>:");
		scanf("%d",&temp.age );
		eatline();
		puts("Enter the location:");
		scanf("%u",&edx);
		while(getchar()!='\n'){
			continue;
		}	
		
		RandomAddItem(temp,&movies,edx);
		
		//��ʾ 
		if(ListIsEmpty(&movies)){
			printf("No data entered.");
		}
		else{
			printf("Here is the movie list:\n");
			Traverse(&movies,showmovies);
		}
		puts("Enter next movie title(empty line to stop))");
	} 
	
	//��� 
	EmptyTheList(&movies);
	printf("Bye!");
	
	return 0;	
}

void showmovies(Item item){
	printf("Movie: %s\n    Rating: %d\n", 
			item.name,
			item.age);
}

 
