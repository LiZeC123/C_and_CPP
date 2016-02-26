#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

typedef struct matrix{
	int row;
	int column;
	int * head;
}Matrix;

typedef struct configuration{
	int where;
}Configuration;

bool InitializeMatrix(Matrix * pmx,int row,int column);

Configuration Matrix_Configuration(Matrix * pmx);

void Get_File_Matrix(Matrix * pmx,const char * filename);

void Get_stdin_Matrix(Matrix * pmx);

void ShowMatrix(Matrix * pmx);



void ToTriangleMattrix(Matrix * pmx);

//condition			:求解三角形方程的解 
//precondition		:pmx指向一个已化为三角形的矩阵 
//postcondition		:该矩阵变为行最简 
void SolveTriangleMattrix(Matrix * pmx);



void Traverse(Matrix * pmx, void (*pfun)(int item));


#endif
