#include "acllib.h"

int Setup()
{
	initWindow("D:\\Desktop\\hello.exe",0,0,661,404);
	
	beginPaint();
	
	rectangle(2,2,638,402);
	
	setTextSize(14);
    setTextColor(RGB(192,192,192));  
    setTextBkColor(BLACK);
    paintText(2,6,"Hello World!");
	paintText(2,39,"--------------------------------");
	paintText(3,54,"Process exited after 0.05644 seconds with return value 0");
	setTextSize(16);
	paintText(3,69,"请按任意键继续. . . ");
	
	setPenColor(RGB(160,160,160));
	line(0,0,0,403);
	line(1,0,660,0);
	
	setPenColor(RGB(105,105,105));
	line(1,1,1,402);
	line(2,1,659,1);
	
	setPenColor(RGB(227,227,227));
	line(1,402,660,402);
	line(659,1,659,402);
	line(639,2,639,20);
	line(639,49,639,402);
	
	setPenColor(RGB(248,248,248));
	line(638,2,638,402);
	
	putPixel(651,9,RGB(45,45,45));
	putPixel(650,10,RGB(30,30,30));
	putPixel(651,10,RGB(53,53,53));
	putPixel(652,10,RGB(91,91,91));
	putPixel(649,11,RGB(33,33,33));
	putPixel(650,11,RGB(73,73,73));
	putPixel(651,11,RGB(121,121,121));
	putPixel(652,11,RGB(140,140,140));
	putPixel(653,11,RGB(134,134,134));
	putPixel(648,12,RGB(85,85,85));
	putPixel(649,12,RGB(119,119,119));
	putPixel(650,12,RGB(157,157,157));
	putPixel(651,12,RGB(174,174,174));
	putPixel(652,12,RGB(183,183,183));
	putPixel(653,12,RGB(191,191,191));
	putPixel(654,12,RGB(182,182,182));
	
	putPixel(648,392,RGB(48,48,48));
	putPixel(649,392,RGB(37,37,37));
	putPixel(650,392,RGB(37,37,37));
	putPixel(651,392,RGB(40,40,40));
	putPixel(652,392,RGB(60,60,60));
	putPixel(653,392,RGB(102,102,102));
	putPixel(654,392,RGB(140,140,140));
	putPixel(649,393,RGB(85,85,85));
	putPixel(650,393,RGB(95,95,95));
	putPixel(651,393,RGB(121,121,121));
	putPixel(652,393,RGB(165,165,165));
	putPixel(653,393,RGB(191,191,191));
	putPixel(650,394,RGB(117,117,117));
	putPixel(651,394,RGB(169,169,169));
	putPixel(652,394,RGB(204,204,204));
	putPixel(651,395,RGB(172,172,172));
	
	setPenColor(RGB(60,127,177));
	line(639,20,639,49);
	line(659,20,659,49);
	line(640,20,659,20);
	line(640,48,659,48);
	
	setPenColor(RGB(0,0,0));
	line(644,30,655,30);
	line(644,31,655,31);
	line(644,34,655,34);
	line(644,35,655,35);
	line(644,38,655,38);
	line(644,39,655,39);
	
	endPaint();	
}
