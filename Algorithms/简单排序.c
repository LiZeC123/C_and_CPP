#include <stdio.h>

//冒泡和插入每次都消去一个逆序对，所以交换次数与逆序对个数相同 
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
         Tmp = A[P]; /* 取出未排序序列中的第一个元素*/
         for ( i=P; i>0 && A[i-1]>Tmp; i-- )
             A[i] = A[i-1]; /*依次与已排序序列中元素比较并右移*/
         A[i] = Tmp; /* 放进合适的位置 */
     }
}


void ShellSort( ElementType A[], int N )
{ /* 希尔排序 - 用Sedgewick增量序列 */
     int Si, D, P, i;
     ElementType Tmp;
     /* 这里只列出一小部分增量 */
     int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};
      
     for ( Si=0; Sedgewick[Si]>=N; Si++ ) 
         ; /* 初始的增量Sedgewick[Si]不能超过待排序列长度 */
 
     for ( D=Sedgewick[Si]; D>0; D=Sedgewick[++Si] )
         for ( P=D; P<N; P++ ) { /* 插入排序*/
             Tmp = A[P];
             for ( i=P; i>=D && A[i-D]>Tmp; i-=D )
                 A[i] = A[i-D];
             A[i] = Tmp;
         }
}
