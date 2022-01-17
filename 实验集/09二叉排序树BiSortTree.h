#pragma once
struct BiNode
{
	int key;
	BiNode* lchild;
	BiNode* rchild;
};
class BiSortTree
{
	BiNode* root = nullptr;
	void Insert(BiNode*& ptr, int k);
	void Delete(BiNode*& ptr, int k);
	BiNode* Search(BiNode* ptr, int k);
	void Free(BiNode* p);
public:
	BiSortTree(int a[], int n);
	~BiSortTree();
	void Insert(int k);
	void Delete(int k);
	bool Search(int k);
};

inline BiSortTree::BiSortTree(int a[], int n)
{
	for (int i = 0; i < n; i++)
		Insert(root, a[i]);
}
void BiSortTree::Insert(BiNode*& ptr, int k)
{
	if (ptr == nullptr)
	{
		ptr = new BiNode;
		ptr->key = k;
		ptr->lchild = ptr->rchild = nullptr;
	}
	else
	{
		if (k < ptr->key)
			Insert(ptr->lchild, k);
		if (k > ptr->key)
			Insert(ptr->rchild, k);
	}
}
void BiSortTree::Insert(int k)
{
	Insert(root, k);
}
inline BiNode* BiSortTree::Search(BiNode* ptr, int k)
{
	if (ptr == nullptr)
		return nullptr;
	if (ptr->key == k)
		return ptr;
	if (ptr->key > k)
		return Search(ptr->lchild, k);
	if (ptr->key < k)
		return Search(ptr->rchild, k);
}
inline bool BiSortTree::Search(int k)
{
	if (Search(root, k))
		return true;
	return false;
}
inline void BiSortTree::Delete(BiNode*& ptr, int k)
{
	if (ptr == nullptr)
		return;
	if (ptr->key > k)
		Delete(ptr->lchild, k);
	if (ptr->key < k)
		Delete(ptr->rchild, k);
	if (ptr->key == k)
	{
		BiNode* tmp = ptr;
		if (ptr->lchild && ptr->rchild)
		{
			tmp = ptr->lchild;
			while (tmp->rchild)
				tmp = tmp->rchild;
			ptr->key = tmp->key;
			Delete(ptr->lchild, tmp->key);
		}
		else
		{
			if (ptr->lchild)
				ptr = ptr->rchild;
			if (ptr->rchild)
				ptr = ptr->lchild;
			delete tmp;
		}
	}
}
inline void BiSortTree::Delete(int k)
{
	Delete(root, k);
}
inline BiSortTree::~BiSortTree()
{
	Free(root);
}
inline void BiSortTree::Free(BiNode* p)
{
	if (p == nullptr)
		return;
	Free(p->lchild);
	Free(p->rchild);
	delete p;
}