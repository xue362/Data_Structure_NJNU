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
			output << "ѧ�� " << t.id << "���� " << t.name << "�Ա� " << t.gender << "רҵ " << t.major << "�������� " << t.birth << endl;
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
		Node<T>* head; //�������ͷָ��
	public:
		LinkList(); //������ͷ���Ŀ�����
		LinkList(T a[], int n); //������n��Ԫ�صĵ�����
		~LinkList(); //��������
		int ListLength(); //������ĳ���
		T& Get(int pos); //��λ����
		Node<T>* Locate(T item); //��ֵ����
		int Locate(string s);
		void PrintLinkList(); //����������
		void Insert(int i, T item); //����Ԫ��
		T Delete(int i); //ɾ�����
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
	head = new Node<T>; //����ͷ���
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
		cerr << "����λ�÷Ƿ�";
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
	while (p && j < i - 1) { //�ҵ���i-1������λ��
		p = p->next;
		j++;
	}
	if (!p) {
		cerr << "����λ�÷Ƿ�";
		exit(1);
	} else {
		Node<T>* s = new Node<T>; //����Ԫ��ֵΪitem���½��s
		s->data = item;
		s->next = p->next; //�ú�巨��s���뵽���p�ĺ���
		p->next = s;
	}
}
template <class T>
T LinkList<T>::Delete(int i) {
	Node<T>* p = head;
	int j = 0;
	while (p && j < i - 1) { //���ҵ�i-1�����
		p = p->next;
		j++;
	}
	if (!p || !p->next) {
		cerr << "ɾ��λ�÷Ƿ�";
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
	cout << "����\n����ѧ�����Լ����ݣ�ÿ�У� ѧ�� ���� �Ա� רҵ ��������YYYYMM ��" << endl;
	cin >> n;
	STU* a = new STU[n];
	for (int i = 0; i < n; i++)
		cin >> a[i];
	LinkList <STU>LList(a, n);
	while (opt == true) {
		system("pause");
		system("cls");
		cout << "**********\n";
		cout << "*0.��  ��*\n";
		cout << "*1.��  ��*\n";
		cout << "*2.��  ��*\n";
		cout << "*3.ɾ  ��*\n";
		cout << "*4.��  ��*\n";
		cout << "**********\n";
		cout << "ѡ��";
		char x;
		cin >> x;
		system("cls");
		switch (x) {
			case '0':
				opt = 0;
				break;
			case '1':
				cout << "��ѡ����1\n";
				LList.PrintLinkList();
				break;
			case '2':
				cout << "��ѡ����2\n";
				cout << "����ѧ��" << endl;
				cin >> s;
				Loc = LList.Locate(s);
				if (Loc) {
					cout << LList.Get(Loc) << endl;
					cout << "������ȷ����" << endl;
					cin >> t;
					LList.Get(Loc).Change(t);
				} else {
					cout << "��ƥ�䣬������ѧ��" << endl;
					cin >> t;
					LList.Insert(LList.ListLength() + 1, t);
				}
				cout << endl;
				break;
			case '3':
				cout << "��ѡ����3\n";
				cout << "����ѧ��" << endl;
				cin >> s;
				LList.Delete(LList.Locate(s));
				break;
			case '4':
				cout << "��ѡ����4\n";
				LList.Sort();
				break;
			default:
				cout << "����Ƿ���������ѡ��!\n";
				break;
		}
	}
}
int main() {
	SMNG();
}
