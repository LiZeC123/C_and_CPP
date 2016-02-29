#include <stdio.h>
#include <stdlib.h>
#include "List.h"

void showmovies(Item item);


inline void eatline(){			//使用内联函数清除缓冲区多余的字符 
	while(getchar() != '\n')
		continue;
}					

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
	
	//显示 
	if(ListIsEmpty(&movies)){
		printf("No data entered.");
	}
	else{
		printf("Here is the movie list:\n");
		Traverse(&movies,showmovies);
	}

	
	
	//随机添加和删除
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
		
		//显示 
		if(ListIsEmpty(&movies)){
			printf("No data entered.");
		}
		else{
			printf("Here is the movie list:\n");
			Traverse(&movies,showmovies);
		}
		puts("Enter next movie title(empty line to stop))");
	} 
	
	//清除 
	EmptyTheList(&movies);
	printf("Bye!");
	
	return 0;	
}

void showmovies(Item item){
	printf("Movie: %s\n    Rating: %d\n", 
			item.name,
			item.age);
}

 
