#pragma once
#include<vector>
#include<iostream>
using namespace std;

//template<class T>
struct Couple
{
	char parent, child;
};
template<class T>
struct CSNode
{
	T data;
	CSNode<T>* firstchild, * nextsibling;
	int degree;
};
template<class T>
class CSTree
{
	CSNode<T>* root;
	void Insert(Couple &p);
	CSNode<T>* Search(CSNode<T>* p, T e);
	void Free(CSNode<T>* p);
	void TraverseByPre(CSNode<T>* p);
	void TraverseByLst(CSNode<T>* p);
	void Degree(CSNode<T>* p);
	int Height(CSNode<T>* p);
	void RootLeafPath(CSNode<T>* p, vector<T>& path);
public:
	CSTree(vector<Couple>& ps);
	~CSTree();
	void TraverseByPre();
	void TraverseByLst();
	void Degree();
	int Height();
	void RootLeafPath();
};

template<class T>
inline void CSTree<T>::Insert(Couple &p)
{
	CSNode<T>* child = new CSNode<T>;
	child->data = p.child;
	child->firstchild = child->nextsibling = nullptr;
	CSNode <T>* parent = Search(root, p.parent);
	if (parent->firstchild == nullptr)
		parent->firstchild = child;
	else
	{
		for (parent = parent->firstchild; parent->nextsibling; parent = parent->nextsibling);
		parent->nextsibling = child;
	}
}

template<class T>
inline CSNode<T>* CSTree<T>::Search(CSNode<T>* p, T e)
{
	if (p == nullptr)
		return nullptr;
	if (p->data == e)
		return p;
	CSNode<T>* q = Search(p->firstchild, e);
	if (q)return q;
	return Search(p->nextsibling, e);
}

template<class T>
void inline CSTree<T>::Free(CSNode<T>* p)
{
	if (p == nullptr)
		return;
	Free(p->firstchild);
	Free(p->nextsibling);
	delete p;
}

template<class T>
inline void CSTree<T>::TraverseByPre(CSNode<T>* p)
{
	if (p == nullptr)
		return;
	cout << p->data << " ";
	TraverseByPre(p->firstchild);
	TraverseByPre(p->nextsibling);
}

template<class T>
inline void CSTree<T>::TraverseByLst(CSNode<T>* p)
{
	if (p == nullptr)
		return;
	TraverseByPre(p->firstchild);
	cout << p->data << " ";
	TraverseByPre(p->nextsibling);
}

template<class T>
inline void CSTree<T>::Degree(CSNode<T>* p)
{
	if (p == nullptr)
		return;
	p->degree = 0;
	CSNode<T>* child = p->firstchild;
	for (; child; child = child->nextsibling)
		p->degree++;
	Degree(p->firstchild);
	Degree(p->nextsibling);
}

template<class T>
inline int CSTree<T>::Height(CSNode<T>* p)
{
	if (p == nullptr)
		return 0;
	int max = 0;
	for (p = p->firstchild; p; p = p->nextsibling)
	{
		int height = Height(p);
		if (height > max)
			max = height;
	}
	return ++max;
}

template<class T>
inline void CSTree<T>::RootLeafPath(CSNode<T>* p, vector<T>& path)
{
	while (p)
	{
		path.push_back(p->data);
		if (p->firstchild)
			RootLeafPath(p->firstchild, path);
		else
		{
			for (vector<char>::iterator iter = path.begin(); iter != path.end(); iter++)
				cout << *iter << " ";
			cout << endl;
		}
		path.pop_back();
		p = p->nextsibling;
	}
}

template<class T>
CSTree<T>::CSTree(vector<Couple>& ps)
{
	if (ps.empty())
	{
		root = nullptr;
		return;
	}
	root = new CSNode<T>;
	root->data = ps[0].parent;
	root->firstchild = root->nextsibling = nullptr;
	int len = ps.size();
	for (int i = 0; i < len; i++)
		Insert(ps[i]);
}

template<class T>
inline CSTree<T>::~CSTree()
{
	Free(root);
}

template<class T>
inline void CSTree<T>::TraverseByPre()
{
	TraverseByPre(root);
}

template<class T>
inline void CSTree<T>::TraverseByLst()
{
	TraverseByLst(root);
}

template<class T>
inline void CSTree<T>::Degree()
{
	Degree(root);
}

template<class T>
inline int CSTree<T>::Height()
{
	return Height(root);
}

template<class T>
inline void CSTree<T>::RootLeafPath()
{
	vector<T> path;
	RootLeafPath(root, path);
}
