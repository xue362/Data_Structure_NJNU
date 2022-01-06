#include <iostream>
#include <algorithm>
#include <string>
#include <time.h>
using namespace std;

template <class T, int MaxSize >
class SeqQueue
{
	T data[MaxSize];
	int front, rear;
public:
	SeqQueue();
	void EnQueue(T x);
	T DeQueue();
	T GetQueue();
	bool Empty();
	int Length();
	void PrintQueue();
};
template <class T, int MaxSize>
SeqQueue<T, MaxSize>::SeqQueue()
{
	front = rear = 0;
}
template <class T, int MaxSize>
void SeqQueue<T, MaxSize>::EnQueue(T x)
{
	if ((rear + 1) % MaxSize == front)
	{
		cerr << "����"; exit(1);
	}
	rear = (rear + 1) % MaxSize;
	data[rear] = x;
}
template <class T, int MaxSize>
T SeqQueue<T, MaxSize>::DeQueue()
{
	if (rear == front)
	{
		cerr << "����"; exit(1);
	}
	front = (front + 1) % MaxSize;
	return data[front];
}
template<class T, int MaxSize>
T SeqQueue<T, MaxSize>::GetQueue()
{
	return data[(front + 1) % MaxSize];
}
template<class T, int MaxSize>
bool SeqQueue<T, MaxSize>::Empty()
{
	return rear == front;
}
template <class T, int MaxSize>
int SeqQueue<T, MaxSize>::Length()
{
	return (rear - front + MaxSize) % MaxSize;
}
template<class T, int MaxSize>
void SeqQueue<T, MaxSize>::PrintQueue()
{
	if (rear == front) return;
	int i = front;
	while (i != rear)
	{
		i = (i + 1) % MaxSize;
		cout << data[i] << " ";
	}
	cout << endl;
}

void Clinic()
{
	SeqQueue <int, 100>SQueue;
	bool opt = true;
	int n;
	cout << "�ѳ�ʼ��\n";
	while (opt == true)
	{
		system("pause");
		system("cls");
		cout << "**********\n";
		cout << "*0.��  ��*\n";
		cout << "*1.��  ��*\n";
		cout << "*2.��  ��*\n";
		cout << "*3.��  ��*\n";
		cout << "*4.��  ��*\n";
		cout << "**********\n";
		cout << "ѡ��";
		char x;
		cin >> x;
		system("cls");
		switch (x)
		{
		case '0':
			opt = 0;
			break;
		case '1':
			cout << "��ѡ����1\n";
			srand((int)time(0));
			n = rand() % 100;
			SQueue.EnQueue(n);
			cout << n << "����ӵȴ�" << endl;
			break;
		case '2':
			cout << "��ѡ����2\n";
			cout << SQueue.DeQueue() << "�ž���" << endl;
			break;
		case '3':
			cout << "��ѡ����3\n";
			SQueue.PrintQueue();
			break;
		case '4':
			cout << "��ѡ����4\n����Ϊ  ";
			cout << SQueue.Length() << endl;
			break;
		default:
			cout << "����Ƿ���������ѡ��!\n";
			break;
		}

	}
	cout << "���˳�!\n";
}
int main()
{
	Clinic();
}