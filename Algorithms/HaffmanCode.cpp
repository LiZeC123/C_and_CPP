#include <iostream>
#include <stdlib.h>
using namespace std;
const int MaxValue = 1000;//��ʼ�趨��Ȩֵ���ֵ
const int MaxBit = 64;//��ʼ�趨��������λ��
const int MaxN = 64;//��ʼ�趨�����Ҷ������
struct HaffNode//���������Ľ��ṹ
{
    int weight;//Ȩֵ
    int flag;//��Ǹýڵ��Ƿ��Ѽ������� 
    int parent;//˫�׽���±�
    int leftChild;//�����±�
    int rightChild;//�Һ����±�
};
struct Code//��Ź��������������Ԫ�ؽṹ
{
    int bit[MaxBit];//����
    int end;//����Ľ����±�
    int weight;//�ַ���Ȩֵ
};
void Haffman(int weight[], int n, HaffNode haffTree[])
//����Ҷ������ΪnȨֵΪweight�Ĺ�������haffTree
{
    int j, m1, m2, x1, x2;
    //��������haffTree��ʼ����n��Ҷ���Ĺ�����������2n-1�����
    for (int i = 0; i<2 * n - 1; i++)
    {
        if (i<n)
            haffTree[i].weight = weight[i];
        else
            haffTree[i].weight = 0;
        //ע������û��else��{}����������n��Ҷ�ӽڵ㻹��n-1����Ҷ�ӽڵ㶼���������4���ĳ�ʼ��
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
int main()
{
    int i, j, n = 4, WPL = 0;
    int weight[] = { 2,4,5,7 };
    HaffNode*myHaffTree = new HaffNode[2 * n - 1];
    Code*myHaffCode = new Code[n];
    if (n>MaxN)
    {
        cout << "�����nԽ�磬�޸�MaxN!" << endl;
        exit(0);
    }
    Haffman(weight, n, myHaffTree);
    HaffmanCode(myHaffTree, n, myHaffCode);
    //���ÿ��Ҷ���Ĺ���������ͬʱ����WPL 
    for (i = 0; i<n; i++)
    {
        cout << "Weight=" << myHaffCode[i].weight << " Code=";
        for (j = 0; j<myHaffCode[i].end; j++)
            cout << myHaffCode[i].bit[j];
        WPL = WPL + myHaffCode[i].weight*myHaffCode[i].end;
        cout << endl;
    }
    cout << "huffman'sWPLis:";
    cout << WPL;
    cout << endl;
    return 0;
}