#include <stdio.h>
#include <stdlib.h>
#include "List.h"

void showmovies(Item item);

int main(void){
	List movies;
	Item temp;
	
	//初始化 
	InitializeList(&movies);
	if(ListIsFull(&movies)){
		fprintf(stderr,"No memory available!");
		exit(1);
	}
	
	//收集并储存 
	puts("Enter first movie title:");
	while(gets(temp.title ) != NULL && temp.title [0] != '\0' ){
		puts("Enter your rating <0-10>:");
		scanf("%d",&temp.rating );
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
	
	//显示 
	if(ListIsEmpty(&movies)){
		printf("No data entered.");
	}
	else{
		printf("Here is the movie list:\n");
		Traverse(&movies,showmovies);
	}
	
	//清除 
	EmptyTheList(&movies);
	printf("Bye!");
	return 0;	
}

void showmovies(Item item){
	printf("Movie: %s Rating: %d\n", 
			item.title,
			item.rating);
}


