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
		cerr << "上溢"; exit(1);
	}
	rear = (rear + 1) % MaxSize;
	data[rear] = x;
}
template <class T, int MaxSize>
T SeqQueue<T, MaxSize>::DeQueue()
{
	if (rear == front)
	{
		cerr << "下溢"; exit(1);
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
	cout << "已初始化\n";
	while (opt == true)
	{
		system("pause");
		system("cls");
		cout << "**********\n";
		cout << "*0.退  出*\n";
		cout << "*1.排  队*\n";
		cout << "*2.就  诊*\n";
		cout << "*3.查  看*\n";
		cout << "*4.人  数*\n";
		cout << "**********\n";
		cout << "选择：";
		char x;
		cin >> x;
		system("cls");
		switch (x)
		{
		case '0':
			opt = 0;
			break;
		case '1':
			cout << "你选择了1\n";
			srand((int)time(0));
			n = rand() % 100;
			SQueue.EnQueue(n);
			cout << n << "号入队等待" << endl;
			break;
		case '2':
			cout << "你选择了2\n";
			cout << SQueue.DeQueue() << "号就诊" << endl;
			break;
		case '3':
			cout << "你选择了3\n";
			SQueue.PrintQueue();
			break;
		case '4':
			cout << "你选择了4\n长度为  ";
			cout << SQueue.Length() << endl;
			break;
		default:
			cout << "输入非法，请重新选择!\n";
			break;
		}

	}
	cout << "已退出!\n";
}
int main()
{
	Clinic();
}