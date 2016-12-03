#include "Board.h"
#include <vector>
#include <Windows.h>
#include <FL/Fl.h>
#include <FL/Fl_Window.h>
#include <FL/Fl_Box.H>
#include <FL/Fl_JPEG_Image.h>
#include <FL/Fl_Button.h>
#include <iostream>

Board::Board() {
	height = 0;
	width = 0;
	numMines = 0;
}

void Board::setWidth(int w) { width = w; }
void Board::setHeight(int h) {	height = h;	}
void Board::setMines(int m) { numMines = m; }
int Board::getWidth() { return width; }
int Board::getHeight() { return height; }
int Board::getMines() { return numMines; }
