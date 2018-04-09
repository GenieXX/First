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
//�ж�ͼƬa��b֮���ܷ�ͨ��һ��ֱ��������a��b֮����0��ת�ǣ�  
bool Pos::matchDirect(Pos a, Pos b)
{
	if (!(a.x == b.x || a.y == b.y))
		return false;
	//a��b�ĺ�������ͬʱ  
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
	//a��b����������ͬʱ  
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
//�ж�ͼƬa��b֮���Ƿ����ͨ��һ��ת�ǵ���������  
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
//�ж�ͼƬa��b֮���Ƿ����ͨ������ת�ǵ���������  
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
//�ж�a��b�ܷ�������������a��b��������ͬ����a��b֮������߹ս���<=2��  
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