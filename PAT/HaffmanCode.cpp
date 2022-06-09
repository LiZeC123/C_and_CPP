#include <iostream>
#include <stdlib.h>
using namespace std;
const int MaxValue = 1000;//初始设定的权值最大值
const int MaxBit = 65;//初始设定的最大编码位数
const int MaxN = 65;//初始设定的最大叶结点个数
struct HaffNode//哈夫曼树的结点结构
{
    int weight;//权值
    char chr;//字符的名称 
    int flag;//标记该节点是否已加入树中 
    int parent;//双亲结点下标
    int leftChild;//左孩子下标
    int rightChild;//右孩子下标
};
struct Code//存放哈夫曼编码的数据元素结构
{
    int bit[MaxBit];//存放编码数组
    int end;//编码的结束下标
    int weight;//字符的权值
};
void Haffman(int weight[], char chr[],int n, HaffNode haffTree[])
//建立叶结点个数为n权值为weight的哈夫曼树haffTree
{
    int j, m1, m2, x1, x2;
    //哈夫曼树haffTree初始化。n个叶结点的哈夫曼树共有2n-1个结点 
    for (int i = 0; i<2 * n - 1; i++)
    {
        if (i<n){
            haffTree[i].weight = weight[i];
            haffTree[i].chr    = chr[i];
        }
        else{
            haffTree[i].weight = 0;
            haffTree[i].chr    = '!';
        }
        haffTree[i].parent = 0;
        haffTree[i].flag = 0;
        haffTree[i].leftChild = -1;
        haffTree[i].rightChild = -1;
    }
    //构造哈夫曼树haffTree的n-1个非叶结点
    for (int i = 0; i<n - 1; i++)
    {
        m1 = m2 = MaxValue;//保存对应数值的权重 
        x1 = x2 = 0;//x1、x2是用来保存最小的两个值在数组对应的下标
 
        for (j = i; j<n + i; j++)//循环找出所有权重中，最小的二个值--morgan
        {
            if (haffTree[j].weight<m1&&haffTree[j].flag == 0)
            {
                m2 = m1;
                x2 = x1;
                m1 = haffTree[j].weight;
                x1 = j;
            }
            else if(haffTree[j].weight<m2&&haffTree[j].flag == 0)
            {
                m2 = haffTree[j].weight;
                x2 = j;
            }
        }
        //将找出的两棵权值最小的子树合并为一棵子树
        haffTree[x1].parent = n + i;
        haffTree[x2].parent = n + i;
        haffTree[x1].flag = 1;
        haffTree[x2].flag = 1;
        haffTree[n + i].weight = haffTree[x1].weight + haffTree[x2].weight;
        haffTree[n + i].leftChild = x1;
        haffTree[n + i].rightChild = x2;
    }
}
void HaffmanCode(HaffNode haffTree[], int n, Code haffCode[])
//由n个结点的哈夫曼树haffTree构造哈夫曼编码haffCode
{
    Code *cd = new Code;
    int child, parent;
    //求n个叶结点的哈夫曼编码
    for (int i = 0; i<n; i++)
    {
    	//从0开始计数
        cd->end = 0;
        cd->weight = haffTree[i].weight;//取得编码对应权值的字符 
        child = i;
        parent = haffTree[child].parent;
        //由叶结点向上直到根结点
        while (parent != 0)
        {
            if (haffTree[parent].leftChild == child)
                cd->bit[cd->end] = 0;//左孩子结点编码0
            else
                cd->bit[cd->end] = 1;//右孩子结点编码1
                                      //cd->end--;
            cd->end++;
            child = parent;
            parent = haffTree[child].parent;
        }
        //保存叶结点的编码和不等长编码的结束位 
        for (int j = cd->end - 1; j >= 0; j--)//end指向的是最后一个字符的下一位 
            haffCode[i].bit[cd->end - j - 1] = cd->bit[j];
 
        haffCode[i].end = cd->end;
        haffCode[i].weight = cd->weight;//保存编码对应的权值
    }
}


inline void eatline(void){
	while(getchar() != '\n'){
		continue;
	}
}

struct Incode{
	char incodebit[MaxBit];
	int  end;
};

struct Tree{
	bool flag;
	struct Tree * Left;
	struct Tree * Right;
};

int main()
{
    int  n = 0, WPL = 0;
    //读取基本参数 
    scanf("%d",&n);
	getchar();//读取此行后面的换行 
    int weight[n];
    char chr[n];
    for(int i=0;i<n;i++){
    	scanf("%c %d",&chr[i],&weight[i]);
    	getchar();
	}
	int case_num;
	scanf("%d",&case_num);
	getchar();
	//构建哈夫曼树，计算WPL 
    HaffNode*myHaffTree = new HaffNode[2 * n - 1];
    Code*myHaffCode = new Code[n];
    Haffman(weight,chr, n, myHaffTree);
    HaffmanCode(myHaffTree, n, myHaffCode);
    //输出每个叶结点的哈夫曼编码同时计算WPL 
    for (int i = 0; i<n; i++)
    {
        WPL = WPL + myHaffCode[i].weight*myHaffCode[i].end;
    }
    
    
	
	//读取输入
	Incode myincode[n];
	int j = 0;
	while(case_num--){
		
		for (int i=0;i<n;i++){
			getchar();
			getchar();
			fgets(myincode[i].incodebit,MaxBit,stdin);
			myincode[i].end = 0;
			j=0;
			while(myincode[i].incodebit[j] == '0' || myincode[i].incodebit[j] == '1'){
				myincode[i].end++;
				j++;
			}
		}
		
		
		//计算该方案的WPL 
		bool answer = true;//判定最后输出的结果 
	    int inWPL = 0;
	    for(int i = 0; i<n; i++){
	    	inWPL = inWPL + myincode[i].end * weight[i];
		}
		if(inWPL != WPL){
			answer = false;
		} 
		
		
		//检查是否为前缀码
		Tree * root = new Tree;
		Tree * proot = root;
		root->flag = false;
		root->Left = NULL;
		root->Right = NULL;
		
		for(int i=0;i<n;i++){
			proot = root;
			for(j=0;j<myincode[i].end;j++){
				if(myincode[i].incodebit[j] == '0'){
					if(proot->Left == NULL){
						proot->Left = new Tree;
						proot = proot->Left;
						proot->Left = NULL;
						proot->Right = NULL;
						proot->flag = false;
					}
					else{
						proot = proot->Left;
						if(proot->flag == true){
							answer = false;
							break;
						}
					}
				}
				else{
					if(proot->Right == NULL){
						proot->Right = new Tree;
						proot = proot->Right;
						proot->Left = NULL;
						proot->Right = NULL;
						proot->flag = false;
					}
					else{
						proot = proot->Right;
						if(proot->flag == true){
							answer = false;
							break;
						}
					}
				}
			}
			
			proot->flag = true;
			if(proot->Left != NULL){
				if(proot->flag == true){
					answer = false;
				}
			}
			if(proot->Right != NULL){
				if(proot->flag == true){
					answer = false;
				}
			}
		}
		if(answer){
			printf("Yes\n");
		}
		else{
			printf("No\n");
		}
	}
    return 0;
}
