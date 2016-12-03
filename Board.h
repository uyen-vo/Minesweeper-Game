#pragma once
#include <vector>
#include "Button.h"
using namespace std;

class Board {
public:
	Board();
	void setWidth(int w);
	int getWidth();
	void setHeight(int h);
	int getHeight();
	void setMines(int m);
	int getMines();


private:
	int height;
	int width;
	int numMines;

};