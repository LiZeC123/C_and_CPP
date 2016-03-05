#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Matrix.h"
//����ѧ�ϵ�������ת��Ϊ���Ե���ֵ 
static int  EdxToEdx(Matrix * pmx,int i,int j);

//��pmxָ��ľ����У���rowָ����һ�и��Ƶ�ptempָ�������֮�� 
static void CopyToTemp(int * ptemp,int row,Matrix * pmx);


bool InitializeMatrix(Matrix * pmx,int row,int column){
	pmx->row    = row;
	pmx->column = column;
	int *ptem;
	ptem = (int *)malloc(row*column*sizeof(int));
	if(ptem == NULL){
		return false;
	}
	pmx->head   = ptem;
	return true;
}

Configuration Matrix_Configuration(Matrix * pmx){
	Configuration con;        				//con ����configuration 
	FILE * fp_con;
	fp_con = fopen("configuration.txt","r");
	fscanf(fp_con,"[where] = %d",&con.where);
	fclose(fp_con); 
	return con;
}

void Get_File_Matrix(Matrix * pmx,const char * filename){
	int * pi = pmx->head;
	const int ROW = pmx->row;
	const int COLUMN = pmx->column;
	int a,b;
	FILE * fp_file;
	fp_file = fopen(filename,"r");
	for(a=0;a<ROW;a++){
		for(b=0;b<COLUMN;b++){
			//�޸�int�󣬴˴���Ҫ�޸� 
			fscanf(fp_file,"%d",pi);
			pi++;
		}
	}	
}

void Get_stdin_Matrix(Matrix * pmx){
	int * pi = pmx->head;
	const int ROW = pmx->row;
	const int COLUMN = pmx->column;
	int a,b;
	puts("plesse input your Matrix now");
	for(a=0;a<ROW;a++){
		for(b=0;b<COLUMN;b++){
			//�޸�int�󣬴˴���Ҫ�޸� 
			scanf("%d",pi);
			pi++;
		}
	}		
}


void ShowMatrix(Matrix * pmx){
	int * pi = pmx->head;
	const int ROW = pmx->row;
	const int COLUMN = pmx->column;
	int a=0,b=0;
	for(a=0;a<ROW;a++){
		putchar('|');
		for(b=0;b<COLUMN;b++){
			printf("%5d",*pi);
			pi++;
		}
		printf("    |\n");
	}
	
}


void Traverse(Matrix * pmx, void (*pfun)(int item)){
	const int ROW = pmx->row;
	const int COLUMN = pmx->column;
	int * pi = pmx->head;
	int i,j;
	for(i=0;i<ROW;i++){
		for(j=0;j<COLUMN;j++){
			(*pfun)(*pi);
			pi++;
			//ʹ��ָ���ȡ���� 
		}
	}
}


void ToTriangleMattrix(Matrix * pmx){
	int each,i,j;
	const int ROW = pmx->row;
	const int COLUMN = pmx->column;
	int * pi = pmx->head; 
	int temp[COLUMN];		//������ڻ����������ڼ���ʱ����ʱ���� 
	int temp_do;			//������ڻ��������еĹؼ�Ԫ�� 
	int temp_done;			//��ű�������еĹؼ�Ԫ�� 
	for(each=1;each<=ROW-1;each++){
		for(i=each+1;i<=ROW;i++){
			CopyToTemp(temp,each,pmx);
			temp_do = pi[EdxToEdx(pmx,each,each)];
			temp_done = pi[EdxToEdx(pmx,i,each)];
			
			for(j=1;j<=COLUMN;j++){
				pi[EdxToEdx(pmx,i,j)] = temp_done*temp[j-1]-temp_do*pi[EdxToEdx(pmx,i,j)]; 
			}	
		}
	} 
} 


static int  EdxToEdx(Matrix * pmx,int i,int j){
	const int ROW = pmx->row;
	const int COLUMN = pmx->column;
	int r = (i-1)*COLUMN+(j-1);
	return r;
}


static void CopyToTemp(int * ptemp,int row,Matrix * pmx){
	const int ROW = pmx->row;
	const int COLUMN = pmx->column;
	int * pi = pmx->head;
	int start,end,i;
	start = EdxToEdx(pmx,row,1);
	end   = EdxToEdx(pmx,row,COLUMN);
	for(i=start;i<=end;i++){
		*ptemp = pi[i];
		ptemp++;
	}
}
