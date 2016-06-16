all: Matrix.o RowReduce.o
	gcc Matrix.o RowReduce.o -o Matrix

Matrix.o: Matrix.c
	gcc -c Matrix.c -o Matrix.o

RowReduce.o: RowReduce.c
	gcc -c RowReduce.c -o RowReduce.o

clean:
	rm *.o
	rm Matrix
