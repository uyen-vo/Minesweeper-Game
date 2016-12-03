#pragma once
#include <Windows.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_JPEG_Image.h>
#include <iostream>
#include <vector>
#include <FL/Fl_Output.H>
class Game;

using namespace std;

class Button : public Fl_Button {
public:
	Button(int a, int b, int c, int d, Game* g) : Fl_Button(a, b, c, d) {
		covered = new Fl_JPEG_Image("coveredTile.jpg");
		emptyUncovered = new Fl_JPEG_Image("emptyUncoveredTile.jpg");
		flagged = new Fl_JPEG_Image("flaggedMine.jpg");
		incorrect = new Fl_JPEG_Image("incorrectMine.jpg");
		losing = new Fl_JPEG_Image("losingMine.jpg");
		mine = new Fl_JPEG_Image("mine.jpg");
		question = new Fl_JPEG_Image("question.jpg");
		timer = new Fl_Output(109, 15, 30, 30);
		closed = false;
		flagStatus = 0;
		red = false;
		game = g;
		ender = false;
		nonBomb = false;
		open = false;
	};
	void resetTime();
	void flagTiles();
	int getFlagStatus();
	void setIndexOne(int one);
	int getIndexOne();
	void setIndexTwo(int two);
	int getIndexTwo();
	void closedTiles();
	void end();
	int handle(int event);
	void mineTiles();
	int getBombValue();
	void setBombValue(int value);
	void openTile();
	void close();
	void redMine();
	void drawRedMine();
	int clickType();
	bool checkCascade();
	void uncover();
	void printNumber();
	bool isClosed();
	void setNonBomb(bool b);
	bool isNonBomb();

private:
	int indexOne;
	int indexTwo;
	Fl_JPEG_Image* covered;
	Fl_JPEG_Image* emptyUncovered;
	Fl_JPEG_Image* flagged;
	Fl_JPEG_Image* incorrect;
	Fl_JPEG_Image* losing;
	Fl_JPEG_Image* mine;
	Fl_JPEG_Image* question;
	Fl_Output* timer;
	bool closed;
	int flagStatus;
	int bombValue;
	bool red;
	Game* game;
	bool ender;
	bool open;
	bool nonBomb;
	static int start;
};
