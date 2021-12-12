#pragma once
#include<iostream>
#include<vector>

using namespace std;
template<class T>
void BubbleSort(T* data, int n)
{
	bool end = false;
	for (int i = 1; i < n; i++)
	{
		if (end == true)
			break;
		end = true;
		for (int j = 0; j < n - 1; j++)
			if (data[j] > data[j + 1])
			{
				swap(data[j], data[j + 1]);
				/*
				T tmp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = tmp;
				*/
				end = false;
			}
	}
}

template<class T>
void SelectSort(T* data, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int k = i;
		for (int j = i + 1; j < n; j++)
			if (data[j] < data[k])
				k = j;
		if (k != i)
			swap(data[k], data[i]);
	}
}

template<class T>
void InsertSort(T* data, int n)
{
	for (int i = 1; i < n; i++)
	{
		T tmp = data[i];
		int j;
		for (j = j - 1; j >= 0 && tmp < data[j]; j--)
			data[j + 1] = data[j];
		data[j + 1] = tmp;
	}
}


template<class T>
void ShellSort(T* data, int n)
{
	for(int d=n/2;d>0;d/=2)
		for (int i = d; i < n; i++)
		{
			T tmp = data[i];
			int j;
			for (j = i - d; j >= 0 && tmp < data[j]; j--)
				data[j + d] = data[j];
			data[j + d] = tmp;
		}
}

template<class T>
int QS_partition(T* data, int i, int j)
{
	T tmp = data[i];
	while (i < j)
	{
		while (i < j && data[j] >= tmp)
			j--;
		if (i < j)
			data[i++] = data[j];
		while (i < j && data[i] <= tmp)
			i++;
		if (i < j)
			data[j--] = data[i];
	}
	data[i] = tmp;
	return i;
}
template<class T>
void QuickSort(T* data, int i, int j)
{
	if (i < j)
	{
		int pivot = QS_partition(data, i, j);
		QuickSort(data, i, pivot - 1);
		QuickSort(data, pivot + 1, j);
	}
}
template<class T>
void QuickSort(T* data, int len)
{
	QuickSort(data, 0, len - 1);
}