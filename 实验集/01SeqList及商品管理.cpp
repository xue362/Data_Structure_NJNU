#include<iostream>
#include<string>
using namespace std;

class Item {//��Ʒ��
		string code;
		string name;
		int price;
		int number;
	public:
		Item() {
			code = "0";
			name = "";
			price = 0;
			number = 0;
		}
		void Changenum(int x) {
			number = x;
		}
		string Getcode() {
			return code;
		}
		bool operator <(const Item& t) {
			return (code < t.code);
		}
		bool operator >(const Item& t) {
			return (code > t.code);
		}
		friend istream& operator>>(istream& input, Item& t) {
			input >> t.code >> t.name >> t.price >> t.number;
			return input;
		}
		friend ostream& operator<<(ostream& output, const Item& t) {
			output << "��Ʒ���� " << t.code << "��Ʒ���� " << t.name << "�۸� " << t.price << "��� " << t.number << endl;
			return output;
		}
};
template <class T, int MaxSize>
class SeqList {//SeqList��
		T data[MaxSize];
		int length;
	public:
		SeqList();
		SeqList(T a[], int n);
		int ListLength();
		T& Get(int pos);
		int Locate(string s);
		int Locate(T item);
		void PrintSeqList();
		void Insert(int i, T item);
		T Delete(int i);
		void MergeListSeq(SeqList<T, MaxSize>& La, SeqList<T, MaxSize>& Lb, SeqList<T, MaxSize>& Lc);
		void Sort();
};
template <class T, int MaxSize>
SeqList<T, MaxSize >::SeqList() {
	length = 0;
}
template <class T, int MaxSize>
SeqList<T, MaxSize>::SeqList(T a[], int n) {
	if (n > MaxSize) {
		cerr << "�����Ƿ�";
		exit(1);
	}
	for (int i = 0; i < n; i++) data[i] = a[i];
	length = n;
}
template<class T, int MaxSize>
int SeqList<T, MaxSize>::ListLength() {
	return length;
}
template <class T, int MaxSize>
void SeqList<T, MaxSize>::Insert(int i, T item) {
	if (length >= MaxSize) {
		cerr << "����";
		exit(1);
	}
	if (i < 1 || i > length + 1) {
		cerr << "����λ�÷Ƿ�";
		exit(1);
	}
	for (int j = length - 1; j >= i - 1; j--)
		data[j + 1] = data[j];
	data[i - 1] = item;
	length++;
}
template <class T, int MaxSize>
T SeqList<T, MaxSize>::Delete(int i) {
	if (length == 0) {
		cerr << "����";
		exit(1);
	}
	if (i < 1 || i > length) {
		cerr << "ɾ��λ�÷Ƿ�";
		exit(1);
	}
	T x = data[i - 1];
	for (int j = i; j < length; j++)
		data[j - 1] = data[j];
	length--;
	return x;
}
template<class T, int MaxSize>
void SeqList<T, MaxSize>::MergeListSeq(SeqList<T, MaxSize>& La, SeqList<T, MaxSize>& Lb, SeqList<T, MaxSize>& Lc) {//�鲢��������˳���
	if (La.length + Lb.length > MaxSize) {
		cerr << "�����";
		exit(1);
	}
	Lc.length = La.length + Lb.length;
	int i = 0, j = 0, k = 0;
	while (i < La.length && j < Lb.length) {
		if (La.data[i] < Lb.data[j]) Lc.data[k++] = La.data[i++];
		else Lc.data[k++] = Lb.data[j++];
	}
	while (i < La.length) Lc.data[k++] = La.data[i++];
	while (j < Lb.length) Lc.data[k++] = Lb.data[j++];
}
template<class T, int MaxSize>
void SeqList<T, MaxSize>::Sort() {//������
	int n = ListLength();
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (data[j] > data[j + 1])
				swap(data[j], data[j + 1]);
}
template <class T, int MaxSize>
T& SeqList<T, MaxSize>::Get(int pos) {
	if (pos < 1 || pos > length) {
		cerr << "����λ�÷Ƿ�";
		exit(1);
	} else
		return data[pos - 1];
}
template <class T, int MaxSize>
int SeqList<T, MaxSize>::Locate(T item) {
	for (int i = 0; i < length; i++)
		if (data[i] == item)
			return i + 1;
	return 0;
}
template <class T, int MaxSize>
int SeqList<T, MaxSize>::Locate(string s) {
	for (int i = 0; i < length; i++)
		if (data[i].Getcode() == s)
			return i + 1;
	return 0;
}
template <class T, int MaxSize>
void SeqList<T, MaxSize>::PrintSeqList() {
	for (int i = 0; i < length; i++)
		cout << data[i];
	cout << endl;
}
void IMNG() {
	bool opt = true;
	int n, Loc;
	Item t;
	string s;
	cout << "����\n����Ԫ�ظ����Լ����ݣ�ÿ�о�Ϊ��Ʒ���룬���ƣ��۸񣬿�棩" << endl;
	cin >> n;
	Item* a = new Item[n];
	for (int i = 0; i < n; i++)
		cin >> a[i];
	SeqList <Item, 100>SList(a, n);
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
				SList.PrintSeqList();
				break;
			case '2':
				cout << "��ѡ����2\n";
				cout << "������Ʒ����" << endl;
				cin >> s;
				Loc = SList.Locate(s);
				if (Loc) {
					cout << SList.Get(Loc) << endl;
					cout << "������ȷ�����" << endl;
					cin >> n;
					SList.Get(Loc).Changenum(n);
				} else {
					cout << "��ƥ�䣬��������Ʒ" << endl;
					cin >> t;
					SList.Insert(SList.ListLength() + 1, t);
				}
				cout << endl;
				break;
			case '3':
				cout << "��ѡ����3\n";
				cout << "������Ʒ����" << endl;
				cin >> s;
				SList.Delete(SList.Locate(s));
				break;
			case '4':
				cout << "��ѡ����4\n";
				SList.Sort();
				break;
			default:
				cout << "����Ƿ���������ѡ��!\n";
				break;
		}
	}
}

int main()
{
	IMNG();
}
