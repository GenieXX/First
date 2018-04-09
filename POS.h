#pragma once
#include "stdafx.h"
//#include "heah.h"

class Pos {
private:

public:
	int x;
	int y;

	Pos();
	Pos(int get_X, int get_Y);
	bool matchDirect(Pos a, Pos b);
	bool matchOneCorner(Pos a, Pos b);
	bool matchTwoCorner(Pos a, Pos b);
	bool match(Pos a, Pos b);
	void collide(Pos a, Pos b);
	int Num();
};