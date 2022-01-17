#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<queue>
const int INF = INT_MAX / 2;
using namespace std;

enum Gtype {
	UNDG,
	DG,
	UNDN,
	DN
};
template<class T>
struct EdgeType
{
	T head, tail;
	int cost;
};
template<class T>
bool operator<(const EdgeType<T>& cmp1, const EdgeType<T>& cmp2)
{
	return cmp1.cost < cmp2.cost;//重载利用sort升序排列
}
template<class T>
struct Edge
{
	T adjvex;
	int lowcost;
};
template<class T>
class MGraph
{
	int vexnum, edgenum;
	Gtype type;
	vector<vector<int>> edges;
	vector<T> vexs;
	void DFS(int v, vector<bool>& visited);
	int GetSubscriptOfVex(T c);
	void Kruskal(vector<EdgeType<T>>& tree);
	void Dijkstra(int v, vector<int>& path, vector<int>& dist);
	void Floyd(vector<vector<int>>& path, vector<vector<int>>& D);
	void FindLoop_DFS(int vi, int v, vector<bool>& visited, vector<int>& path);//作业: 找出图中的一个回路
public:
	MGraph();
	void CreateGraph(Gtype t, vector<T>& v, vector<EdgeType<T>>& e);
	~MGraph();
	void DFS();
	void BFS();
	void Prim(int v);
	void Kruskal();
	void Dijkstra(int v);
	void Floyd(int i, int j);
	void FindLoop(int vi);
};
template<class T>
inline MGraph<T>::MGraph()
{
	vexnum = edgenum = 0;
	type = UNDG;
}
template<class T>
inline MGraph<T>::~MGraph()
{
}
template<class T>
inline int MGraph<T>::GetSubscriptOfVex(T c)
{
	for (int i = 0; i < vexnum; i++)
		if (c == vexs[i])
			return i;
	return 0;
}
template<class T>
inline void MGraph<T>::CreateGraph(Gtype t, vector<T>& v, vector<EdgeType<T>>& e)
{
	vexnum = v.size();
	edgenum = e.size();
	int& vn = vexnum, & en = edgenum;
	type = t;
	vexs.resize(vn);
	edges.resize(vn);
	for (int i = 0; i < vn; i++)
		vexs[i] = v[i];
	for (int i = 0; i < vn; i++)
		edges[i].resize(vn);
	for (int i = 0; i < vn; i++)
		for (int j = 0; j < vn; j++)
			if (i == j)
				edges[i][j] = 0;
			else edges[i][j] = INF;//int型不能使用INFINITY宏，用INF较为合适，下同
	for (int i = 0; i < en; i++)
	{
		switch (type)
		{
		case UNDG:
			edges[GetSubscriptOfVex(e[i].head)][GetSubscriptOfVex(e[i].tail)] = edges[GetSubscriptOfVex(e[i].tail)][GetSubscriptOfVex(e[i].head)] = 1;
			break;
		case DG:
			edges[GetSubscriptOfVex(e[i].head)][GetSubscriptOfVex(e[i].tail)] = 1;
			break;
		case UNDN:
			edges[GetSubscriptOfVex(e[i].head)][GetSubscriptOfVex(e[i].tail)] = edges[GetSubscriptOfVex(e[i].tail)][GetSubscriptOfVex(e[i].head)] = e[i].cost;
			break;
		case DN:
			edges[GetSubscriptOfVex(e[i].head)][GetSubscriptOfVex(e[i].tail)] = e[i].cost;
			break;
		}
	}
}
template<class T>
inline void MGraph<T>::DFS(int v, vector<bool>& visited)
{
	visited[v] = true;
	cout << vexs[v] << " ";
	for (int i = 0; i < vexnum; i++)
		if (!visited[i] && edges[v][i] == 1)
			DFS(i, visited);
}
template<class T>
inline void MGraph<T>::DFS()
{
	vector<bool> visited(vexnum, false);
	for (int i = 0; i < vexnum; i++)
		if (!visited[i])
			DFS(i, visited);
}
template<class T>
inline void MGraph<T>::BFS()
{
	queue<int> q;
	vector<bool> visited(vexnum, false);
	for (int i = 0; i < vexnum; i++)
	{
		if (!visited[i])
		{
			q.push(i);
			visited[i] = true;
			cout << vexs[i] << " ";
			while(q.size())
			{
				int u = q.front();
				q.pop();
				for (int j = 0; j < vexnum; j++)
				{
					if (edges[u][j] == 1 && !visited[j])
					{
						visited[j] = true;
						cout << vexs[j] << " ";
						q.push(j);
					}
				}
			}
		}
	}
}
template<class T>
inline void MGraph<T>::Prim(int v)
{
	vector<Edge<T>> miniedges(vexnum);//建立该点邻接点的数组，记录到达所需权值
	for (int i = 0; i < vexnum; i++)
	{
		miniedges[i].adjvex = vexs[v];
		miniedges[i].lowcost = edges[v][i];
	}
	miniedges[v].lowcost = 0;//理论上可略去，因edges[v][v]==0
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
		cout << miniedges[k].adjvex << "," << vexs[k] << endl;
		miniedges[k].lowcost = 0;//此处排除已进入的点
		for (int j = 0; j < vexnum; j++)
			if (edges[k][j] < miniedges[j].lowcost && miniedges[j].lowcost != 0 && edges[k][j] != 0)//注意!=0
			{
				miniedges[j].adjvex = vexs[k];
				miniedges[j].lowcost = edges[k][j];
			}
	}
}
template<class T>
inline void MGraph<T>::Kruskal(vector<EdgeType<T>>& tree)
{
	vector<EdgeType<T>> graph;//需要注意，书中的头尾为int型，此处为template
	for(int i=0;i<vexnum;i++)//将边排入graph
		for(int j=0;j<vexnum;j++)
			if (edges[i][j] != 0 && edges[i][j] != INF)
			{
				EdgeType<T> tmp;
				tmp.head = vexs[i];
				tmp.tail = vexs[j];
				tmp.cost = edges[i][j];
				graph.push_back(tmp);
			}
	sort(graph.begin(), graph.end());//排序
	tree.resize(vexnum - 1);//开始建立树
	vector<int> components(edgenum);
	for (int i = 0; i < vexnum; i++)
		components[i] = i;//用于判断环
	int k = 0, j = 0;
	while (k < vexnum - 1)
	{
		int h1 = GetSubscriptOfVex(graph[j].head);
		int t1 = GetSubscriptOfVex(graph[j].tail);
		int h2 = components[h1];
		int t2 = components[t1];
		if (h2 != t2)
		{
			tree[k].head = vexs[h1];
			tree[k].tail = vexs[t1];
			tree[k].cost = graph[j].cost;
			k++;
			for (int i = 0; i < vexnum; i++)
				if (components[i] == t2)
					components[i] = h2;
		}
		j++;
	}
}
template<class T>
inline void MGraph<T>::Kruskal()
{
	vector<EdgeType<T>> tree;
	Kruskal(tree);
	for (int i = 0; i < tree.size(); i++)
		cout << vexs[GetSubscriptOfVex(tree[i].head)] << "," << vexs[GetSubscriptOfVex(tree[i].tail)] << endl;
}
template<class T>
inline void MGraph<T>::Dijkstra(int v, vector<int>& path, vector<int>& dist)
{
	vector<bool> visited(vexnum, false);
	for (int i = 0; i < vexnum; i++)
	{
		dist[i] = edges[v][i];
		if ((i == v || dist[i] < INF))
			path[i] = v;
		else path[i] = -1;
	}
	dist[v] = 0;
	visited[v] = true;//选中起始点
	for (int i = 1; i < vexnum; i++)
	{
		int k = 0;
		int min = INF;
		for (int j = 0; j < vexnum; j++)
			if (!visited[j] && dist[j] < min)
			{
				min = dist[j];
				k = j;
			}
		visited[k] = true;
		for (int j = 0; j < vexnum; j++)
			if (!visited[j])
				if (edges[k][j] != 0 && edges[k][j] != INF)
					if (edges[k][j] + dist[k] < dist[j])
					{
						dist[j] = dist[k] + edges[k][j];
						path[j] = k;
					}
	}
}
template<class T>
inline void MGraph<T>::Dijkstra(int v)
{
	vector<int> path(vexnum);
	vector<int> dist(vexnum);
	Dijkstra(v, path, dist);
/*	for (auto i = path.begin(); i != path.end(); i++)
		cout << *i << ' ';
	cout << endl;*/
	int n = path.size() - 1;
	vector<int> print;
	print.push_back(n);
	while (n != v && n > 0)
	{
		n = path[n];
		print.push_back(n);
	}
	for (int i = print.size() - 1; i > 0; i--)
		cout << print[i] << "->";
	cout << print[0];
}
template<class T>
inline void MGraph<T>::Floyd(int i, int j)
{
	vector<vector<int>> path(vexnum);
	vector<vector<int>> D(vexnum);
	for (int k = 0; k < vexnum; k++)
		path[k].resize(vexnum), D[k].resize(vexnum);
	Floyd(path, D);
	cout << i << "->";
	int k = path[i][j];
	while (k != -1 && k != j)
	{
		cout << k << "->";
		k = path[k][j];
	}
	cout << j;
}
template<class T>
inline void MGraph<T>::Floyd(vector<vector<int>>& path, vector<vector<int>>& D)
{
	for(int i=0;i<vexnum;i++)
		for (int j = 0; j < vexnum; j++)
		{
			if (i == j)
				D[i][j] = 0;
			else D[i][j] = edges[i][j];
			if (D[i][j] < INF)
				path[i][j] = j;
			else path[i][j] = -1;
		}
	for(int k=0;k<vexnum;k++)
		for(int i=0;i<vexnum;i++)
			for(int j=0;j<vexnum;j++)
				if (D[i][k] + D[k][j] < D[i][j])
				{
					D[i][j] = D[i][k] + D[k][j];
					path[i][j] = path[i][k];
				}
}
template<class T>
inline void MGraph<T>::FindLoop_DFS(int vi, int v, vector<bool>& visited, vector<int>& path)
{
	if (v != vi)
		visited[v] = true;
	path.push_back(v);
	for (int i = 0; i < vexnum; i++)
	{
		if (edges[v][i] ==1 && i == vi)
		{
			path.push_back(i);
			for (int i = 0; i < path.size(); i++)
				cout << path[i] << " ";
			cout << endl;
		}
		if (edges[v][i] ==1 && !visited[i])
			FindLoop_DFS(vi, i, visited, path);
	}
	path.pop_back();
}
template<class T>
inline void MGraph<T>::FindLoop(int vi)
{
	vector<int> path;
	bool exist = false;
	vector<bool> visited(vexnum, false);
	FindLoop_DFS(vi, vi, visited, path);
	if (path.empty())
		cout << vi << " 顶点无回路" << endl;
}