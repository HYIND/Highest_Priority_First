#include<string>
#include<stdlib.h>	
#include<ctime>
#include<iostream>

using namespace std;

struct PCB {
	string name;//������
	PCB* next;//����ָ��
	int arrivetime;//����ʱ��
	int grade;//���̵����ȼ�
	int runtime;//Ԥ������ʱ��
	string state;//����״̬

	PCB()//���캯������ʼ����������
	{
		arrivetime = rand() % 5 + 1;//����ʱ�䣬����һ��1-5�������
		grade = rand() % 5 + 1;//���ȼ�������һ��1-5�������
		runtime = rand() % 5 + 1;//��������ʱ�䣬����һ��1-5�������
		state = "Ready";//�ó�ʼ״̬Ϊ����״̬
	}
};


