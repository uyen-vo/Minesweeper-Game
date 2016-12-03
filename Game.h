#pragma once
#include "Board.h"
#include "Button.h"
#include "menuButton.h"
#include <Windows.h>
#include <FL/Fl.h>
#include <FL/Fl_Window.h>
#include <FL/Fl_Box.H>
#include <FL/Fl_JPEG_Image.h>
#include <FL/Fl_Button.h>
#include <FL/Fl_Timer.H>
#include <iostream>
#include <cstring>
#include <atlstr.h>
#include <cstringt.h>
#include <vector>
#include <FL/Fl_Output.H>

using namespace std;

class Game : public Fl_Window {
public:

	Game(int a, int b) : Fl_Window(a, b) {
		color(FL_BACKGROUND_COLOR);
		debugger = false;
		status = new menuButton(2, 10 , 80, 40, 0, 0, 0);
		counter = new Fl_Output(85, 15, 23, 30);
		CString count;
		numOpened = 0;
		timeCount = 0;
		firstClick = false;
	};
	bool getDebug();
	void setDebug(bool d);
	void createButtons();
	void createDimensions(Board* b);
	void counterCallback(Fl_Widget* w, void*);
	void openBox(int indexOne, int indexTwo);
	void lose(int indexOne, int indexTwo);
	bool isWinner();
	void firstMouseClick();
	bool first();
	void gameStatus();
	bool progressButton();
	void createMineBoard();
	void debug();
	void assignValue();
	void increaseMineCount();
	void decreaseMineCount();
	void updateCounter();
	void clearAdjacent(int indexOne, int indexTwo, int b);

private:
	int timeCount;
	int h;
	int w;
	int numBombsOnBoard;
	vector<vector<Button*> > allButtons;
	vector<vector<int> > bombs;
	bool debugger;
	menuButton* status;
	Fl_Output* counter;
	CString count;
	int numOpened;
	bool firstClick;

};