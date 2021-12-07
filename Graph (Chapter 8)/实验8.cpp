

// 实验8.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<iostream>
#include<vector>
#include"MGraph.h"
#include"ALGraph.h"
/*
测试数据

5
0 1 2 3 4
7
0 1 1
0 2 1
1 3 1
2 4 1
3 2 1 
3 4 1 
4 1 1 

6
0 1 2 3 4 5
10
0 1 2
0 2 5
0 3 4
1 2 4
1 4 5 
2 3 6 
2 4 3 
2 5 4
3 5 7
4 5 1

5
0 1 2 3 4
7
0 1 10
0 3 30
0 4 100
1 2 50
2 4 10
3 2 20
3 4 60

*/
using namespace std;
int main()
{
	vector<char> v;
	vector<EdgeType<char>> e;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		char c;
		cin >> c;
		v.push_back(c);
	}
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		EdgeType<char> et;
		cin >> et.head >> et.tail >> et.cost;
		e.push_back(et);
	}
	cout << "矩阵" << endl;
	MGraph<char> G1;
	G1.CreateGraph(DN, v, e);
	cout << "DFS" << endl;
	G1.DFS();
	cout << endl;
	cout << "BFS" << endl;
	G1.BFS();
	cout << endl;
	cout << "PRIM" << endl;
	G1.Prim(0);
	cout << endl;
	cout << "KRUSKAL" << endl;
	G1.Kruskal();
	cout << endl;
	cout << "DIJKSTRA" << endl;
	G1.Dijkstra(0);
	cout << endl;
	cout << "FLOYD" << endl;
	G1.Floyd(0, 4);
	cout << endl;
	G1.FindLoop(0);
	cout << "表" << endl;
	ALGraph<char> G2;
	G2.CreateGraph(DN, v, e);
	cout << "DFS" << endl;
	G2.DFS();
	cout << endl;
	cout << "BFS" << endl;
	G2.BFS();
	cout << endl;
	if (G2.ifExistPath_BFS('0', '1'))
		cout << "0to1 YES" << endl;
	else cout << "0to1 NO" << endl;
	if (G2.ifExistPath_BFS('2', '0'))
		cout << "2to0 YES" << endl;
	else cout << "2to0 NO" << endl;
	G2.Prim(0);
	G2.MinSpanForest_Prim();
	if (G2.ExistPath_Lenth(0,4,7))
		cout << "YES" << endl;
	else cout << "NO" << endl;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
