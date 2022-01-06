#pragma once
#include<string>
#include<iostream>
#include<vector>
using namespace std;
struct HNode
{
	char data;
	double weight;
	int parent, lchild, rchild;
};

class HTree
{
private:

	vector<HNode> hufftree;
	int n;
public:
	HTree(vector<HNode>& leaves);
	void SelectSmall(int& least, int& less, int i, vector<bool> &select);
	void SelectSmall(int& least, int& less, int i);
	vector<int> GetCode(int i);
	string Solvecode(vector<int> source);
};
void HTree::SelectSmall(int& least, int& less, int i)
{
	least = less = 0;
	int m1 = hufftree[0].weight;
	int m2 = hufftree[0].weight;
	int tmp = 0;
	for (int j = 0; j < i; j++)
		if (m1 > hufftree[j].weight)
			m1 = hufftree[j].weight, least = j;
	for (int j = 0; j < i; j++)
		if (m2 > hufftree[j].weight && m2 != m1)
			m2 = hufftree[j].weight, less = j;
}
void HTree::SelectSmall(int& least, int& less, int i, vector<bool>& select)
{
	int temp, j, k, m;
	for (j = 0; j < i; j++)							//挑出第一个没被选择过的节点
		if (select[j] == 0)
		{
			least = j;
			select[j] = 1;
			break;
		}
	for (k = j + 1; k < i; k++)							//挑出第二个没被选择过的节点
		if (select[k] == 0)
		{
			less = k;
			select[k] = 1;
			break;
		}
	if (hufftree[j].weight > hufftree[k].weight)	//确定两个节点的大小关系
	{
		temp = least;
		least = less;
		less = temp;
	}
	for (m = k + 1; k < i; k++)
	{
		if (hufftree[k].weight < hufftree[least].weight && !select[k])
		{
			select[less] = 0;
			less = least;
			least = k;
			select[least] = 1;
		}
		if (hufftree[k].weight > hufftree[least].weight && (hufftree[k].weight < hufftree[less].weight) && !select[k])
		{
			select[less] = 0;
			less = k;
			select[k] = 1;
		}
	}
}
HTree::HTree(vector<HNode>& leaves)
{
	int i;
	int n = leaves.size();
	hufftree.resize(2 * n - 1);
	vector<bool> select(2*n-1, 0);
	if (n <= 1)
		exit(1);
	for (i = 0; i < n; i++)
	{
		hufftree[i].data = leaves[i].data;
		hufftree[i].weight = leaves[i].weight;
		hufftree[i].parent = hufftree[i].lchild = hufftree[i].rchild = -1;
	}
	for (i = n; i < 2 * n - 1; i++)
	{
		int least, less;
		SelectSmall(least, less, i, select);
		hufftree[least].parent = hufftree[less].parent = i;
		hufftree[i].parent = -1;
		hufftree[i].lchild = least;
		hufftree[i].rchild = less;
		hufftree[i].weight = hufftree[least].weight + hufftree[less].weight;
	}
}
vector<int> HTree::GetCode(int i)
{
	vector<int> code;
	int p = i;
	int temp = hufftree[i].parent;
	while (temp != -1)
	{
		if (hufftree[temp].lchild == p)
			code.insert(code.begin(), 0);
		else
			code.insert(code.begin(), 1);
		p = temp;
		temp = hufftree[temp].parent;
	}
	return code;
}
string HTree::Solvecode(vector<int> source)
{
	string target = "";
	int root = hufftree.size() - 1;
	int p = root;
	int len = source.size();
	for (int i = 0; i < len; i++)
	{
		if (source[i] == 0)
			p = hufftree[p].lchild;
		else if (source[i] == 1)
			p = hufftree[p].rchild;
		if (hufftree[p].lchild == -1 && hufftree[p].rchild == -1)
		{
			target = target + hufftree[p].data;
			p = root;
		}
	}
	return target;
}