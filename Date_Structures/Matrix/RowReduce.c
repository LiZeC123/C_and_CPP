#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	Matrix Rc;
	int  row,column;
	printf("How many unknown number does the matrix have:");
	scanf("%d",&row);
	column=row+1;
	
	//��ʼ�� 
	if(!InitializeMatrix(&Rc,row,column)){
		puts("The memory is full now.");
		system("pause");
		exit(1);
	}
	Configuration con;
	con = Matrix_Configuration(&Rc);
	
	//���������ļ�ѡ���ȡ��ʽ 
	if(con.where == 1){
		Get_File_Matrix(&Rc,"source.txt");
	}
	else{
		Get_stdin_Matrix(&Rc);
	}
	
	//��ʾ��ǰ���� 
	puts("There is the matrix you input:");

	ShowMatrix(&Rc);
	
	
	//ת���������η���
	ToTriangleMattrix(&Rc);
	puts("there is the answer:");
	ShowMatrix(&Rc);
	
	
	return 0;
}
