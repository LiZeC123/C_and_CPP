
#include "acllib.h"
#include <stdlib.h>
#include <time.h>
 
int speed = 3;
 
void speedModi( int key, int event )
{
    /* /��Ӧ���̡� ���������ٶ�*/ 
    if( event != KEY_UP )
        return;
    switch( key )
    {
    case VK_UP:
        if( speed <= 10 )
            speed++;
        break;
    case VK_DOWN:
        if( speed > 1 )
            speed--;
        break;
    };
}
 
void Player( int timerID )
{
    int i,j;
    static int iShiver = 2;             //��������ֵ
    static int iCCarSpeed = 3;      //�����ٶ�
    static DWORD dwColor=0;   //���������ɫ
    /* **************** ����ΪԤ�������� **************** */
    static POINT pointLight[][9] = {
        {   {50,330},   {65,330},   {65,150},   {85,150},   {85,140},   {30,140},   {30,150},   {50,150},   {50,330}    },
        {   {200,330},  {215,330},  {215,150},  {235,150},  {235,140},  {180,140},  {180,150},  {200,150},  {200,330}   },
        {   {350,330},  {365,330},  {365,150},  {385,150},  {385,140},  {330,140},  {330,150},  {350,150},  {350,330}   },
        {   {500,330},  {515,330},  {515,150},  {535,150},  {535,140},  {480,140},  {480,150},  {500,150},  {500,330}   },
        {   {650,330},  {665,330},  {665,150},  {685,150},  {685,140},  {630,140},  {630,150},  {650,150},  {650,330}   }, //���һ����֤��������
    }; //·�ƽṹ��,·�ƿ��Ϊ55px
    static POINT pointCar[] = { {40,380},   {65,380},   {90,355},   {195,355},  {215,380},  {250,380},  {250,410},  {40,410},   {40,380} };    //С������ṹ С�����Ϊ210px
    static POINT pointComingCar[] = {   {30,325},   {65,325},   {90,300},   {195,300},  {215,325},  {240,325},  {240,355},  {30,355},   {30,325} };    //��������ṹ С�����Ϊ210px
    static int pointComingCarWheel[][4] = { {70,335,105,370},  {155,335,190,370} }; //��������
    static POINT pointComingCarRevise[] = { {30,325},   {65,325},   {90,300},   {195,300},  {215,325},  {240,325},  {240,355},  {30,355},   {30,325} };    //��������ṹ ����������
    static int pointComingCarWheelRevise[][4] = { {70,335,105,370},    {155,335,190,370} }; //�������� ����������
    /* **************** ����ΪԤ�������� **************** */
 
    iShiver = -iShiver;   //��ת�Բ�������
 
    /* ˢ�±��� */
    beginPaint();
    setPenColor(EMPTY);
    setBrushColor(WHITE);
    setBrushStyle(BRUSH_STYLE_SOLID);
    rectangle(0,0,600,450); 
 
    /* ���Ƶ�· */
    setPenWidth(10);
    setBrushColor(RGB(230,230,230));
    rectangle(0,310,600,450);
    setPenColor(YELLOW);
    line(0,320,600,320);
    line(0,440,600,440);    //��·
    setPenColor(WHITE);
    line(0,380,600,380);
 
    /* ����·�� */
    setPenWidth(3);
    setPenColor(RGB(5,167,185));
    setBrushColor(RGB(5,200,220));
    for( j=0; j<5; j++)   
    {
        polygon( pointLight[j], 9 );
    }
 
    /* �������� */
    setPenWidth(5);
    /* �������� */
    setPenColor(RGB(5,167,185));
    setBrushColor(dwColor);     //dwColor���·��ж������Ƿ�Խ������ʱͬʱ����
    polygon(pointComingCar, 9);    //���Ƴ���
    setPenColor(RGB(0,0,0));
    setBrushColor(RGB(80,75,75));   //����������ɫ
    ellipse(pointComingCarWheel[0][0],pointComingCarWheel[0][1],pointComingCarWheel[0][2],pointComingCarWheel[0][3]);
    ellipse(pointComingCarWheel[1][0],pointComingCarWheel[1][1],pointComingCarWheel[1][2],pointComingCarWheel[1][3]);
    /* ����ǰ���ĳ� */
    setPenColor(RGB(215,215,215));
    setBrushColor(RGB(5,200,220));
    polygon(pointCar, 9);
    setPenColor(RGB(0,0,0));
    setBrushColor(RGB(80,75,75));
    ellipse(85,390,120,425);
    ellipse(170,390,205,425);
 
    /* �·������ͼ���� */
    for( j=0; j<5; j++)
    {
        if( pointLight[j][3].x < -55 )   //���·��j�Ƿ���ȫԽ����Ļ,Light[j][3]��Ϊ���Ҳ�ĵ㣬������õ�Խ����·�ƿ���������Ϊ��ȫԽ����Ļ
        {
            for( i=0; i<9; i++ ) pointLight[j][i].x += 750;        //������·�ƺ���һ���ڼ�һ��λ��࣬��Ϊ600+150 
        }
        else
        {
            for( i=0; i<9; i++ ) pointLight[j][i].x -= speed;  //���������ƶ�·�ƣ����С��ǰ���Ĵ��
        }
    }
    if( pointComingCar[6].x < -210 ) //ͬ����С���Ƿ���ȫԽ��
    {
        int iTemp = rand() % 300;
 
        for( i=0; i<9; i++ ) pointComingCar[i].x += 1020+iTemp;        //Խ�������һ���ڼ��������ȣ���Ϊ600+210*2������������ֵ
        pointComingCarWheel[0][0] += 1020+iTemp;
        pointComingCarWheel[0][2] += 1020+iTemp;
        pointComingCarWheel[1][0] += 1020+iTemp;
        pointComingCarWheel[1][2] += 1020+iTemp;
        iCCarSpeed = rand() % 10+1; //������������ٶ�1-10
        iShiver = iCCarSpeed / 4 * 2; //ʹ�ò������ٶȲ�����������
        dwColor = RGB(rand() % 255, rand() % 255, rand() % 255);  //��������ó���ɫ
    }
    else
    {
        for( i=0; i<9; i++ ) pointComingCar[i].x -= speed+iCCarSpeed;      //�����ƶ��������ӣ�����speedΪǰ���ٶȣ�iCCarSpeedΪ����С�����ٶ�
        pointComingCarWheel[0][0] -= speed+iCCarSpeed;
        pointComingCarWheel[0][2] -= speed+iCCarSpeed;
        pointComingCarWheel[1][0] -= speed+iCCarSpeed;
        pointComingCarWheel[1][2] -= speed+iCCarSpeed;
        //ʹ��ԭʼ������������Ч�����޸�����������������ƫ�Ƶ�����
        for( i=0; i<9; i++ ) pointComingCar[i].y = pointComingCarRevise[i].y + iShiver;
        pointComingCarWheel[0][1] = pointComingCarWheelRevise[0][1] + iShiver;
        pointComingCarWheel[0][3] = pointComingCarWheelRevise[0][3] + iShiver;
        pointComingCarWheel[1][1] = pointComingCarWheelRevise[1][1] + iShiver;
        pointComingCarWheel[1][3] = pointComingCarWheelRevise[1][3] + iShiver;
    }
    endPaint();
}
 
int Setup()
{
    srand((unsigned)time(NULL));
    initWindow("Hello World", 100, 100 , 600 , 450);
 
    registerTimerEvent(&Player);    //ע�ᶨʱ����Ϣ
    registerKeyboardEvent(&speedModi);  //ע�������Ϣ
    startTimer(1, 10);
 
    return 0;
}
