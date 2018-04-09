#include "stdafx.h"
#include "POS.h"
using namespace std;

extern vector<Color> color;
extern int arr[10][14];

Pos::Pos()
{
	x = 0;
	y = 0;
}

Pos::Pos(int get_X, int get_Y)
{
	x = get_X;
	y = get_Y;
}

void Pos::collide(Pos a, Pos b) {
	//color[arr[a.x][a.y]].red = 255;
	//color[arr[a.x][a.y]].green = 255;
	//color[arr[a.x][a.y]].blue = 255;

	//color[arr[b.x][b.y]].red = 255;
	//color[arr[b.x][b.y]].green = 255;
	//color[arr[b.x][b.y]].blue = 255;

	arr[a.x][a.y] = 0;
	arr[b.x][b.y] = 0;
}

int Pos::Num() {
	int num = 8 * 12;
	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 13; j++)
		{
			if (arr[i][j] == 0)
				num--;
		}
	}
	return num;
}
//判断图片a和b之间能否通过一条直线相连（a和b之间有0个转角）  
bool Pos::matchDirect(Pos a, Pos b)
{
	if (!(a.x == b.x || a.y == b.y))
		return false;
	//a、b的横坐标相同时  
	bool yMatch = true;
	if (a.y == b.y)
	{
		if (a.x > b.x)
		{
			for (int i = b.x + 1;i < a.x;i++)
			{
				if (arr[i][a.y] != 0)
					yMatch = false;
			}
		}
		if (b.x > a.x)
		{
			for (int i = a.x + 1;i < b.x;i++)
			{
				if (arr[i][a.y] != 0)
					yMatch = false;
			}
		}
	}
	//a、b的纵坐标相同时  
	bool xMatch = true;
	if (a.x == b.x)
	{
		if (a.y > b.y)
		{
			for (int i = b.y + 1;i < a.y;i++)
			{
				if (arr[a.x][i] != 0)
					xMatch = false;
			}
		}
		if (b.y > a.y)
		{
			for (int i = a.y + 1;i < b.y;i++)
			{
				if (arr[a.x][i] != 0)
					xMatch = false;
			}
		}
	}
	return (xMatch && yMatch);
}
//判断图片a和b之间是否可以通过一个转角的折线相连  
bool Pos::matchOneCorner(Pos a, Pos b)
{
	Pos tmp;
	tmp.x = a.x;
	tmp.y = b.y;

	if (arr[a.x][b.y] == 0 && matchDirect(a, tmp) && matchDirect(tmp, b))
	{
		//collide(a, tmp);
		//collide(tmp, b);
		collide(a, b);
		return true;
	}
	tmp.x = b.x;
	tmp.y = a.y;
	if (arr[b.x][a.y] == 0 && matchDirect(a, tmp) && matchDirect(tmp, b))
	{
		//collide(a, tmp);
		//collide(tmp, b);
		collide(a, b);
		return true;
	}
	return false;
}
//判断图片a和b之间是否可以通过两个转角的折线相连  
bool Pos::matchTwoCorner(Pos a, Pos b)
{
	int i, j;
	int num = Num();

	for (i = a.y - 1, j = a.x;i >= 0;i--)
	{
		Pos tmp;
		tmp.x = j;
		tmp.y = i;
		if (arr[j][i] != 0)
		{
			break;
		}
		else if (matchOneCorner(b, tmp))
		{
			collide(a, tmp);
			return true;
		}
	}

	for (i = a.y + 1, j = a.x;i < 14;i++)
	{
		Pos tmp;
		tmp.x = j;
		tmp.y = i;
		if (arr[j][i] != 0)
		{
			break;
		}
		else if (matchOneCorner(b, tmp))
		{
			collide(a, tmp);
			return true;
		}
	}
	for (i = a.y, j = a.x - 1;j >= 0;j--)
	{
		Pos tmp;
		tmp.x = j;
		tmp.y = i;
		if (arr[j][i] != 0)
		{
			break;
		}
		else if (matchOneCorner(b, tmp))
		{
			collide(a, tmp);
			return true;
		}
	}
	for (i = a.y, j = a.x + 1;j < 10;j++)
	{
		Pos tmp;
		tmp.x = j;
		tmp.y = i;
		if (arr[j][i] != 0)
		{
			break;
		}
		else if (matchOneCorner(b, tmp))
		{
			collide(a, tmp);
			return true;
		}
	}
	return false;
}
//判断a和b能否相连，条件是a和b的类型相同，且a和b之间的连线拐角数<=2个  
bool Pos::match(Pos a, Pos b)
{
	if (a.x == b.x && a.y == b.y)
		return false;
	else if (arr[a.x][a.y] != arr[b.x][b.y])
		return false;
	else if (matchDirect(a, b))
	{
		collide(a, b);
		return true;
	}
	else if (matchOneCorner(a, b))
		return true;
	else if (matchTwoCorner(a, b))
		return true;
	return false;
}