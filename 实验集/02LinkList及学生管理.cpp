#include<iostream>
#include<string>
using namespace std; 
class STU {
		string id;
		string name;
		string gender;
		string major;
		string birth;
	public:
		STU() {}
		friend istream& operator>>(istream& input, STU& t) {
			input >> t.id >> t.name >> t.gender >> t.major >> t.birth;
			return input;
		}
		friend ostream& operator<<(ostream& output, const STU& t) {
			output << "学号 " << t.id << "姓名 " << t.name << "性别 " << t.gender << "专业 " << t.major << "出生年月 " << t.birth << endl;
			return output;
		}
		void Change(STU &t) {
			id = t.id;
			name = t.name;
			gender = t.gender;
			major = t.major;
			birth = t.birth;
		}
		string getid() {
			return id;
		}
		bool operator <(const STU& t) {
			return (id < t.id);
		}
		bool operator >(const STU& t) {
			return (id > t.id);
		}
};
template <class T>
struct Node {
	T data;
	Node<T>* next;
};
template <class T>
class LinkList {
		Node<T>* head; //单链表的头指针
	public:
		LinkList(); //建立带头结点的空链表
		LinkList(T a[], int n); //建立有n个元素的单链表
		~LinkList(); //析构函数
		int ListLength(); //求单链表的长度
		T& Get(int pos); //按位查找
		Node<T>* Locate(T item); //按值查找
		int Locate(string s);
		void PrintLinkList(); //遍历单链表
		void Insert(int i, T item); //插入元素
		T Delete(int i); //删除结点
		void InvertList();
		void Sort();
		void MergeLinkList(LinkList<T>& La, LinkList<T>& Lb, LinkList<T>& Lc);
};
template <class T>
LinkList<T>::LinkList() {
	head = new Node<T>;
	head->next = NULL;
}
template <class T>
LinkList<T>::LinkList(T a[], int n) {
	head = new Node<T>; //生成头结点
	Node<T>* rear = head;
	for (int i = 0; i < n; i++) {
		Node<T>* s = new Node<T>;
		s->data = a[i];
		rear->next = s;
		rear = s;
	}
	rear->next = NULL;
}
template <class T>
int LinkList<T>::ListLength() {
	int num = 0;
	Node<T>* p = head->next;
	while (p) {
		p = p->next;
		num++;
	}
	return num;
}
template <class T>
T& LinkList<T>::Get(int pos) {
	Node<T>* p = head->next;
	int j = 1;
	while (p && j < pos) {
		p = p->next;
		j++;
	}
	if (!p || j > pos) {
		cerr << "查找位置非法";
		exit(1);
	} else return p->data;
}
template <class T>
Node<T>* LinkList<T>::Locate(T key) {
	Node<T>* p = head->next;
	while (p && p->data != key)
		p = p->next;
	return p;
}
template<class T>
void LinkList<T>::PrintLinkList() {
	Node<T>* p = head->next;
	while (p) {
		cout << p->data << " ";
		p = p->next;
	}
}
template <class T>
void LinkList<T>::Insert(int i, T item) {
	Node<T>* p = head;
	int j = 0;
	while (p && j < i - 1) { //找到第i-1个结点的位置
		p = p->next;
		j++;
	}
	if (!p) {
		cerr << "插入位置非法";
		exit(1);
	} else {
		Node<T>* s = new Node<T>; //生成元素值为item的新结点s
		s->data = item;
		s->next = p->next; //用后插法将s插入到结点p的后面
		p->next = s;
	}
}
template <class T>
T LinkList<T>::Delete(int i) {
	Node<T>* p = head;
	int j = 0;
	while (p && j < i - 1) { //查找第i-1个结点
		p = p->next;
		j++;
	}
	if (!p || !p->next) {
		cerr << "删除位置非法";
		exit(1);
	}
	Node<T>* q = p->next;
	T x = q->data;
	p->next = q->next;
	delete q;
	return x;
}
template<class T>
void LinkList<T>::InvertList() {
	Node<T>* q = head->next;
	head->next = NULL;
	while (q) {
		Node<T>* p = q;
		q = q->next;
		p->next = head->next;
		head->next = p;
	}
}
template<class T>
void LinkList<T>::MergeLinkList(LinkList<T>& La, LinkList<T>& Lb, LinkList<T>& Lc) {
	Lc.length = La.length + Lb.length;
	Node<T>* i = La.head->next;
	Node<T>* j = La.head->next;
	Node<T>* k = La.head->next;
	while (i < La.length && j < Lb.length) {
		if (La.data[i] < Lb.data[j]) {
			Lc.data[k] = La.data[i];
			k = k->next;
			i = i->next;
		} else Lc.data[k] = Lb.data[j];
		{
			k = k->next;
			j = j->next;
		}
	}
	while (i < La.length) {
		Lc.data[k] = La.data[i];
		k = k->next;
		i = i->next;
	}
	while (j < Lb.length) {
		Lc.data[k] = Lb.data[j];
		k = k->next;
		j = j->next;
	}
}
template <class T>
LinkList<T>:: ~LinkList() {
	Node<T>* p = head;
	while (p) {
		Node<T>* q = p;
		p = p->next;
		delete q;
	}
	head = NULL;
}
template<class T>
int LinkList<T>::Locate(string s) {
	int loc = 1;
	Node<T>* p = head->next;
	while (p && p->data.getid() != s)
		p = p->next, loc++;
	return loc;
}
template<class T>
void LinkList<T>::Sort() {
	int n = this->ListLength();
	for (int i = 1; i < n; i++)
		for (int j = 1; j < n - i; j++)
			if (Get(j) > Get(j + 1))
				swap(Get(j), Get(j + 1));
}
void SMNG() {
	bool opt = true;
	int n;
	int Loc;
	STU t;
	string s;
	string stmp;
	cout << "构造\n输入学生数以及内容（每行： 学号 姓名 性别 专业 出生年月YYYYMM ）" << endl;
	cin >> n;
	STU* a = new STU[n];
	for (int i = 0; i < n; i++)
		cin >> a[i];
	LinkList <STU>LList(a, n);
	while (opt == true) {
		system("pause");
		system("cls");
		cout << "**********\n";
		cout << "*0.退  出*\n";
		cout << "*1.查  看*\n";
		cout << "*2.修  改*\n";
		cout << "*3.删  除*\n";
		cout << "*4.排  序*\n";
		cout << "**********\n";
		cout << "选择：";
		char x;
		cin >> x;
		system("cls");
		switch (x) {
			case '0':
				opt = 0;
				break;
			case '1':
				cout << "你选择了1\n";
				LList.PrintLinkList();
				break;
			case '2':
				cout << "你选择了2\n";
				cout << "输入学号" << endl;
				cin >> s;
				Loc = LList.Locate(s);
				if (Loc) {
					cout << LList.Get(Loc) << endl;
					cout << "输入正确内容" << endl;
					cin >> t;
					LList.Get(Loc).Change(t);
				} else {
					cout << "无匹配，输入新学生" << endl;
					cin >> t;
					LList.Insert(LList.ListLength() + 1, t);
				}
				cout << endl;
				break;
			case '3':
				cout << "你选择了3\n";
				cout << "输入学号" << endl;
				cin >> s;
				LList.Delete(LList.Locate(s));
				break;
			case '4':
				cout << "你选择了4\n";
				LList.Sort();
				break;
			default:
				cout << "输入非法，请重新选择!\n";
				break;
		}
	}
}
int main() {
	SMNG();
}
