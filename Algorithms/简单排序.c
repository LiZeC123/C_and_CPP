#include <stdio.h>

//ð�ݺͲ���ÿ�ζ���ȥһ������ԣ����Խ�������������Ը�����ͬ 
void BobbleSort( ElementType A[],int N){
	for(P = N-1;P >= 0;P--){
		flag = 0;
		for( i = 0;i < P;i++ ){
			if( A[i] > A[i+1]){
				Swap(A[i],A[i+1]);
				flag = 1;
			}
		}
		if(flag == 0){
			break;
		}
	}
}


void InsertionSort( ElementType A[], int N )
{ 
     int P, i;
     ElementType Tmp;
      
     for ( P=1; P<N; P++ ) {
         Tmp = A[P]; /* ȡ��δ���������еĵ�һ��Ԫ��*/
         for ( i=P; i>0 && A[i-1]>Tmp; i-- )
             A[i] = A[i-1]; /*������������������Ԫ�رȽϲ�����*/
         A[i] = Tmp; /* �Ž����ʵ�λ�� */
     }
}


void ShellSort( ElementType A[], int N )
{ /* ϣ������ - ��Sedgewick�������� */
     int Si, D, P, i;
     ElementType Tmp;
     /* ����ֻ�г�һС�������� */
     int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};
      
     for ( Si=0; Sedgewick[Si]>=N; Si++ ) 
         ; /* ��ʼ������Sedgewick[Si]���ܳ����������г��� */
 
     for ( D=Sedgewick[Si]; D>0; D=Sedgewick[++Si] )
         for ( P=D; P<N; P++ ) { /* ��������*/
             Tmp = A[P];
             for ( i=P; i>=D && A[i-D]>Tmp; i-=D )
                 A[i] = A[i-D];
             A[i] = Tmp;
         }
}
