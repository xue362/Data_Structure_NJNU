#pragma once
#include<vector>
#include<iostream>
#include<queue>
#include<stack>
using namespace std;

template <class T>
struct BiNode
{
	T data;
	BiNode<T>* lchild;
	BiNode<T>* rchild;
};

template <class T>
class BiTree
{
	BiNode<T>* root;
	BiNode<T>* CreateByPre(vector<T>& pre, int& i);
	void TraverseByPre(BiNode<T>* p);
	void TraverseByMid(BiNode<T>* p);
	void TraverseByLst(BiNode<T>* p);
	int CountLeaf(BiNode<T>* p);
	int CountOneBranch(BiNode<T>* p);
	int CountTwoBranch(BiNode<T>* p);
	BiNode<T>* CreateByPreMid(vector<T>& pre, vector<T>& mid, int ipre, int imid, int n);
	int Height(BiNode<T>* p);
	void RootLeafPath(BiNode<T>* p, vector<T>& path);
	BiNode<T>* Search(BiNode<T>* p, T e);
	void SwitchChild(BiNode<T>* p);
	void Free(BiNode<T>* p);
public:
	BiTree();
	~BiTree();
	void CreateByPre(vector<T>& pre);
	void CreateByPreMid(vector<T>& pre, vector<T>& mid);
	void TraverseByPre();
	void TraverseByMid();
	void TraverseByLst();
	void TraverseByLev();
	int CountLeaf();
	int CountOneBranch();
	int CountTwoBranch();
	int Height();
	void RootLeafPath_TraverseByPre();
	BiNode<T>* Search(T e);
};

template<class T>
BiNode<T>* BiTree<T>::CreateByPre(vector<T>& pre, int& i)
{
	T e = pre[i++];
	if (!(e >= 'a' && e <= 'z' || e >= 'A' && e <= 'Z'|| e >= '0' && e <= '9'))
		return nullptr;
	BiNode<T>* p = new BiNode<T>;
	p->data = e;
	p->lchild = CreateByPre(pre, i);
	p->rchild = CreateByPre(pre, i);
	return p;
}
template<class T>
BiNode<T>* BiTree<T>::CreateByPreMid(vector<T>& pre, vector<T>& mid, int ipre, int imid, int n)
{
	if (n == 0)
		return nullptr;
	BiNode<T>* p = new BiNode<T>;
	p->data = pre[ipre];
	int i;
	for (i = 0; i < n; i++)
		if (pre[ipre] == mid[imid + i])
			break;
	p->lchild = CreateByPreMid(pre, mid, ipre + 1, imid, i);
	p->rchild = CreateByPreMid(pre, mid, ipre + i + 1, imid + i + 1, n - i - 1);
	return p;
}
template<class T>
void BiTree<T>::TraverseByPre(BiNode<T>* p)
{
	if (p == nullptr)
		return;
	cout << p->data << " ";
	TraverseByPre(p->lchild);
	TraverseByPre(p->rchild);
}
template<class T>
void BiTree<T>::TraverseByMid(BiNode<T>* p)
{
	if (p == nullptr)
		return;
	TraverseByPre(p->lchild);
	cout << p->data << " ";
	TraverseByPre(p->rchild);
}
template<class T>
void BiTree<T>::TraverseByLst(BiNode<T>* p)
{
	if (p == nullptr)
		return;
	TraverseByPre(p->lchild);
	TraverseByPre(p->rchild);
	cout << p->data << " ";
}
template<class T>
void BiTree<T>::TraverseByPre()
{
	TraverseByPre(root);
}
template<class T>
void BiTree<T>::TraverseByMid()
{
	TraverseByPre(root);
}
template<class T>
void BiTree<T>::TraverseByLst()
{
	TraverseByPre(root);
}
template<class T>
void BiTree<T>::TraverseByLev()
{
	if (root == nullptr)return;
	queue<BiNode<T>*> Q;
	Q.push(root);
	while (!Q.empty())
	{
		BiNode<T>* p = Q.front();
		Q.pop();
		cout << p->data << " ";
		if (p->lchild)
			Q.push(p->lchild);
		if (p->rchild)
			Q.push(p->rchild);
	}
}
template<class T>
int BiTree<T>::CountLeaf(BiNode<T>* p)
{
	if (p == nullptr)
		return 0;
	int left = CountTwoBranch(p->lchild);
	int right = CountTwoBranch(p->rchild);
	if (!p->lchild && !p->rchild)
		return 1 + left + right;
	else return 0 + left + right;
}
template<class T>
int BiTree<T>::CountOneBranch(BiNode<T>* p)
{
	if (p == nullptr)
		return 0;
	int left = CountTwoBranch(p->lchild);
	int right = CountTwoBranch(p->rchild);
	if ((p->lchild || p->rchild) && !(p->lchild && p->rchild))
		return 1 + left + right;
	else return 0 + left + right;
}
template<class T>
int BiTree<T>::CountTwoBranch(BiNode<T>* p)
{
	if (p == nullptr)
		return 0;
	int left = CountTwoBranch(p->lchild);
	int right = CountTwoBranch(p->rchild);
	if (p->lchild && p->rchild)
		return 1 + left + right;
	else return 0 + left + right;
}
template<class T>
int BiTree<T>::CountLeaf()
{
	return CountLeaf(root);
}
template<class T>
int BiTree<T>::CountOneBranch()
{
	return CountOneBranch(root);
}
template<class T>
int BiTree<T>::CountTwoBranch()
{
	return CountTwoBranch(root);
}
template<class T>
int BiTree<T>::Height(BiNode<T>* p)
{
	if (p == nullptr)
		return 0;
	int left = Height(p->lchild);
	int right = Height(p->rchild);
	if (left > right)
		return left + 1;
	else return right + 1;
}
template<class T>
int BiTree<T>::Height()
{
	return Height(root);
}
template<class T>
BiTree<T>::BiTree()
{
	root = nullptr;
}
template<class T>
inline BiTree<T>::~BiTree()
{
	Free(root);
}
template<class T>
inline void BiTree<T>::Free(BiNode<T>* p)
{
	if (p == nullptr)
		return;
	Free(p->lchild);
	Free(p->rchild);
	delete p;
}
template<class T>
void BiTree<T>::CreateByPre(vector<T>& pre)
{
	int i = 0;
	root = CreateByPre(pre, i);
}
template<class T>
void BiTree<T>::CreateByPreMid(vector<T>& pre, vector<T>& mid)
{
	int n = pre.size();
	root = CreateByPreMid(pre, mid, 0, 0, n);
}
template<class T>
BiNode<T>* BiTree<T>::Search(BiNode<T>* p, T e)
{
	if (p == nullptr)
		return nullptr;
	if (p->data == e)
		return p;
	BiNode<T>* q = Search(p->lchild, e);
	if (q)return q;
	return Search(p->rchild, e);
}
template<class T>
BiNode<T>* BiTree<T>::Search(T e)
{
	return Search(root, e);
}
template<class T>
void BiTree<T>::RootLeafPath(BiNode<T>* p, vector<T>& path)
{
	if (p == nullptr)
		return;
	path.push_back(p->data);
	if (!p->lchild && !p->rchild)
	{
		int len = path.size();
		for (int i = 0; i < len; i++)
			cout << path[i] << " ";
		cout << endl;
	}
	else
	{
		RootLeafPath(p->lchild, path);
		RootLeafPath(p->rchild, path);
	}
	path.pop_back();//注意此时递归弹出
}
template<class T>
void BiTree<T>::RootLeafPath_TraverseByPre()
{
	vector<T> path;
	RootLeafPath(root, path);
}
template<class T>
void BiTree<T>::SwitchChild(BiNode<T>* p)
{
	if (p == nullptr)
		return;
	SwitchChild(p->lchild);
	SwitchChild(p->rchild);
	swap(p->lchild, p->rchild);
}