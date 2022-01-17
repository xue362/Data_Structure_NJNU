#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
template <class T, int MaxSize >
class SeqStack {
	T data[MaxSize];
	int top;
public:
	SeqStack();
	void Push(T x);
	T Pop();
	T Top();
	bool Empty();
	void StackTraverse();
};

template <class T, int MaxSize>
SeqStack<T, MaxSize>::SeqStack() {
	top = -1;
}
template <class T, int MaxSize>
void SeqStack<T, MaxSize>::Push(T x) {
	if (top == MaxSize - 1) {
		cerr << "上溢";
		exit(1);
	}
	top++;
	data[top] = x;
}
template <class T, int MaxSize>
T SeqStack<T, MaxSize>::Pop() {
	T x;
	if (top == -1) {
		cerr << "下溢";
		exit(1);
	}
	x = data[top];
	top--;
	return x;
}
template <class T, int MaxSize>
T SeqStack<T, MaxSize>::Top() {
	if (top == -1) {
		cerr << "下溢";
		exit(1);
	}
	return data[top];
}
template <class T, int MaxSize>
bool SeqStack<T, MaxSize>::Empty() {
	return top == -1;
}
template <class T, int MaxSize>
void SeqStack<T, MaxSize>::StackTraverse() {
	for (int i = 0; i <= top; i++)
		cout << data[i] << " ";
}
int cal2(int b, int a, char c)
{
	int result;
	if (c == '+') result = a + b;
	if (c == '-') result = a - b;
	if (c == '*') result = a * b;
	if (c == '/') result = a / b;
	return result;
}
int solve(string s)
{
	SeqStack<char,100> op; //运算符 
	SeqStack<int,100> number; //值 
	int num = 0;
	for (char c : s)
	{
		if (c >= '0' && c <= '9')
			num = num * 10 + c - '0';
		else
		{
			if (num) number.Push(num); 
			num = 0;
			while (c != '(' && !op.Empty() && (op.Top() == '*' || op.Top() == '/'))
				number.Push(cal2(number.Pop(), number.Pop(), op.Pop()));
			// 乘除运算符直接运算 
			if (c == ')')
			{
				while (op.Top() != '(') 
					number.Push(cal2(number.Pop(), number.Pop(), op.Pop()));
				op.Pop();
			}
			else
				op.Push(c);
		}
	}
	if (num) number.Push(num);
	while (!op.Empty()) 
		number.Push(cal2(number.Pop(), number.Pop(), op.Pop()));
	return number.Top();
}
int main() {
	string exp;
	cin >> exp;
	cout << exp<<" = (取整) "<<solve(exp) << endl;
}
