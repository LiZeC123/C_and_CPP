#include <stdio.h>
#include <stdbool.h>

#define Null -1

typedef struct tree{
	char data;
	int left;
	int right;
}Tree;

int BuildTree(Tree a [],int size);
bool Isomorphic(Tree a[],Tree b[],int roota,int rootb);

int main(void){
	int sizea;
	int roota;
	scanf("%d",&sizea);
	Tree a[sizea];
	roota = BuildTree(a,sizea); 
	
	int sizeb;
	int rootb;
	scanf("%d",&sizeb);
	Tree b[sizeb];
	rootb = BuildTree(b,sizeb);
	
	if(sizea == 0 && sizeb == 0){
		printf("Yes");
		return 0;
	}
	
	if (sizea == 0 || sizeb == 0){
		printf("No");
		return 0;
	}
	
	
	bool answer;
	answer = Isomorphic(a,b,roota,rootb);
	
	if(answer){
		printf("Yes");
	}
	else{
		printf("No");
	}
	
	return 0;
}


int BuildTree(Tree a [],int size){
	char cl,cr;
	bool check[size];
	for(int i=0;i<size;i++){
		check[i] = true;
	}
	
	for(int i=0;i<size;i++){
		scanf("\n%c %c %c",&a[i].data,&cl,&cr);
		if(cl != '-'){
			a[i].left = cl - '0';
			check[a[i].left] = false;
		}
		else{
			a[i].left = Null;
		}
		
		if(cr != '-'){
			a[i].right = cr - '0';
			check[a[i].right] = false;
		}
		else{
			a[i].right = Null;
		}
	}
	int root;
	for(int i=0;i<size;i++){
		if(check[i] == true){
			root = i;
			break;
		}
	}
	
	return root;
	
}



bool Isomorphic(Tree a[],Tree b[],int roota,int rootb){
	if(roota == Null && rootb == Null){
		return true;
	}
	
	if((roota == Null && rootb != Null) || (roota != Null && rootb == Null)){
		return false;
	}
	
	if(a[roota].data != b[rootb].data){
		return false;
	}
	
	if(a[roota].left == Null && b[rootb].left == Null){
		return Isomorphic(a,b,a[roota].right,b[rootb].right);
	}
	
	if((a[roota].left != Null && b[rootb].left != Null) && (a[a[roota].left].data == b[b[rootb].left].data)){
		return Isomorphic(a,b,a[roota].left,b[rootb].left) && Isomorphic(a,b,a[roota].right,b[rootb].right);
	}
	else{
		return Isomorphic(a,b,a[roota].left,b[rootb].right) && Isomorphic(a,b,a[roota].right,b[rootb].left);
	}
	
}
