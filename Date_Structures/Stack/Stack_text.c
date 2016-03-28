#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "Stack.h" 


char menu(void);
void addpet(Stack * pt);
void droppet(Stack *pt);
void showpet(Stack * pt);

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	Stack pets;
	char choice;
	
	InitializeStack(&pets);
	while((choice = menu()) != 'q'){
		switch(choice){
			case 'a' : 
				addpet(&pets);
				while(getchar() != '\n'){
					continue;
				}
				break;
			case 'n' :
				printf("%d pets in club\n",StackItemCount(&pets));
				break;
			case 'd' :
				droppet(&pets);
				break;
			default  :
				puts("Switching error");
		}
	}

	return 0;
}

char menu(void){
	int ch;
	
	puts("Nerfville Pet Club Membership Program"); 
	puts("Enter the letter correspnoding to your choice:");
	puts("a)add a pet		                    n)number of pet");
	puts("d)delete a pet and show that pets	    q)quit");
	while ((ch=getchar()) != EOF){
		while(getchar() != '\n'){
			continue;
		}
		
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


void addpet(Stack * pt){
	Item temp;
	
	if(StackIsFull(pt)){
		puts("No room in the club");
	}
	else{
		puts("Please enter data of pet");
		scanf("%d",&temp.data);
		Push(temp,pt);
	}
}


void droppet(Stack * pt){
	Item temp;
	
	if(StackIsEmpty(pt)){
		puts("No enteries");
		return;
	}
	
	if(Pop(&temp,pt)){
		printf("%d",temp);
	}
	else{
		printf("fail to delete");
	}
}


