#pragma once

#include<iostream>
using namespace std;
#define Record int

//顺序查找
int SeqSearch(Record* r, int n, int k)
{
	int i;
	for (i = 0; i < n && r[i] != k; i++);
	if (i < n)
		return i;
	else
		return -1;
}

int SeqSearch_Guard(Record* r, int n, int k)
{
	r[n] = k;//需求多一个数据空间
	int i = 0;
	while (r[i] != k)
		i++;
	if (i < n)
		return i;
	else 
		return -1;
}

//二分查找
int BiSearch_Circ(Record* r, int n, int k)
{
	int low = 0, high = n - 1, mid = 0;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (r[mid] == k)
			return mid;
		if (r[mid] < k)
			low = mid + 1;
		if (r[mid] > k)
			high = mid - 1;
	}
	return -1;
}

int BiSearch_Recu(Record* r, int low, int high, int k)
{
	if (low > high)
		return -1;
	int mid = (low + high) / 2;
	if (r[mid] == k)
		return mid;
	if (r[mid] < k)
		return BiSearch_Recu(r, mid + 1, high, k);
	else return BiSearch_Recu(r, low, mid - 1, k);
}