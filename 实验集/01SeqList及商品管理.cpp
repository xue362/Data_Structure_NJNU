#include<iostream>
#include<string>
using namespace std;

class Item {//商品类
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
			output << "商品代码 " << t.code << "商品名称 " << t.name << "价格 " << t.price << "库存 " << t.number << endl;
			return output;
		}
};
template <class T, int MaxSize>
class SeqList {//SeqList类
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
		cerr << "参数非法";
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
		cerr << "上溢";
		exit(1);
	}
	if (i < 1 || i > length + 1) {
		cerr << "插入位置非法";
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
		cerr << "下溢";
		exit(1);
	}
	if (i < 1 || i > length) {
		cerr << "删除位置非法";
		exit(1);
	}
	T x = data[i - 1];
	for (int j = i; j < length; j++)
		data[j - 1] = data[j];
	length--;
	return x;
}
template<class T, int MaxSize>
void SeqList<T, MaxSize>::MergeListSeq(SeqList<T, MaxSize>& La, SeqList<T, MaxSize>& Lb, SeqList<T, MaxSize>& Lc) {//归并两个有序顺序表
	if (La.length + Lb.length > MaxSize) {
		cerr << "溢出！";
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
void SeqList<T, MaxSize>::Sort() {//简单排序
	int n = ListLength();
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (data[j] > data[j + 1])
				swap(data[j], data[j + 1]);
}
template <class T, int MaxSize>
T& SeqList<T, MaxSize>::Get(int pos) {
	if (pos < 1 || pos > length) {
		cerr << "查找位置非法";
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
	cout << "构造\n输入元素个数以及内容（每行均为商品代码，名称，价格，库存）" << endl;
	cin >> n;
	Item* a = new Item[n];
	for (int i = 0; i < n; i++)
		cin >> a[i];
	SeqList <Item, 100>SList(a, n);
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
				SList.PrintSeqList();
				break;
			case '2':
				cout << "你选择了2\n";
				cout << "输入商品代码" << endl;
				cin >> s;
				Loc = SList.Locate(s);
				if (Loc) {
					cout << SList.Get(Loc) << endl;
					cout << "输入正确库存量" << endl;
					cin >> n;
					SList.Get(Loc).Changenum(n);
				} else {
					cout << "无匹配，输入新商品" << endl;
					cin >> t;
					SList.Insert(SList.ListLength() + 1, t);
				}
				cout << endl;
				break;
			case '3':
				cout << "你选择了3\n";
				cout << "输入商品代码" << endl;
				cin >> s;
				SList.Delete(SList.Locate(s));
				break;
			case '4':
				cout << "你选择了4\n";
				SList.Sort();
				break;
			default:
				cout << "输入非法，请重新选择!\n";
				break;
		}
	}
}

int main()
{
	IMNG();
}
