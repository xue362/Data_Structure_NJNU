#include <iostream>
#include <algorithm>
#include <string>
#include<cstring>
using namespace std;

int BF(char* s, char* t)
{
	int index = 0;
	int i, j;
	for (i = 0, j = 0; s[i] != 0;)
	{
		if (s[i] == t[j])
			i++, j++;
		else i = ++index, j = 0;
		if (t[j] == 0)
			return index;
	}
	return -1;
}

void GetNext(char* p, int* ne)
{
    ne[0] = -1;
    int j = 0;
    int k = -1;
    int len = strlen(p);
    while (j < len)
    {
        if (k == -1 || p[j] == p[k])
            ne[++j] = ++k;
        else
            k = ne[k];
    }
}

void GetNextval(char *p, int* nextval)
{
    int i = 0,j = -1;
    nextval[0] = -1;
    int len = strlen(p);
    while (i < len)
    {
        if (j == -1 || p[i] == p[j])
        {
            if (p[++i] != p[++j])
                nextval[i] = j;
            else
                nextval[i] = nextval[j];
        }
        else
            j = nextval[j];
    }
}

int KMPMod(char* s, char* t)//¸Ä½øµÄKMP 
{
    int i = 0;
    int j = 0;
    int slen = strlen(s);
    int tlen = strlen(t);
    int* ne = new int[tlen];
    GetNextval(t, ne);
    while (i < slen && j < tlen)
    {
        if (j == -1 || s[i] == t[j])
            i++, j++;
        else
            j = ne[j];
    }
    if (j == tlen)
        return i - j;
    else
        return -1;
}
int KMP(char* s, char* t)
{
    int i = 0;
    int j = 0;
    int slen = strlen(s);
    int tlen = strlen(t);
    int* ne = new int[tlen];
    GetNext(t, ne);
    while (i < slen && j < tlen)
    {
        if (j == -1 || s[i] == t[j])
            i++,j++;
        else
            j = ne[j];
    }
    if (j == tlen)
        return i - j;
    else
        return -1;
}
int main()
{
	char s[] = "HString subs1, subs2; next[1] ";
	char t[] = "subs2";
    cout << BF(s, t) << endl;
    cout << KMP(s, t) << endl;
    cout << KMPMod(s, t) << endl;
}
