#include"PCB.cpp"

using namespace std;

PCB* runing = new PCB;//指向正在运行的进程
PCB* runinglast = new PCB;//指向正在运行的进程的上一个进程，方便调度
int Time = 0;//系统时间

PCB* creat() //创建进程列表
{
	PCB* head, * end, * current;
	head = new PCB;//分配内存
	end = head;
	int m;//进程的数目
	srand((unsigned)time(NULL));
	m = rand() % 5 + 1;//随机生成1-5个进程
	end->next = NULL;
	for (int i = 1; i <= m; i++) //生成m个进程
	{
		current = new PCB;//生成新的进程
		current->name = to_string(i);//命名
		end->next = current;//将新的进程插入
		end = current;
	}
	end->next = NULL;//将尾节点的下一个节点置为空
	PCB* p;
	p = head;//将头节点传递给p指针
	cout << "队列中的情况:" << endl;
	cout << "进程名" << '\t' << "到达时间" << '\t' << "优先数" << '\t' << "估计运行时间" << '\t' << "进程状态" << endl;
	while (p->next != NULL) {//输出初始化生成的进程数据
		p = p->next;
		cout << p->name << '\t' << p->arrivetime << '\t' << '\t' << p->grade << '\t' << p->runtime << '\t' << '\t' << p->state << endl;
	}
	cout << '\n';
	return head;//返回头指针
}

void display(PCB* head) 
{
	PCB* p = head;//将头指针传给p指针
	if (p->next == NULL) //判断链表是否为空
	{
		cout << "就绪队列中进程已全部运行完毕！"<<endl;
	}
	else 
	{
		int i = 0;
		while (p->next != NULL) 
		{
			if (p->next->arrivetime <= Time) //链表不为空，则把链表内到达时间小于等于系统时间的进程输出
			{
				if (!i)
				{
					cout << "当前就绪队列中的情况:" << endl;
					cout << "进程名" << '\t' << "到达时间" << '\t' << "优先数" << '\t' << "估计运行时间" << '\t' << "进程状态" << endl;
					i++;
				}
				p = p->next;
				cout << p->name << '\t' << p->arrivetime << '\t' << '\t' << p->grade << '\t' << p->runtime << '\t' << '\t' << p->state << endl;
			}
			else {
				p = p->next;
			}
		}
		if (!i)
		{
			cout << "就绪队列中进程已全部运行完毕！,当前就绪队列为空。";
		}
		cout << '\n';
	}
}

int run(PCB* head)	//运行进程
{
	PCB* p;
	//指针p用于遍历寻找可以处理的进程，q用于再次遍历并给当前就绪序列中其他进程优先数-1
	p = head;//将头指针传给p指针
	Time++;//系统时间加一
	while (1) //循环遍历整个链表，找出优先级最高的进程
	{
		if (p->next == NULL) //如果p指向的下一个节点为空，则代表已经遍历了链表，退出循环
		{
			break;
		}
		if ((p->next->arrivetime <= Time) && runing == NULL) 
			//若进程到达时间小于等于当前系统时间，并且当前最高优先级指针为空则用指针指向该节点
		{
			runing = p->next;//用当前运行进程指针指向第一个符合条件的进程
			runinglast = p;//用指针指向第一个符合条件的进程的上一个节点
			p = p->next;
		}
		else if (runing != NULL && (p->next->arrivetime <= Time)&&((p->next->grade) < (runing->grade)))
			//若当前最高优先级指针非空才进行比较
		{ 
				runing = p->next;
				runinglast = p;
				p = p->next;//p等于p的下一个节点	
		}
		else 
		{
			p = p->next;//如果上面都不符合，p也等于下一个节点
		}
	}

	cout << "当前时间：" << Time << endl;//输出当前系统时间
	if (runing != NULL) //如果当前运行进程指针非空，则代表就绪列表中有进程
	{
		display(head);
		cout << "当前正在运行进程：" << runing->name << "进程" << endl;
		runing->grade = (runing->grade) + 1;//优先级数加一
		runing->runtime = (runing->runtime) - 1;//预计运行时间减一
		runing->state = "Working";//状态变为运行态
		p = head;
		while(p->next!=NULL)
		{
			if (runing != NULL && (p->next->arrivetime <= Time) && (p->next != runing))
			{
				p->next->grade -= 1;
				p = p->next;
			}
			else p = p->next;
		}
		if (runing->runtime == 0) //判断进程是否完成
		{
			cout << "进程" << runing->name << "已经运行完毕，退出就绪队列！" << endl;
			runing->state = "C";//置进程的状态为完成态
			runinglast->next = runing->next;//从链表中删除该节点
			delete runing;//释放内存
			runing = NULL;//节点删除之后，把当前最高优先级指针置为空
			display(head);//输出当前就绪队列中的情况
			cout << "-------------------分割线-------------------" << endl;
		}
		else //如果没当前运行的进程没有完成，就把进程的状态切换回就绪状态，
		{
			cout << "当前进程运行完毕后，"; display(head);
			runing->state = "Ready";
			cout << "-------------------分割线-------------------" << endl;
		}
	}
	else cout << "当前没有进程在运行。"<<'\n' << "-------------------分割线-------------------" << endl;
	return 0;
}

int main() 
{ 
	runing = NULL;//一开始把当前最高优先级指针置空
	PCB* p;//声明指针
	p = creat();//创建链表，用指针接受返回的头指针
	while (p->next != NULL) //循环判断直到队列为空
	{
		run(p);
	}
	getchar();
}
