#include<string>
#include<stdlib.h>	
#include<ctime>
#include<iostream>

using namespace std;

struct PCB {
	string name;//进程名
	PCB* next;//链接指针
	int arrivetime;//到达时间
	int grade;//进程的优先级
	int runtime;//预计运行时间
	string state;//进程状态

	PCB()//构造函数，初始化进程数据
	{
		arrivetime = rand() % 5 + 1;//到达时间，分配一个1-5的随机数
		grade = rand() % 5 + 1;//优先级，分配一个1-5的随机数
		runtime = rand() % 5 + 1;//估计运行时间，分配一个1-5的随机数
		state = "Ready";//置初始状态为就绪状态
	}
};


