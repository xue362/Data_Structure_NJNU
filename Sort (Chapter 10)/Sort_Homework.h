#pragma once
#include<iostream>
#include"Sort.h"
#include<stack>
using namespace std;

//��һ������������������������
void Divide_Positive_Negative_int(int* data, int n)
{
	int i = 0, j = n - 1;
	while (i < j)
	{
		while (i < j && data[j] >= 0)
			j--;
		if (i < j)
			swap(data[i++], data[j]);
		while (i < j && data[i] <= 0)
			i++;
		if (i < j)
			swap(data[i], data[j--]);
	}
}

//��������ķǵݹ�ʵ��
template<class T>
void QuickSort_Stack(T* data, int n)
{
	int i = 0, j = n - 1;
	stack<int> s;
	s.push(i);
	s.push(j);
	while (!s.empty())
	{
		int j = s.top();//�����Ҳ�ģ���ȡ�Ҳ�
		s.pop();
		int i = s.top();
		s.pop();
		int pivot = QS_partition(data, i, j);
		if (pivot - 1 > i)
		{
			s.push(i);
			s.push(pivot - 1);
		}
		if (pivot + 1 < j)
		{
			s.push(pivot + 1);
			s.push(j);
		}
	}
}