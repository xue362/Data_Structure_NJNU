#pragma once
#include<iostream>
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
template<class T>
void HS_Sift(T* data, int k, int m)
{
	int i = k, j = 2 * i;
	while (j <= m)
	{
		if (j < m && data[j] < data[j + 1])
			j++;
		if (data[i] > data[j])
			break;
		else
		{
			swap(data[i], data[j]);
			i = j;
			j = 2 * i;
		}
	}
}
template<class T>
void HeapSort(T* data, int n)
{
	for (int i = n / 2; i >= 0; i--)
		HS_Sift(data, i, n);
	for (int i = 1; i < n; i++)
	{
		swap(data[1], data[n - i + 1]);
		HS_Sift(data, 1, n - i);
	}
}
template<class T>
void Merge(T* r, T* r1, int s, int m, int t)
{
	int i = s,
		j = m + 1,
		k = s;
	while (i <= m && j <= t)
		if (r[i] <= r[j])
			r1[k++] = r[i++];
		else r1[k++] = r[j++];
	while (i <= m)
		r1[k++] = r[i++];
	while (j <= t)
		r1[k++] = r[j++];
}
template<class T>
void MergeSort_Recu(T* r, T* r1, int s, int t, int len=0)
{
	if (s == t)
		r1[s] = r[s];
	else {
		T* r2 = new T[len];
		int m = (s + t) / 2;
		MergeSort_Recu(r, r2, s, m);
		MergeSort_Recu(r, r2, m + 1, t);
		Merge(r2, r1, s, m, t);
	}
}
template<class T>
void MergeSort(T* r, int len)
{
	T* r1 = new T[len];
	MergeSort_Recu(r, r1, 0, len - 1, len);
	for (int i = 0; i < len; i++)
		cout << r1[i] << " ";
	cout << endl;
}