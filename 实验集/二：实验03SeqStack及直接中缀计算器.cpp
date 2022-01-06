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
int getPripority(char ch) {
	switch (ch) {
	case '(':
		return 1;
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
		return 3;
	default:
		return 0;
	}
}
bool isNum(char ch) {
	if (ch >= '0' && ch <= '9')
		return true;
	return false;
}
int cal(int a, int b, char ch) {
	int result;
	switch (ch) {
	case '+':
		result = a + b;
		break;
	case '-':
		result = a - b;
		break;
	case '*':
		result = a * b;
		break;
	case '/':
		result = a / b;
		break;
	}
	return result;
}
int Calmain(string exp) {
	SeqStack<char, 100> op;
	SeqStack<int, 100> number;
	int len = exp.size();
	for (int i = 0; i < len; i++) {
		if (exp[i] == ' ')continue;
		if (isNum(exp[i])) {
			int num = 0;
			while (i < len && isNum(exp[i])) {
				num = num * 10 + (exp[i] - '0');
				i++;
			}
			i--;
			number.Push(num);
		}
		else {
			int score = getPripority(exp[i]);
			if (op.Empty() || exp[i] == '(' || score > getPripority(op.Top())) {
				op.Push(exp[i]);
			}
			else {
				while (!op.Empty() && score <= getPripority(op.Top())) {
					if (op.Top() == '(') {
						//如果栈顶为左括号,括号内运算完毕
						op.Pop();
						break;
					}
					char ch = op.Pop();
					int b = number.Pop();
					int a = number.Pop();
					int result = cal(a, b, ch);
					number.Push(result);
				}
				if (exp[i] != ')')
					op.Push(exp[i]);
			}
		}
	}
	while (!op.Empty()) { //处理完整个字符串之后把栈所有符号都输出
		char ch = op.Pop();
		int b = number.Pop();
		int a = number.Pop();
		int result = cal(a, b, ch);//计算
		number.Push(result);
	}
	return number.Top();
}
int main() {
	string exp;
	cin >> exp;
	cout << exp<<" = (取整) "<<Calmain(exp) << endl;
}
