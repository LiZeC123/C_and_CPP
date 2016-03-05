#include <stdio.h>
#include <stdlib.h>
#include "List.h"

#include <string.h>
#include <ctype.h>


void eatline(void){			//使用内联函数清除缓冲区多余的字符 
	while(getchar() != '\n')
		continue;
}					


char menu(void);
Item Get_Item(void);
unsigned int Get_Location(void);
void showmovies(Item item);
void Print_Count(unsigned int count);

int main(void){
	List movies;
	Item temp;
	unsigned int location;
	char choice;

	
	//初始化 
	InitializeList(&movies);
	
	while((choice = menu()) != 'q'){
		switch(choice){
			case 'a' :
				temp = Get_Item();
				if(AddItem(temp,&movies)==false){
					fprintf(stderr,"Problem allocating memory\n");
				}
				
				if(ListIsFull(&movies)){
					puts("The list is full.");

				}
				break;
				
			case 'l' :
				if(ListIsEmpty(&movies)){
					printf("No data entered.");
				}
				else{
					system("cls");
					printf("Here is the movie list:\n");
					Traverse(&movies,showmovies);
					puts("------------------------------------------");
				}
				break;
				
			case 'f' :
				temp = Get_Item();
				location = Get_Location();
				RandomAddItem(temp,location,&movies);
				break;
				
			case 'n' :
				Print_Count(ListItemCount(&movies));
				break;
				
			case 'd' :
				location = Get_Location();
				DeleteItem(&movies,location);
				break;
				
			default  :
				puts("Switching error");
		}
	}	
	EmptyTheList(&movies);
	puts("Bye!");
	
	return 0;	
}

char menu(void){
	int ch;
	
	puts("Nerfville Movies List Program"); 
	puts("Enter the letter correspnoding to your choice:");
	puts("a)add a pet at the last               f)add a movies after a location");
	puts("l)show list of pets                   n)number of pet");
	puts("d)delete a movies after a location    q)quit ");

	while ((ch=getchar()) != EOF){
		eatline();
		
		ch = tolower(ch);
		if(strchr("alndfq",ch) == NULL){
			puts("Please enter an a,l,n,f,d or q:");
		}
		else{
			break;
		}
	}
	if(ch == EOF){
		ch = 'q';
	}
	
	return ch;
}




void showmovies(Item item){
	printf("Movie:%sRating:%2d\n", item.name,item.rating);
}

Item Get_Item(void){
	Item temp;
	puts("Please input movies name:");
	fgets(temp.name ,MAX_SIZE,stdin);
	puts("Enter your rating <0-10>:");
	scanf("%d",&temp.rating );
	eatline();
	return temp;
}
 
unsigned int Get_Location(void){
	unsigned int location;
	puts("Please input the location:");
	scanf("%u",&location);
	return location;
}
 
 void Print_Count(unsigned int count){
 	printf("There are %4u movies in the list\n");
 }
 
