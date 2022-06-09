/******************************************************************/ 
/* 基于基本遗传算法的函数最优化 SGA.C */ 
/* A Function Optimizer using Simple Genetic Algorithm */ 
/* developed from the Pascal SGA code presented by David E.Goldberg */ 
//******************************************************************/ 
#include 
#include 
#include 
#include "graph.c" 
/* 全局变量 */ 
struct individual /* 个体*/ 
{ 
unsigned *chrom; /* 染色体 */ 
double fitness; /* 个体适应度*/ 
double varible; /* 个体对应的变量值*/ 
int xsite; /* 交叉位置 */ 
int parent[2]; /* 父个体 */ 
int *utility; /* 特定数据指针变量 */ 
}; 
struct bestever /* 最佳个体*/ 
{ 
unsigned *chrom; /* 最佳个体染色体*/ 
double fitness; /* 最佳个体适应度 */ 
double varible; /* 最佳个体对应的变量值 */ 
int generation; /* 最佳个体生成代 */ 
}; 
struct individual *oldpop; /* 当前代种群 */ 
struct individual *newpop; /* 新一代种群 */ 
struct bestever bestfit; /* 最佳个体 */ 
double sumfitness; /* 种群中个体适应度累计 */ 
double max; /* 种群中个体最大适应度 */ 
double avg; /* 种群中个体平均适应度 */ 
double min; /* 种群中个体最小适应度 */ 
float pcross; /* 交叉概率 */ 
float pmutation; /* 变异概率 */ 
int popsize; /* 种群大小 */ 
int lchrom; /* 染色体长度*/ 
int chromsize; /* 存储一染色体所需字节数 */ 
int gen; /* 当前世代数 */ 
int maxgen; /* 最大世代数 */ 
int run; /* 当前运行次数 */ 
int maxruns; /* 总运行次数 */ 
int printstrings; /* 输出染色体编码的判断，0 -- 不输出, 1 -- 输出 */ 
int nmutation; /* 当前代变异发生次数 */ 
int ncross; /* 当前代交叉发生次数 */ 

/* 随机数发生器使用的静态变量 */ 
static double oldrand[55]; 
static int jrand; 
static double rndx2; 
static int rndcalcflag; 
/* 输出文件指针 */ 
FILE *outfp ; 
/* 函数定义 */ 
void advance_random(); 
int flip(float);rnd(int, int); 
void randomize(); 
double randomnormaldeviate(); 
float randomperc(),rndreal(float,float); 
void warmup_random(float); 
void initialize(),initdata(),initpop(); 
void initreport(),generation(),initmalloc(); 
void freeall(),nomemory(char *),report(); 
void writepop(),writechrom(unsigned *); 
void preselect(); 
void statistics(struct individual *); 
void title(),repchar (FILE *,char *,int); 
void skip(FILE *,int); 
int select(); 
void objfunc(struct individual *); 
int crossover (unsigned *, unsigned *, unsigned *, unsigned *); 
void mutation(unsigned *); 


void initialize() /* 遗传算法初始化 */ 
{ 
/* 键盘输入遗传算法参数 */ 
initdata(); 
/* 确定染色体的字节长度 */ 
chromsize = (lchrom/(8*sizeof(unsigned))); 
if(lchrom%(8*sizeof(unsigned))) chromsize++; 
/*分配给全局数据结构空间 */ 
initmalloc(); 
/* 初始化随机数发生器 */ 
randomize(); 
/* 初始化全局计数变量和一些数值*/ 
nmutation = 0; 
ncross = 0; 
bestfit.fitness = 0.0; 
bestfit.generation = 0; 
/* 初始化种群，并统计计算结果 */ 
initpop(); 
statistics(oldpop); 
initreport(); 
} 

void initdata() /* 遗传算法参数输入 */ 
{ 
char answer[2]; 
setcolor(9); 
disp_hz16("种群大小(20-100)：",100,150,20); 
gscanf(320,150,9,15,4,"%d", &popsize); 
if((popsize%2) != 0) 
{ 
fprintf(outfp, "种群大小已设置为偶数\n"); 
popsize++; 
}; 
setcolor(9); 
disp_hz16("染色体长度(8-40)：",100,180,20); 
gscanf(320,180,9,15,4,"%d", &lchrom); 
setcolor(9); 
disp_hz16("是否输出染色体编码(y/n)：",100,210,20); 
printstrings=1; 
gscanf(320,210,9,15,4,"%s", answer); 
if(strncmp(answer,"n",1) == 0) printstrings = 0; 
setcolor(9); 
disp_hz16("最大世代数(100-300)：",100,240,20); 
gscanf(320,240,9,15,4,"%d", &maxgen); 
setcolor(9); 
disp_hz16("交叉率(0.2-0.9)：",100,270,20); 
gscanf(320,270,9,15,5,"%f", &pcross); 
setcolor(9); 
disp_hz16("变异率(0.01-0.1)：",100,300,20); 
gscanf(320,300,9,15,5,"%f", &pmutation); 
} 

void initpop() /* 随机初始化种群 */ 
{ 
int j, j1, k, stop; 
unsigned mask = 1; 
for(j = 0; j < popsize; j++) 
{ 
for(k = 0; k < chromsize; k++) 
{ 
oldpop[j].chrom[k] = 0; 
if(k == (chromsize-1)) 
stop = lchrom - (k*(8*sizeof(unsigned))); 
else 
stop =8*sizeof(unsigned); 
for(j1 = 1; j1 <= stop; j1++) 
{ 
oldpop[j].chrom[k] = oldpop[j].chrom[k]<<1; 
if(flip(0.5)) 
oldpop[j].chrom[k] = oldpop[j].chrom[k]|mask; 
} 
} 
oldpop[j].parent[0] = 0; /* 初始父个体信息 */ 
oldpop[j].parent[1] = 0; 
oldpop[j].xsite = 0; 
objfunc(&(oldpop[j])); /* 计算初始适应度*/ 
} 
} 

void initreport() /* 初始参数输出 */ 
{ 
void skip(); 
skip(outfp,1); 
fprintf(outfp," 基本遗传算法参数\n"); 
fprintf(outfp," -------------------------------------------------\n"); 
fprintf(outfp," 种群大小(popsize) = %d\n",popsize); 
fprintf(outfp," 染色体长度(lchrom) = %d\n",lchrom); 
fprintf(outfp," 最大进化代数(maxgen) = %d\n",maxgen); 
fprintf(outfp," 交叉概率(pcross) = %f\n", pcross); 
fprintf(outfp," 变异概率(pmutation) = %f\n", pmutation); 
fprintf(outfp," -------------------------------------------------\n"); 
skip(outfp,1); 
fflush(outfp); 
} 

void generation() 
{ 
int mate1, mate2, jcross, j = 0; 
/* 每代运算前进行预选 */ 
preselect(); 
/* 选择, 交叉, 变异 */ 
do 
{ 
/* 挑选交叉配对 */ 
mate1 = select(); 
mate2 = select(); 
/* 交叉和变异 */ 
jcross = crossover(oldpop[mate1].chrom, oldpop[mate2].chrom, newpop[j].chrom, newpop[j+1].chrom); 
mutation(newpop[j].chrom); 
mutation(newpop[j+1].chrom); 
/* 解码, 计算适应度 */ 
objfunc(&(newpop[j])); 
/*记录亲子关系和交叉位置 */ 
newpop[j].parent[0] = mate1+1; 
newpop[j].xsite = jcross; 
newpop[j].parent[1] = mate2+1; 
objfunc(&(newpop[j+1])); 
newpop[j+1].parent[0] = mate1+1; 
newpop[j+1].xsite = jcross; 
newpop[j+1].parent[1] = mate2+1; 
j = j + 2; 
} 
while(j < (popsize-1)); 

} 

void initmalloc() /*为全局数据变量分配空间 */ 
{ 
unsigned nbytes; 
char *malloc(); 
int j; 
/* 分配给当前代和新一代种群内存空间 */ 
nbytes = popsize*sizeof(struct individual); 
if((oldpop = (struct individual *) malloc(nbytes)) == NULL) 
nomemory("oldpop"); 
if((newpop = (struct individual *) malloc(nbytes)) == NULL) 
nomemory("newpop"); 
/* 分配给染色体内存空间 */ 
nbytes = chromsize*sizeof(unsigned); 
for(j = 0; j < popsize; j++) 
{ 
if((oldpop[j].chrom = (unsigned *) malloc(nbytes)) == NULL) 
nomemory("oldpop chromosomes"); 
if((newpop[j].chrom = (unsigned *) malloc(nbytes)) == NULL) 
nomemory("newpop chromosomes"); 
} 
if((bestfit.chrom = (unsigned *) malloc(nbytes)) == NULL) 
nomemory("bestfit chromosome"); 

} 

void freeall() /* 释放内存空间 */ 
{ 
int i; 
for(i = 0; i < popsize; i++) 
{ 
free(oldpop[i].chrom); 
free(newpop[i].chrom); 
} 
free(oldpop); 
free(newpop); 
free(bestfit.chrom); 
} 

void nomemory(string) /* 内存不足，退出*/ 
char *string; 
{ 
fprintf(outfp,"malloc: out of memory making %s!!\n",string); 
exit(-1); 
} 

void report() /* 输出种群统计结果 */ 
{ 
void repchar(), skip(); 
void writepop(), writestats(); 
repchar(outfp,"-",80); 
skip(outfp,1); 
if(printstrings == 1) 
{ 
repchar(outfp," ",((80-17)/2)); 
fprintf(outfp,"模拟计算统计报告 \n"); 
fprintf(outfp, "世代数 %3d", gen); 
repchar(outfp," ",(80-28)); 
fprintf(outfp, "世代数 %3d\n", (gen+1)); 
fprintf(outfp,"个体 染色体编码"); 
repchar(outfp," ",lchrom-5); 
fprintf(outfp,"适应度 父个体 交叉位置 "); 
fprintf(outfp,"染色体编码 "); 
repchar(outfp," ",lchrom-5); 
fprintf(outfp,"适应度\n"); 
repchar(outfp,"-",80); 
skip(outfp,1); 
writepop(outfp); 
repchar(outfp,"-",80); 
skip(outfp,1); 
} 
fprintf(outfp,"第 %d 代统计: \n",gen); 
fprintf(outfp,"总交叉操作次数 = %d, 总变异操作数 = %d\n",ncross,nmutation); 
fprintf(outfp," 最小适应度：%f 最大适应度：%f 平均适应度 %f\n", min,max,avg); 
fprintf(outfp," 迄今发现最佳个体 => 所在代数： %d ", bestfit.generation); 
fprintf(outfp," 适应度：%f 染色体：", bestfit.fitness); 
writechrom((&bestfit)->chrom); 
fprintf(outfp," 对应的变量值: %f", bestfit.varible); 
skip(outfp,1); 
repchar(outfp,"-",80); 
skip(outfp,1); 
} 

void writepop() 
{ 
struct individual *pind; 
int j; 
for(j=0; j { 
fprintf(outfp,"%3d) ",j+1); 
/* 当前代个体 */ 
pind = &(oldpop[j]); 
writechrom(pind->chrom); 
fprintf(outfp," %8f | ", pind->fitness); 
/* 新一代个体 */ 
pind = &(newpop[j]); 
fprintf(outfp,"(%2d,%2d) %2d ", 
pind->parent[0], pind->parent[1], pind->xsite); 
writechrom(pind->chrom); 
fprintf(outfp," %8f\n", pind->fitness); 
} 
} 

void writechrom(chrom) /* 输出染色体编码 */ 
unsigned *chrom; 
{ 
int j, k, stop; 
unsigned mask = 1, tmp; 
for(k = 0; k < chromsize; k++) 
{ 
tmp = chrom[k]; 
if(k == (chromsize-1)) 
stop = lchrom - (k*(8*sizeof(unsigned))); 
else 
stop =8*sizeof(unsigned); 
for(j = 0; j < stop; j++) 
{ 
if(tmp&mask) 
fprintf(outfp,"1"); 
else 
fprintf(outfp,"0"); 
tmp = tmp>>1; 
} 
} 
} 

void preselect() 
{ 
int j; 
sumfitness = 0; 
for(j = 0; j < popsize; j++) sumfitness += oldpop[j].fitness; 
} 

int select() /* 轮盘赌选择*/ 
{ 
extern float randomperc(); 
float sum, pick; 
int i; 
pick = randomperc(); 
sum = 0; 
if(sumfitness != 0) 
{ 
for(i = 0; (sum < pick) && (i < popsize); i++) 
sum += oldpop[i].fitness/sumfitness; 
} 
else 
i = rnd(1,popsize); 
return(i-1); 
} 

void statistics(pop) /* 计算种群统计数据 */ 
struct individual *pop; 
{ 
int i, j; 
sumfitness = 0.0; 
min = pop[0].fitness; 
max = pop[0].fitness; 
/* 计算最大、最小和累计适应度 */ 
for(j = 0; j < popsize; j++) 
{ 
sumfitness = sumfitness + pop[j].fitness; 
if(pop[j].fitness > max) max = pop[j].fitness; 
if(pop[j].fitness < min) min = pop[j].fitness; 
/* new global best-fit individual */ 
if(pop[j].fitness > bestfit.fitness) 
{ 
for(i = 0; i < chromsize; i++) 
bestfit.chrom[i] = pop[j].chrom[i]; 
bestfit.fitness = pop[j].fitness; 
bestfit.varible = pop[j].varible; 
bestfit.generation = gen; 
} 
} 
/* 计算平均适应度 */ 
avg = sumfitness/popsize; 
} 

void title() 
{ 
settextstyle(0,0,4); 
gprintf(110,15,4,0,"SGA Optimizer"); 
setcolor(9); 
disp_hz24("基本遗传算法",220,60,25); 
} 

void repchar (outfp,ch,repcount) 
FILE *outfp; 
char *ch; 
int repcount; 
{ 
int j; 
for (j = 1; j <= repcount; j++) fprintf(outfp,"%s", ch); 
} 

void skip(outfp,skipcount) 
FILE *outfp; 
int skipcount; 
{ 
int j; 
for (j = 1; j <= skipcount; j++) fprintf(outfp,"\n"); 
} 

void objfunc(critter) /* 计算适应度函数值 */ 
struct individual *critter; 
{ 
unsigned mask=1; 
unsigned bitpos; 
unsigned tp; 
double pow(), bitpow ; 
int j, k, stop; 
critter->varible = 0.0; 
for(k = 0; k < chromsize; k++) 
{ 
if(k == (chromsize-1)) 
stop = lchrom-(k*(8*sizeof(unsigned))); 
else 
stop =8*sizeof(unsigned); 
tp = critter->chrom[k]; 
for(j = 0; j < stop; j++) 
{ 
bitpos = j + (8*sizeof(unsigned))*k; 
if((tp&mask) == 1) 
{ 
bitpow = pow(2.0,(double) bitpos); 
critter->varible = critter->varible + bitpow; 
} 
tp = tp>>1; 
} 
} 
critter->varible =-1+critter->varible*3/(pow(2.0,(double)lchrom)-1); 
critter->fitness =critter->varible*sin(critter->varible*10*atan(1)*4)+2.0; 
} 

void mutation(unsigned *child) /*变异操作*/ 
{ 
int j, k, stop; 
unsigned mask, temp = 1; 
for(k = 0; k < chromsize; k++) 
{ 
mask = 0; 
if(k == (chromsize-1)) 
stop = lchrom - (k*(8*sizeof(unsigned))); 
else 
stop = 8*sizeof(unsigned); 
for(j = 0; j < stop; j++) 
{ 
if(flip(pmutation)) 
{ 
mask = mask|(temp< nmutation++; 
} 
} 
child[k] = child[k]^mask; 
} 
} 

int crossover (unsigned *parent1, unsigned *parent2, unsigned *child1, unsigned *child2) 
/* 由两个父个体交叉产生两个子个体 */ 
{ 
int j, jcross, k; 
unsigned mask, temp; 
if(flip(pcross)) 
{ 
jcross = rnd(1 ,(lchrom - 1));/* Cross between 1 and l-1 */ 
ncross++; 
for(k = 1; k <= chromsize; k++) 
{ 
if(jcross >= (k*(8*sizeof(unsigned)))) 
{ 
child1[k-1] = parent1[k-1]; 
child2[k-1] = parent2[k-1]; 
} 
else if((jcross < (k*(8*sizeof(unsigned)))) && (jcross > ((k-1)*(8*sizeof(unsigned))))) 
{ 
mask = 1; 
for(j = 1; j <= (jcross-1-((k-1)*(8*sizeof(unsigned)))); j++) 
{ 
temp = 1; 
mask = mask<<1; 
mask = mask|temp; 
} 
child1[k-1] = (parent1[k-1]&mask)|(parent2[k-1]&(~mask)); 
child2[k-1] = (parent1[k-1]&(~mask))|(parent2[k-1]&mask); 
} 
else 
{ 
child1[k-1] = parent2[k-1]; 
child2[k-1] = parent1[k-1]; 
} 
} 
} 
else 
{ 
for(k = 0; k < chromsize; k++) 
{ 
child1[k] = parent1[k]; 
child2[k] = parent2[k]; 
} 
jcross = 0; 
} 
return(jcross); 
} 

void advance_random() /* 产生55个随机数 */ 
{ 
int j1; 
double new_random; 
for(j1 = 0; j1 < 24; j1++) 
{ 
new_random = oldrand[j1] - oldrand[j1+31]; 
if(new_random < 0.0) new_random = new_random + 1.0; 
oldrand[j1] = new_random; 
} 
for(j1 = 24; j1 < 55; j1++) 
{ 
new_random = oldrand [j1] - oldrand [j1-24]; 
if(new_random < 0.0) new_random = new_random + 1.0; 
oldrand[j1] = new_random; 
} 
} 

int flip(float prob) /* 以一定概率产生0或1 */ 
{ 
float randomperc(); 
if(randomperc() <= prob) 
return(1); 
else 
return(0); 
} 

void randomize() /* 设定随机数种子并初始化随机数发生器 */ 
{ 
float randomseed; 
int j1; 
for(j1=0; j1<=54; j1++) 
oldrand[j1] = 0.0; 
jrand=0; 
do 
{ 
setcolor(9); 
disp_hz16("随机数种子[0-1]:",100,330,20); 
gscanf(320,330,9,15,4,"%f", &randomseed); 
} 
while((randomseed < 0.0) || (randomseed > 1.0)); 
warmup_random(randomseed); 
} 

double randomnormaldeviate() /* 产生随机标准差 */ 
{ 
double sqrt(), log(), sin(), cos(); 
float randomperc(); 
double t, rndx1; 
if(rndcalcflag) 
{ rndx1 = sqrt(- 2.0*log((double) randomperc())); 
t = 6.2831853072 * (double) randomperc(); 
rndx2 = rndx1 * sin(t); 
rndcalcflag = 0; 
return(rndx1 * cos(t)); 
} 
else 
{ 
rndcalcflag = 1; 
return(rndx2); 
} 
} 

float randomperc() /*与库函数random()作用相同, 产生[0,1]之间一个随机数 */ 
{ 
jrand++; 
if(jrand >= 55) 
{ 
jrand = 1; 
advance_random(); 
} 
return((float) oldrand[jrand]); 
} 

int rnd(low, high) /*在整数low和high之间产生一个随机整数*/ 
int low,high; 
{ 
int i; 
float randomperc(); 
if(low >= high) 
i = low; 
else 
{ 
i = (randomperc() * (high - low + 1)) + low; 
if(i > high) i = high; 
} 
return(i); 
} 


void warmup_random(float random_seed) /* 初始化随机数发生器*/ 
{ 
int j1, ii; 
double new_random, prev_random; 

oldrand[54] = random_seed; 
new_random = 0.000000001; 
prev_random = random_seed; 
for(j1 = 1 ; j1 <= 54; j1++) 
{ 
ii = (21*j1)%54; 
oldrand[ii] = new_random; 
new_random = prev_random-new_random; 
if(new_random<0.0) new_random = new_random + 1.0; 
prev_random = oldrand[ii]; 
} 
advance_random(); 
advance_random(); 
advance_random(); 
jrand = 0; 
} 


main(argc,argv) /* 主程序 */ 
int argc; 
char *argv[]; 
{ 
struct individual *temp; 
FILE *fopen(); 
void title(); 
char *malloc(); 
if((outfp = fopen(argv[1],"w")) == NULL) 
{ 
fprintf(stderr,"Cannot open output file %s\n",argv[1]); 
exit(-1); 
} 
g_init(); 
setcolor(9); 
title(); 
disp_hz16("输入遗传算法执行次数(1-5):",100,120,20); 
gscanf(320,120,9,15,4,"%d",&maxruns); 
for(run=1; run<=maxruns; run++) 
{ 
initialize(); 
for(gen=0; gen { 
fprintf(outfp,"\n第 %d / %d 次运行: 当前代为 %d, 共 %d 代\n", run,maxruns,gen,maxgen); 
/* 产生新一代 */ 
generation(); 
/* 计算新一代种群的适应度统计数据 */ 
statistics(newpop); 
/* 输出新一代统计数据 */ 
report(); 
temp = oldpop; 
oldpop = newpop; 
newpop = temp; 
} 
freeall(); 
} 
} 
