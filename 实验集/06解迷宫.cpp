#include<iostream>
using namespace std;

const int SIZE = 64;
const int M = 10;
const int N = 10;
const int m = 8;
const int n = 8;

struct SqType {
	int x, y;
	int pre;
};

struct moved {
	int x, y;
};
void PrintPath(SqType sq[], int rear) {
	int i = rear;
	while (i != 0) {
		cout << "(" << sq[i].x << "," << sq[i].y << ")" << endl;
		i = sq[i].pre;
	}
}
void FindShortPath(int maze[][N]) {
	int i, j, v, front, rear, x, y;
	struct moved move[8] = {
		{-1, -1},
		{-1, 0},
		{-1, 1},
		{0, -1},
		{0, 1},
		{1, -1},
		{1, 0},
		{1, 1}
	};
	SqType sq[SIZE];
	sq[1].x = 1;
	sq[1].y = 1;
	sq[1].pre = 0;
	front = 1;
	rear = 1;
	maze[1][1] = -1;							//标记防止重复到达
	while (front <= rear) {
		x = sq[front].x;
		y = sq[front].y;
		for (v = 0; v < 8; v++) {
			i = x + move[v].x;
			j = y + move[v].y;
			if (maze[i][j] == 0) {			//寻到路，进行赋值
				rear++;
				sq[rear].x = i;
				sq[rear].y = j;
				sq[rear].pre = front;
				maze[i][j] = -1;
				if ((i == m) && (j == n)) {
					PrintPath(sq, rear);
					return;
				}
			}
		}
		front++;
	}
	return;
}
int main() {
	int maze[10][10] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 1, 0, 1, 0, 0, 1, 1},
		{1, 1, 0, 1, 0, 1, 1, 0, 0, 1},
		{1, 1, 0, 0, 0, 0, 1, 1, 0, 1},
		{1, 1, 1, 0, 1, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
		{1, 1, 0, 0, 0, 0, 1, 1, 1, 1},
		{1, 1, 1, 0, 1, 0, 0, 0, 1, 1},
		{1, 1, 1, 0, 1, 1, 1, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	FindShortPath(maze);
	return 0;
}
