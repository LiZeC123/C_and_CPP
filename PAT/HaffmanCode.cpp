#include <iostream>
#include <stdlib.h>
using namespace std;
const int MaxValue = 1000;//��ʼ�趨��Ȩֵ���ֵ
const int MaxBit = 65;//��ʼ�趨��������λ��
const int MaxN = 65;//��ʼ�趨�����Ҷ������
struct HaffNode//���������Ľ��ṹ
{
    int weight;//Ȩֵ
    char chr;//�ַ������� 
    int flag;//��Ǹýڵ��Ƿ��Ѽ������� 
    int parent;//˫�׽���±�
    int leftChild;//�����±�
    int rightChild;//�Һ����±�
};
struct Code//��Ź��������������Ԫ�ؽṹ
{
    int bit[MaxBit];//��ű�������
    int end;//����Ľ����±�
    int weight;//�ַ���Ȩֵ
};
void Haffman(int weight[], char chr[],int n, HaffNode haffTree[])
//����Ҷ������ΪnȨֵΪweight�Ĺ�������haffTree
{
    int j, m1, m2, x1, x2;
    //��������haffTree��ʼ����n��Ҷ���Ĺ�����������2n-1����� 
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
    //�����������haffTree��n-1����Ҷ���
    for (int i = 0; i<n - 1; i++)
    {
        m1 = m2 = MaxValue;//�����Ӧ��ֵ��Ȩ�� 
        x1 = x2 = 0;//x1��x2������������С������ֵ�������Ӧ���±�
 
        for (j = i; j<n + i; j++)//ѭ���ҳ�����Ȩ���У���С�Ķ���ֵ--morgan
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
        //���ҳ�������Ȩֵ��С�������ϲ�Ϊһ������
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
//��n�����Ĺ�������haffTree�������������haffCode
{
    Code *cd = new Code;
    int child, parent;
    //��n��Ҷ���Ĺ���������
    for (int i = 0; i<n; i++)
    {
    	//��0��ʼ����
        cd->end = 0;
        cd->weight = haffTree[i].weight;//ȡ�ñ����ӦȨֵ���ַ� 
        child = i;
        parent = haffTree[child].parent;
        //��Ҷ�������ֱ�������
        while (parent != 0)
        {
            if (haffTree[parent].leftChild == child)
                cd->bit[cd->end] = 0;//���ӽ�����0
            else
                cd->bit[cd->end] = 1;//�Һ��ӽ�����1
                                      //cd->end--;
            cd->end++;
            child = parent;
            parent = haffTree[child].parent;
        }
        //����Ҷ���ı���Ͳ��ȳ�����Ľ���λ 
        for (int j = cd->end - 1; j >= 0; j--)//endָ��������һ���ַ�����һλ 
            haffCode[i].bit[cd->end - j - 1] = cd->bit[j];
 
        haffCode[i].end = cd->end;
        haffCode[i].weight = cd->weight;//��������Ӧ��Ȩֵ
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
    //��ȡ�������� 
    scanf("%d",&n);
	getchar();//��ȡ���к���Ļ��� 
    int weight[n];
    char chr[n];
    for(int i=0;i<n;i++){
    	scanf("%c %d",&chr[i],&weight[i]);
    	getchar();
	}
	int case_num;
	scanf("%d",&case_num);
	getchar();
	//������������������WPL 
    HaffNode*myHaffTree = new HaffNode[2 * n - 1];
    Code*myHaffCode = new Code[n];
    Haffman(weight,chr, n, myHaffTree);
    HaffmanCode(myHaffTree, n, myHaffCode);
    //���ÿ��Ҷ���Ĺ���������ͬʱ����WPL 
    for (int i = 0; i<n; i++)
    {
        WPL = WPL + myHaffCode[i].weight*myHaffCode[i].end;
    }
    
    
	
	//��ȡ����
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
		
		
		//����÷�����WPL 
		bool answer = true;//�ж��������Ľ�� 
	    int inWPL = 0;
	    for(int i = 0; i<n; i++){
	    	inWPL = inWPL + myincode[i].end * weight[i];
		}
		if(inWPL != WPL){
			answer = false;
		} 
		
		
		//����Ƿ�Ϊǰ׺��
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
