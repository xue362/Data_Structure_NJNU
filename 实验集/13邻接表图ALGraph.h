#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include"MGraph.h"
using namespace std;

struct EdgeNode
{
	int adjvex;
	EdgeNode* nextedge;
	int cost;
};
template<class T>
struct VexNode
{
	T data;
	EdgeNode* firstedge;
};
template<class T>
struct Couple
{
	T parent;
	T child;
};
template<class T>
class ALGraph
{
	int vexnum, edgenum;
	vector<VexNode<T>> adjlist;
	Gtype type;
	void DFS(int v, vector<bool>& visited);
	void SortForAdjlist();
	void SortForEdgeLink(EdgeNode* head);
	int GetSubscriptOfVex(T c);
	int GetWeight(int head, int tail);
	void Prim(int v, vector<bool>& visited, vector<Couple<T>>& mintree);//作业第三题
	bool ExistPath_DFS_Lenth(int i, int j, int k, int& n, vector<bool>& visited);//作业第四题
public:
	ALGraph();
	void CreateGraph(Gtype t, vector<T>& v, vector<EdgeType<T>>& e);
	~ALGraph();
	void DFS();//作业第一题
	void BFS();
	bool ifExistPath_BFS(T a, T b);//作业第二题
	void Prim(int v);
	void MinSpanForest_Prim();//作业第三题
	bool ExistPath_Lenth(int i, int j, int k);//作业第四题
	void TopoSort();
};
template<class T>
inline ALGraph<T>::ALGraph()
{
	vexnum = edgenum = 0;
	type = UNDG;
}
template<class T>
inline ALGraph<T>::~ALGraph()
{
}
template<class T>
inline int ALGraph<T>::GetSubscriptOfVex(T c)
{
	for (int i = 0; i < vexnum; i++)
		if (c == adjlist[i].data)
			return i;
	return 0;
}
struct Copy
{
	int adjvex;
	int cost;
};
bool operator<(const Copy& cmp1, const Copy& cmp2)
{
	return cmp1.adjvex < cmp2.adjvex;//重载利用sort升序排列
}
template<class T>
inline void ALGraph<T>::SortForEdgeLink(EdgeNode* head)
{
	if (!head)return;
	EdgeNode* L = head;
	vector<Copy> copy;
	while (L)
	{
		Copy tmp;
		tmp.adjvex = L->adjvex;
		tmp.cost = L->cost;
		copy.push_back(tmp);
		L = L->nextedge;
	}
	sort(copy.begin(), copy.end());
	L = head;
	for (int i = 0; L; i++)
	{
		L->adjvex = copy[i].adjvex;
		L->cost = copy[i].cost;
//		cout << L->adjvex << " " << " ";
		L = L->nextedge;
	}
//	cout << endl;
}
template<class T>
inline void ALGraph<T>::SortForAdjlist()
{
	for (int i = 0; i < vexnum; i++)
		SortForEdgeLink(adjlist[i].firstedge);
}
template<class T>
inline void ALGraph<T>::CreateGraph(Gtype t, vector<T>& v, vector<EdgeType<T>>& e)
{
	vexnum = v.size();
	edgenum = e.size();
	int& vn = vexnum, & en = edgenum;
	type = t;
	adjlist.resize(vn);
	for (int i = 0; i < vn; i++)
	{
		adjlist[i].data = v[i];
		adjlist[i].firstedge = NULL;
	}
	for (int i = 0; i < en; i++)
	{
		EdgeNode* p = new EdgeNode;
		int va = GetSubscriptOfVex(e[i].head), vb = GetSubscriptOfVex(e[i].tail);
		int cost = e[i].cost;
		switch (type)
		{
		case UNDG:
			p->adjvex = vb;
			p->cost = 1;
			p->nextedge = adjlist[va].firstedge;
			adjlist[va].firstedge = p;
			p = new EdgeNode;
			p->adjvex = va;
			p->cost = 1;
			p->nextedge = adjlist[vb].firstedge;
			adjlist[vb].firstedge = p;
			break;
		case DG:
			p->adjvex = vb;
			p->cost = 1;
			p->nextedge = adjlist[va].firstedge;
			adjlist[va].firstedge = p;
			break;
		case UNDN:
			p->adjvex = vb;
			p->cost = cost;
			p->nextedge = adjlist[va].firstedge;
			adjlist[va].firstedge = p;
			p = new EdgeNode;
			p->adjvex = va;
			p->cost = cost;
			p->nextedge = adjlist[vb].firstedge;
			adjlist[vb].firstedge = p;
			break;
		case DN:
			p->adjvex = vb;
			p->cost = cost;
			p->nextedge = adjlist[va].firstedge;
			adjlist[va].firstedge = p;
			break;
		}
	}
	SortForAdjlist();//注意 此函数使各子链表按递增排序
}
template<class T>
inline void ALGraph<T>::DFS(int v, vector<bool>& visited)
{
	cout << adjlist[v].data << " ";
	visited[v] = true;
	for (EdgeNode* p = adjlist[v].firstedge; p; p = p->nextedge)
		if (!visited[p->adjvex])
			DFS(p->adjvex, visited);
}
template<class T>
inline void ALGraph<T>::DFS()
{
	vector<bool> visited(vexnum, false);
	for (int i = 0; i < vexnum; i++)
		if (!visited[i])
			DFS(i, visited);
}
template<class T>
inline void ALGraph<T>::BFS()
{
	queue<int> q;
	vector<bool> visited(vexnum, false);
	for (int i = 0; i < vexnum; i++)
	{
		if (!visited[i])
		{
			q.push(i);
			visited[i] = true;
			cout << adjlist[i].data << " ";
			while (q.size())
			{
				int u = q.front();
				q.pop();
				for (EdgeNode* p=adjlist[u].firstedge; p; p = p->nextedge)
				{
					if (!visited[p->adjvex])
					{
						q.push(p->adjvex);
						visited[p->adjvex] = true;
						cout << adjlist[p->adjvex].data << " ";
					}
				}
			}
		}
	}
}
template<class T>
inline bool ALGraph<T>::ifExistPath_BFS(T a, T b)
{
	int i = GetSubscriptOfVex(a), j = GetSubscriptOfVex(b);
	int e, k;
	vector<bool> visited(vexnum, false);
	queue<int> q;
	q.push(i);
	while (!q.empty())
	{
		e = q.front();
			q.pop();
		visited[e] = true;
		for (EdgeNode* p = adjlist[e].firstedge; p; p = p->nextedge)
		{
			k = p->adjvex;//当前指向顶点的位置
			if (k == j)
				return true;
			else if (!visited[k])
				q.push(k);
		}
	}
	return false;
}
template<class T>
inline int ALGraph<T>::GetWeight(int head, int tail)
{
	if (head == tail)return 0;
	EdgeNode* p = adjlist[head].firstedge;
	while (p)
	{
		if (tail == p->adjvex)
			return p->cost;
		p = p->nextedge;
	}
	return INF;
}
template<class T>
inline void ALGraph<T>::Prim(int v)
{
	vector<Edge<T>> miniedges(vexnum);//建立该点邻接点的数组，记录到达所需权值
	for (int i = 0; i < vexnum; i++)
	{
		miniedges[i].adjvex = adjlist[v].data;
		miniedges[i].lowcost = GetWeight(v, i);
	}
	miniedges[v].lowcost = 0;
	for (int i = 1; i < vexnum; i++)
	{
		int k = 0;
		int min = INF;
		for (int j = 0; j < vexnum; j++)
			if (miniedges[j].lowcost < min && miniedges[j].lowcost != 0)//注意!=0
			{
				min = miniedges[j].lowcost;
				k = j;
			}
		cout << miniedges[k].adjvex << "," << adjlist[k].data << endl;
		miniedges[k].lowcost = 0;//此处排除已进入的点
		for (int j = 0; j < vexnum; j++)
		{
			int costkj = GetWeight(k, j);
			if (costkj < miniedges[j].lowcost && miniedges[j].lowcost != 0 && costkj != 0)//注意!=0
			{
				miniedges[j].adjvex = adjlist[k].data;
				miniedges[j].lowcost = costkj;
			}
		}
	}
}
template<class T>
inline void ALGraph<T>::Prim(int v, vector<bool>& visited, vector<Couple<T>>& mintree)
{
	vector<Edge<T>> miniedges(vexnum);//建立该点邻接点的数组，记录到达所需权值
	for (int i = 0; i < vexnum; i++)
	{
		miniedges[i].adjvex = adjlist[v].data;
		miniedges[i].lowcost = GetWeight(v, i);
	}
	miniedges[v].lowcost = 0;
	for (int i = 1; i < vexnum; i++)
	{
		int k = 0;
		int min = INF;
		for (int j = 0; j < vexnum; j++)
			if (miniedges[j].lowcost < min && miniedges[j].lowcost != 0)//注意!=0
			{
				min = miniedges[j].lowcost;
				k = j;
			}
		Couple<T> tmp;
		tmp.parent = miniedges[k].adjvex;
		tmp.child = adjlist[k].data;
		visited[GetSubscriptOfVex(tmp.parent)] = true;
		visited[GetSubscriptOfVex(tmp.child)] = true;
		mintree.push_back(tmp);
		miniedges[k].lowcost = 0;//此处排除已进入的点
		for (int j = 0; j < vexnum; j++)
		{
			int costkj = GetWeight(k, j);
			if (costkj < miniedges[j].lowcost && miniedges[j].lowcost != 0 && costkj != 0)//注意!=0
			{
				miniedges[j].adjvex = adjlist[k].data;
				miniedges[j].lowcost = costkj;
			}
		}
	}
}
template<class T>
inline void ALGraph<T>::MinSpanForest_Prim()
{
	vector<bool> visited(vexnum, false);
	vector<vector<Couple<T>>> mintrees(vexnum);
	vector<Couple<T>> minforest;
	for (int i = 0; i < vexnum; i++)
		if (!visited[i])
			Prim(i, visited, mintrees[i]);
	for(int i=0;i<vexnum;i++)
		if (!mintrees[i].empty())
		{
			Couple<T> tmp;
			tmp.parent = 'R';
			tmp.child = adjlist[i].data;
			minforest.push_back(tmp);
			int len = mintrees[i].size();
			for (int j = 0; j < len; j++)
				minforest.push_back(mintrees[i][j]);
		}
	for (int i = 0; i < minforest.size(); i++)
		cout << minforest[i].parent << "," << minforest[i].child << endl;
	//此处应使用森林生成算法（二元组），待补
}
template<class T>
inline bool ALGraph<T>::ExistPath_DFS_Lenth(int i, int j, int k, int &n, vector<bool> &visited)
{
	EdgeNode* p;
	visited[i] = true;
	if (i == j && n == k)
		return true;
	n++;
	p = adjlist[i].firstedge;
	while (p)
	{
		if (!visited[p->adjvex])
			if (ExistPath_DFS_Lenth(p->adjvex, j, k, n, visited))
				return true;
		p = p->nextedge;
	}
	visited[i] = false;
	n--;
	return false;
}
template<class T>
inline bool ALGraph<T>::ExistPath_Lenth(int i, int j, int k)
{
	vector<bool> visited(vexnum, false);
	int n = 0;
	return ExistPath_DFS_Lenth(i, j, k, n, visited);
}
template<class T>
inline void ALGraph<T>::TopoSort()
{
	vector<int> indegree(vexnum, 0);
	queue<int> q;
	EdgeNode* p;
	for (int i = 0; i < vexnum; i++)
	{
		p = adjlist[i].firstedge;
		while (p)
		{
			indegree[p->adjvex]++;
			p = p->nextedge;
		}
	}
	for (int i = 0; i < vexnum; i++)
		if (indegree[i] == 0)
			q.push(i);
	int cnt = 0;
	while (!q.empty())
	{
		int out = q.front();
		q.pop();
		cout << adjlist[out].data << " ";
		cnt++;
		p = adjlist[out].firstedge;
		while (p)
		{
			indegree[p->adjvex]--;
			if (indegree[p->adjvex] == 0)
				q.push(p->adjvex);
			p = p->nextedge;
		}
	}
	if (cnt < vexnum)
		cout << "Loop Exists!" << endl;
}