#pragma once
#include "Game.h"
#include "Board.h"
#include "Button.h"
#include <Windows.h>
#include <Fl/FL.h>
#include <Fl/FL_Window.h>
#include <Fl/FL_Button.h>
#include <Fl/FL_JPEG_Image.H>
#include "Game.h"
#include <iostream>
#include <FL/Fl_Output.H>
#include <vector>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Input_.H>
#include <cstring>
#include <atlstr.h>
#include <cstringt.h>

class menuButton : public Fl_Button {
public:
	menuButton(int x, int y, int w, int h, int dim1, int dim2, int mine) : Fl_Button(x, y, w, h)
	{
		this->dim1 = dim1;
		this->dim2 = dim2;
		this->mine = mine;
	};
	int getW() { return dim1; }
	int getH() { return dim2; }
	int getM() { return mine; }
	void setW(int w) { dim1 = w; }
	void setH(int h) { dim2 = h; }
	void setM(int m) { mine = m; }
	

private:
	int dim1, dim2, mine;
};