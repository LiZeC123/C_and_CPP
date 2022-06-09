
#include "acllib.h"
#include <stdlib.h>
#include <time.h>
 
int speed = 3;
 
void speedModi( int key, int event )
{
    /* /响应键盘↑ ↓键调整速度*/ 
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
    static int iShiver = 2;             //来车抖动值
    static int iCCarSpeed = 3;      //来车速度
    static DWORD dwColor=0;   //来车随机颜色
    /* **************** 以下为预置数据组 **************** */
    static POINT pointLight[][9] = {
        {   {50,330},   {65,330},   {65,150},   {85,150},   {85,140},   {30,140},   {30,150},   {50,150},   {50,330}    },
        {   {200,330},  {215,330},  {215,150},  {235,150},  {235,140},  {180,140},  {180,150},  {200,150},  {200,330}   },
        {   {350,330},  {365,330},  {365,150},  {385,150},  {385,140},  {330,140},  {330,150},  {350,150},  {350,330}   },
        {   {500,330},  {515,330},  {515,150},  {535,150},  {535,140},  {480,140},  {480,150},  {500,150},  {500,330}   },
        {   {650,330},  {665,330},  {665,150},  {685,150},  {685,140},  {630,140},  {630,150},  {650,150},  {650,330}   }, //多出一根保证动画连贯
    }; //路灯结构组,路灯宽度为55px
    static POINT pointCar[] = { {40,380},   {65,380},   {90,355},   {195,355},  {215,380},  {250,380},  {250,410},  {40,410},   {40,380} };    //小车主体结构 小车宽度为210px
    static POINT pointComingCar[] = {   {30,325},   {65,325},   {90,300},   {195,300},  {215,325},  {240,325},  {240,355},  {30,355},   {30,325} };    //来车主体结构 小车宽度为210px
    static int pointComingCarWheel[][4] = { {70,335,105,370},  {155,335,190,370} }; //来车轮子
    static POINT pointComingCarRevise[] = { {30,325},   {65,325},   {90,300},   {195,300},  {215,325},  {240,325},  {240,355},  {30,355},   {30,325} };    //来车主体结构 修正用数据
    static int pointComingCarWheelRevise[][4] = { {70,335,105,370},    {155,335,190,370} }; //来车轮子 修正用数据
    /* **************** 以上为预置数据组 **************** */
 
    iShiver = -iShiver;   //翻转以产生抖动
 
    /* 刷新背景 */
    beginPaint();
    setPenColor(EMPTY);
    setBrushColor(WHITE);
    setBrushStyle(BRUSH_STYLE_SOLID);
    rectangle(0,0,600,450); 
 
    /* 绘制道路 */
    setPenWidth(10);
    setBrushColor(RGB(230,230,230));
    rectangle(0,310,600,450);
    setPenColor(YELLOW);
    line(0,320,600,320);
    line(0,440,600,440);    //马路
    setPenColor(WHITE);
    line(0,380,600,380);
 
    /* 绘制路灯 */
    setPenWidth(3);
    setPenColor(RGB(5,167,185));
    setBrushColor(RGB(5,200,220));
    for( j=0; j<5; j++)   
    {
        polygon( pointLight[j], 9 );
    }
 
    /* 绘制两车 */
    setPenWidth(5);
    /* 绘制来车 */
    setPenColor(RGB(5,167,185));
    setBrushColor(dwColor);     //dwColor由下方判断来车是否越出窗口时同时生成
    polygon(pointComingCar, 9);    //绘制车体
    setPenColor(RGB(0,0,0));
    setBrushColor(RGB(80,75,75));   //调整轮子颜色
    ellipse(pointComingCarWheel[0][0],pointComingCarWheel[0][1],pointComingCarWheel[0][2],pointComingCarWheel[0][3]);
    ellipse(pointComingCarWheel[1][0],pointComingCarWheel[1][1],pointComingCarWheel[1][2],pointComingCarWheel[1][3]);
    /* 绘制前方的车 */
    setPenColor(RGB(215,215,215));
    setBrushColor(RGB(5,200,220));
    polygon(pointCar, 9);
    setPenColor(RGB(0,0,0));
    setBrushColor(RGB(80,75,75));
    ellipse(85,390,120,425);
    ellipse(170,390,205,425);
 
    /* 下方处理绘图数据 */
    for( j=0; j<5; j++)
    {
        if( pointLight[j][3].x < -55 )   //检查路灯j是否完全越出屏幕,Light[j][3]点为最右侧的点，因此若该点越出负路灯宽度则可以认为完全越出屏幕
        {
            for( i=0; i<9; i++ ) pointLight[j][i].x += 750;        //超出则将路灯横移一窗口加一单位间距，此为600+150 
        }
        else
        {
            for( i=0; i<9; i++ ) pointLight[j][i].x -= speed;  //否则正常移动路灯，造成小车前进的错觉
        }
    }
    if( pointComingCar[6].x < -210 ) //同理检查小车是否完全越出
    {
        int iTemp = rand() % 300;
 
        for( i=0; i<9; i++ ) pointComingCar[i].x += 1020+iTemp;        //越出则横移一窗口加两车身宽度，此为600+210*2，再添加随机数值
        pointComingCarWheel[0][0] += 1020+iTemp;
        pointComingCarWheel[0][2] += 1020+iTemp;
        pointComingCarWheel[1][0] += 1020+iTemp;
        pointComingCarWheel[1][2] += 1020+iTemp;
        iCCarSpeed = rand() % 10+1; //随机产生来车速度1-10
        iShiver = iCCarSpeed / 4 * 2; //使用产生的速度产生抖动幅度
        dwColor = RGB(rand() % 255, rand() % 255, rand() % 255);  //随机产生该车颜色
    }
    else
    {
        for( i=0; i<9; i++ ) pointComingCar[i].x -= speed+iCCarSpeed;      //正常移动车身及轮子，这里speed为前车速度，iCCarSpeed为该辆小车的速度
        pointComingCarWheel[0][0] -= speed+iCCarSpeed;
        pointComingCarWheel[0][2] -= speed+iCCarSpeed;
        pointComingCarWheel[1][0] -= speed+iCCarSpeed;
        pointComingCarWheel[1][2] -= speed+iCCarSpeed;
        //使用原始组来产生抖动效果，修复因多次来车后车辆产生偏移的问题
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
 
    registerTimerEvent(&Player);    //注册定时器消息
    registerKeyboardEvent(&speedModi);  //注册键盘消息
    startTimer(1, 10);
 
    return 0;
}
