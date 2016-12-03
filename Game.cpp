#include "Game.h"
#include "Board.h"
#include "Button.h"
#include <Windows.h>
#include <FL/Fl.h>
#include <FL/Fl_Output.H>
#include <FL/Fl_Window.h>
#include <FL/Fl_Box.H>
#include <FL/Fl_JPEG_Image.h>
#include <FL/Fl_Button.h>
#include <FL/Fl_Timer.H>
#include <iostream>
#include <time.h>
#include <vector>
#include <cstring>
#include <atlstr.h>
#include <cstringt.h>
#include "menuButton.h"
#include <string>

bool debug1 = false;

bool Game::first() {
	return firstClick;
}

void Game::firstMouseClick() {
	firstClick = true;
}

void Game::createMineBoard() {
	srand(time(NULL));
	bombs.resize(w, vector<int>(h, 0));
	for (int i = 0; i < numBombsOnBoard; i++) {
		bool bombpresent = true;
		int x;
		int y;
		while (bombpresent == true) {

			x = rand() % w;
			y = rand() % h;
			if (bombs.at(x).at(y) == 0) {
				bombpresent = false;
				bombs.at(x).at(y) = 9;
			}
		}
	}

	int numBombs;
	int x = 0;
	int y = 0;



	x = 0;
	y = 0;

	numBombs = 0;
	for (y = 1; y < h - 1; y++) {
		if (bombs.at(x).at(y) != 9) {
			numBombs = 0;
			if (bombs.at(x).at(y - 1) == 9) numBombs++;
			if (bombs.at(x).at(y + 1) == 9) numBombs++;
			if (bombs.at(x + 1).at(y + 1) == 9) numBombs++;
			if (bombs.at(x + 1).at(y - 1) == 9) numBombs++;
			if (bombs.at(x + 1).at(y) == 9) numBombs++;
			bombs.at(x).at(y) = numBombs;
		}
	}


	x = w - 1;
	y = 0;

	numBombs = 0;
	for (y = 1; y < h - 1; y++) {
		if (bombs.at(x).at(y) != 9) {
			numBombs = 0;
			if (bombs.at(x).at(y - 1) == 9) numBombs++;
			if (bombs.at(x).at(y + 1) == 9) numBombs++;
			if (bombs.at(x - 1).at(y + 1) == 9) numBombs++;
			if (bombs.at(x - 1).at(y - 1) == 9) numBombs++;
			if (bombs.at(x - 1).at(y) == 9) numBombs++;
			bombs.at(x).at(y) = numBombs;
		}
	}


	x = 0;
	y = 0;

	numBombs = 0;
	for (x = 1; x < w - 1; x++) {
		if (bombs.at(x).at(y) != 9) {
			numBombs = 0;
			if (bombs.at(x - 1).at(y) == 9) numBombs++;
			if (bombs.at(x + 1).at(y) == 9) numBombs++;
			if (bombs.at(x + 1).at(y + 1) == 9) numBombs++;
			if (bombs.at(x).at(y + 1) == 9) numBombs++;
			if (bombs.at(x - 1).at(y + 1) == 9) numBombs++;
			bombs.at(x).at(y) = numBombs;
		}
	}

	x = 0;
	y = h - 1;

	numBombs = 0;
	for (x = 1; x < w - 1; x++) {
		if (bombs.at(x).at(y) != 9) {
			numBombs = 0;
			if (bombs.at(x - 1).at(y) == 9) numBombs++;
			if (bombs.at(x + 1).at(y) == 9) numBombs++;
			if (bombs.at(x + 1).at(y - 1) == 9) numBombs++;
			if (bombs.at(x).at(y - 1) == 9) numBombs++;
			if (bombs.at(x - 1).at(y - 1) == 9) numBombs++;
			bombs.at(x).at(y) = numBombs;
		}
	}

	//--------------------------------------------
	x = 0;
	y = 0;
	if (bombs.at(0).at(0) != 9) {
		numBombs = 0;
		if (bombs.at(1).at(0) == 9) numBombs++;
		if (bombs.at(0).at(1) == 9) numBombs++;
		if (bombs.at(1).at(1) == 9) numBombs++;
		bombs.at(0).at(0) = numBombs;
	}

	x = w;
	y = h;
	if (bombs.at(x - 1).at(y - 1) != 9) {
		numBombs = 0;
		if (bombs.at(x - 2).at(y - 1) == 9) numBombs++;
		if (bombs.at(x - 2).at(y - 2) == 9) numBombs++;
		if (bombs.at(x - 1).at(y - 2) == 9) numBombs++;
		bombs.at(x - 1).at(y - 1) = numBombs;
	}

	x = 0;
	y = h;
	if (bombs.at(x).at(y - 1) != 9) {
		numBombs = 0;
		if (bombs.at(0).at(y - 2) == 9) numBombs++;
		if (bombs.at(1).at(y - 1) == 9) numBombs++;
		if (bombs.at(1).at(y - 2) == 9) numBombs++;
		bombs.at(0).at(y - 1) = numBombs;
	}

	x = w;
	y = 0;
	if (bombs.at(x - 1).at(y) != 9) {
		numBombs = 0;
		if (bombs.at(x - 1).at(1) == 9) numBombs++;
		if (bombs.at(x - 2).at(0) == 9) numBombs++;
		if (bombs.at(x - 2).at(1) == 9) numBombs++;
		bombs.at(x - 1).at(0) = numBombs;
	}



	for (int x = 1; x < w - 1; x++) {
		for (int y = 1; y < h - 1; y++) {
			if (bombs.at(x).at(y) != 9) {
				int numBombs = 0;
				if (bombs.at(x - 1).at(y - 1) == 9) numBombs = numBombs + 1;
				if (bombs.at(x - 1).at(y) == 9) numBombs = numBombs + 1;
				if (bombs.at(x - 1).at(y + 1) == 9) numBombs = numBombs + 1;
				if (bombs.at(x).at(y - 1) == 9) numBombs = numBombs + 1;
				if (bombs.at(x).at(y + 1) == 9) numBombs = numBombs + 1;
				if (bombs.at(x + 1).at(y - 1) == 9) numBombs = numBombs + 1;
				if (bombs.at(x + 1).at(y) == 9) numBombs = numBombs + 1;
				if (bombs.at(x + 1).at(y + 1) == 9) numBombs = numBombs + 1;
				bombs.at(x).at(y) = numBombs;
			}
		}
	}
}

void Game::setDebug(bool d) { debugger = d; }

bool Game::getDebug() { return debugger; }

void Game::debug() {
	if (debugger) {
		int count = 0;
		for (int x = 0; x < h; x++) {
			for (int y = 0; y < w; y++) {
				cout << bombs.at(y).at(x) << " ";
				if (bombs.at(y).at(x) == 9) count++;
			}
			cout << endl;
		}
		cout << "number of bombs: " << count << endl;
		cout << "* indicates bomb, # indicates number" << endl << endl;
		cout << "time status: " << firstClick << endl;
	}
}

void Game::assignValue() {
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			allButtons.at(i).at(j)->setBombValue(bombs.at(i).at(j));
			if (debugger) {
				if (allButtons.at(i).at(j)->getBombValue() == 9) {
					allButtons.at(i).at(j)->label("*");
					allButtons.at(i).at(j)->align(FL_ALIGN_IMAGE_BACKDROP);
				}
				else if (allButtons.at(i).at(j)->getBombValue() != 0) {
					allButtons.at(i).at(j)->label("#");
					allButtons.at(i).at(j)->align(FL_ALIGN_IMAGE_BACKDROP);
				}
			}
			if (allButtons.at(i).at(j)->getBombValue() != 9) {
				allButtons.at(i).at(j)->setNonBomb(true);
			}
		}
	}
}

void Game::createDimensions(Board* b) {
	h = b->getHeight();
	w = b->getWidth();
	numBombsOnBoard = b->getMines();

	status->setW(w);
	status->setH(h);
	status->setM(numBombsOnBoard);
	status->label("In Progress");

	allButtons.resize(w);
	for (int i = 0; i < w; i++) {
		allButtons[i].resize(h);
	}
}

void Game::decreaseMineCount() { numBombsOnBoard--; cout << "mine counter: " << numBombsOnBoard << endl; 
	updateCounter();
}

void Game::increaseMineCount() { numBombsOnBoard++; cout << "mine counter: " << numBombsOnBoard << endl;
	updateCounter();
}

void Game::createButtons() {

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			allButtons.at(i).at(j) = new Button(i * 15, j * 15 + 60, 15, 15, this);
			allButtons.at(i).at(j)->setIndexOne(i);
			allButtons.at(i).at(j)->setIndexTwo(j);
			allButtons.at(i).at(j)->closedTiles();
		}
	}
}

void Game::clearAdjacent(int indexOne, int indexTwo, int b) {
	int count = 0;
	if (indexOne != (w - 1) && indexTwo != (h - 1) && indexOne != 0 && indexTwo != 0) {
		for (int i = indexOne - 1; i <= indexOne + 1; i++) {
			for (int j = indexTwo - 1; j <= indexTwo + 1; j++) {
				if (i == w || j == h) { return; }
				else if (allButtons.at(i).at(j)->getFlagStatus() == 1) {
					count++;
				}
			}
		}
	}

	//left edge
	else if (indexOne == 0 && indexTwo != 0 && indexTwo != (h - 1)) {
		for (int i = indexOne; i <= indexOne + 1; i++) {
			for (int j = indexTwo - 1; j <= indexTwo + 1; j++) {
				if (i == w || j == h) { return; }
				else if (allButtons.at(i).at(j)->getFlagStatus() == 1) {
					count++;
				}
			}
		}
	}

	//right edge
	else if (indexOne == (w - 1) && indexTwo != 0 && indexTwo != (h - 1)) {
		for (int i = indexOne - 1; i <= indexOne; i++) {
			for (int j = indexTwo - 1; j <= indexTwo + 1; j++) {
				if (i == w || j == h) { return; }
				else if (allButtons.at(i).at(j)->getFlagStatus() == 1) {
					count++;
				}
			}
		}
	}

	//bottom edge

	else if (indexTwo == (h - 1) && indexOne != 0 && indexOne != (w - 1)) {
		for (int i = indexOne - 1; i <= indexOne + 1; i++) {
			for (int j = indexTwo - 1; j <= indexTwo; j++) {
				if (i == w || j == h) { return; }
				else if (allButtons.at(i).at(j)->getFlagStatus() == 1) {
					count++;
				}
			}
		}
	}

	//top edge
	else if (indexTwo == 0 && indexOne != 0 && indexTwo != (w - 1)) {
		for (int i = indexOne - 1; i <= indexOne + 1; i++) {
			for (int j = indexTwo; j <= indexTwo + 1; j++) {
				if (i == w || j == h) { return; }
				else if (allButtons.at(i).at(j)->getFlagStatus() == 1) {
					count++;
				}
			}
		}
	}

	//top left corner
	else if (indexTwo == 0 && indexOne == 0) {
		for (int i = indexOne; i <= indexOne + 1; i++) {
			for (int j = indexTwo; j <= indexTwo + 1; j++) {
				if (i == w || j == h) { return; }
				else if (allButtons.at(i).at(j)->getFlagStatus() == 1) {
					count++;
				}
			}
		}
	}
	//top right corner
	else if (indexOne == (w - 1) && indexTwo == 0) {
		for (int i = indexOne - 1; i <= indexOne; i++) {
			for (int j = indexTwo; j <= indexTwo + 1; j++) {
				if (i == w || j == h) { return; }
				else if (allButtons.at(i).at(j)->getFlagStatus() == 1) {
					count++;
				}
			}
		}
	}
	//bottom left corner
	else if (indexOne == 0 && indexTwo == (h - 1)) {
		for (int i = indexOne; i <= indexOne + 1; i++) {
			for (int j = indexTwo - 1; j <= indexTwo; j++) {
				if (i == w || j == h) { return; }
				else if (allButtons.at(i).at(j)->getFlagStatus() == 1) {
					count++;
				}
			}
		}
	}
	//bottom right corner
	else if (indexOne == (w - 1) && indexTwo == (h - 1)) {
		for (int i = indexOne - 1; i <= indexOne; i++) {
			for (int j = indexTwo - 1; j <= indexTwo; j++) {
				if (i == w || j == h) { return; }
				else if (allButtons.at(i).at(j)->getFlagStatus() == 1) {
					count++;
				}
			}
		}
	}
	if (debugger) {
		cout << "flag count: " << count << endl;
	}


	/////////////////////////////////////////////////////////////
	
	
	
	if (count == b) {
	
		if (indexOne != (w - 1) && indexTwo != (h - 1) && indexOne != 0 && indexTwo != 0) {
			for (int i = indexOne - 1; i <= indexOne + 1; i++) {
				for (int j = indexTwo - 1; j <= indexTwo + 1; j++) {
					if (i == w || j == h) { return; }
					else if (allButtons.at(i).at(j)->getFlagStatus() != 1) {
						if (allButtons.at(i).at(j)->getBombValue() == 0) {
							openBox(i, j);
						}
						else {
							allButtons.at(i).at(j)->uncover();
						}
					}
				}
			}
		}

		//left edge
		else if (indexOne == 0 && indexTwo != 0 && indexTwo != (h - 1)) {
			for (int i = indexOne; i <= indexOne + 1; i++) {
				for (int j = indexTwo - 1; j <= indexTwo + 1; j++) {
					if (i == w || j == h || allButtons.at(i).at(j)->getBombValue() == 9) { return; }
					else if (allButtons.at(i).at(j)->getFlagStatus() != 1) {
						if (allButtons.at(i).at(j)->getBombValue() == 0) {
							openBox(i, j);
						}
						else {
							allButtons.at(i).at(j)->uncover();
						}
					}
				}
			}
		}

		//right edge
		else if (indexOne == (w - 1) && indexTwo != 0 && indexTwo != (h - 1)) {
			for (int i = indexOne - 1; i <= indexOne; i++) {
				for (int j = indexTwo - 1; j <= indexTwo + 1; j++) {
					if (i == w || j == h) { return; }
					else if (allButtons.at(i).at(j)->getFlagStatus() != 1) {
						if (allButtons.at(i).at(j)->getBombValue() == 0) {
							openBox(i, j);
						}
						else {
							allButtons.at(i).at(j)->uncover();
						}
					}
				}
			}
		}

		//bottom edge

		else if (indexTwo == (h - 1) && indexOne != 0 && indexOne != (w - 1)) {
			for (int i = indexOne - 1; i <= indexOne + 1; i++) {
				for (int j = indexTwo - 1; j <= indexTwo; j++) {
					if (i == w || j == h) { return; }
					else if (allButtons.at(i).at(j)->getFlagStatus() != 1) {
						if (allButtons.at(i).at(j)->getBombValue() == 0) {
							openBox(i, j);
						}
						else {
							allButtons.at(i).at(j)->uncover();
						}
					}
				}
			}
		}

		//top edge
		else if (indexTwo == 0 && indexOne != 0 && indexTwo != (w - 1)) {
			for (int i = indexOne - 1; i <= indexOne + 1; i++) {
				for (int j = indexTwo; j <= indexTwo + 1; j++) {
					if (i == w || j == h) { return; }
					else if (allButtons.at(i).at(j)->getFlagStatus() != 1) {
						if (allButtons.at(i).at(j)->getBombValue() == 0) {
							openBox(i, j);
						}
						else {
							allButtons.at(i).at(j)->uncover();
						}
					}
				}
			}
		}

		//top left corner
		else if (indexTwo == 0 && indexOne == 0) {
			for (int i = indexOne; i <= indexOne + 1; i++) {
				for (int j = indexTwo; j <= indexTwo + 1; j++) {
					if (i == w || j == h) { return; }
					else if (allButtons.at(i).at(j)->getFlagStatus() != 1) {
						if (allButtons.at(i).at(j)->getBombValue() == 0) {
							openBox(i, j);
						}
						else {
							allButtons.at(i).at(j)->uncover();
						}
					}
				}
			}
		}
		//top right corner
		else if (indexOne == (w - 1) && indexTwo == 0) {
			for (int i = indexOne - 1; i <= indexOne; i++) {
				for (int j = indexTwo; j <= indexTwo + 1; j++) {
					if (i == w || j == h) { return; }
					else if (allButtons.at(i).at(j)->getFlagStatus() != 1) {
						if (allButtons.at(i).at(j)->getBombValue() == 0) {
							openBox(i, j);
						}
						else {
							allButtons.at(i).at(j)->uncover();
						}
					}
				}
			}
		}
		//bottom left corner
		else if (indexOne == 0 && indexTwo == (h - 1)) {
			for (int i = indexOne; i <= indexOne + 1; i++) {
				for (int j = indexTwo - 1; j <= indexTwo; j++) {
					if (i == w || j == h) { return; }
					else if (allButtons.at(i).at(j)->getFlagStatus() != 1) {
						if (allButtons.at(i).at(j)->getBombValue() == 0) {
							openBox(i, j);
						}
						else {
							allButtons.at(i).at(j)->uncover();
						}
					}
				}
			}
		}
		//bottom right corner
		else if (indexOne == (w - 1) && indexTwo == (h - 1)) {
			for (int i = indexOne - 1; i <= indexOne; i++) {
				for (int j = indexTwo - 1; j <= indexTwo; j++) {
					if (i == w || j == h) { return; }
					else if (allButtons.at(i).at(j)->getFlagStatus() != 1) {
						if (allButtons.at(i).at(j)->getBombValue() == 0) {
							openBox(i, j);
						}
						else {
							allButtons.at(i).at(j)->uncover();
						}
					}
				}
			}
		}
	}
	}

void statusCallback(Fl_Widget* widget, void*) {
	menuButton* button = dynamic_cast<menuButton*>(widget);
	
	

	button->window()->hide();
	button->deactivate();
	int w = button->getW();
	int h = button->getH();
	int m = button->getM();

	Game* p = new Game(15 * w, 15 * h + 60);
	Board* b = new Board();
	p->setDebug(debug1);
	b->setWidth(w);
	b->setHeight(h);
	b->setMines(m);
	p->createDimensions(b);
	p->createMineBoard();
	p->createButtons();
	p->assignValue();
	p->debug();
	p->updateCounter();
	p->gameStatus();
	p->redraw();
	p->end();
	p->show();
	Fl::run();
}

void Game::counterCallback(Fl_Widget* w, void*) {

}

void Game::openBox(int indexOne, int indexTwo) {
	int clue = allButtons.at(indexOne).at(indexTwo)->getBombValue();
	bool open = allButtons.at(indexOne).at(indexTwo)->checkCascade();
	
	if (clue == 9) {
		return;
	}
		if (clue == 0) {
		if (indexOne != (w - 1) && indexTwo != (h - 1) && indexOne != 0 && indexTwo != 0) {
			for (int i = indexOne - 1; i <= indexOne + 1; i++) {
				for (int j = indexTwo - 1; j <= indexTwo + 1; j++) {
					if (i == w || j == h) { return; }
					else if (!allButtons.at(i).at(j)->checkCascade()) {
						if (allButtons.at(i).at(j)->getFlagStatus() != 1) {
							allButtons.at(i).at(j)->uncover();
							openBox(i, j);
						}
					}
				}
			}
		}

		//left edge
		else if (indexOne == 0 && indexTwo != 0 && indexTwo != (h - 1)) {
			for (int i = indexOne; i <= indexOne + 1; i++) {
				for (int j = indexTwo - 1; j <= indexTwo + 1; j++) {
					if (i == w || j == h ) { return; }
					else if (!allButtons.at(i).at(j)->checkCascade()) {
						if (allButtons.at(i).at(j)->getFlagStatus() != 1) {
							allButtons.at(i).at(j)->uncover();
							openBox(i, j);
						}
					}
				}
			}
		}

		//right edge
		else if (indexOne == (w - 1) && indexTwo != 0 && indexTwo != (h - 1)) {
			for (int i = indexOne - 1; i <= indexOne; i++) {
				for (int j = indexTwo - 1; j <= indexTwo+1; j++) {
					if (i == w || j == h) { return; }
					else if (!allButtons.at(i).at(j)->checkCascade()) {
						if (allButtons.at(i).at(j)->getFlagStatus() != 1) {
							allButtons.at(i).at(j)->uncover();
							openBox(i, j);
						}
					}
				}
			}
		}

		//bottom edge

		else if (indexTwo == (h-1) && indexOne!=0 && indexOne != (w-1)) {
			for (int i = indexOne - 1; i <= indexOne + 1; i++) {
				for (int j = indexTwo - 1; j <= indexTwo; j++) {
					if (i == w || j == h) { return; }
					else if (!allButtons.at(i).at(j)->checkCascade()) {
						if (allButtons.at(i).at(j)->getFlagStatus() != 1) {
							allButtons.at(i).at(j)->uncover();
							openBox(i, j);
						}
					}
				}	
			}
		}

		//top edge
		else if (indexTwo == 0 && indexOne != 0 && indexTwo != (w - 1)) {
			for (int i = indexOne - 1; i <= indexOne + 1; i++) {
				for (int j = indexTwo; j <= indexTwo + 1; j++) {
					if (i == w || j == h) { return; }
					else if (!allButtons.at(i).at(j)->checkCascade()) {
						if (allButtons.at(i).at(j)->getFlagStatus() != 1) {
							allButtons.at(i).at(j)->uncover();
							openBox(i, j);
						}
					}
					else {}
				}
			}
		}

		//top left corner
		else if (indexTwo == 0 && indexOne == 0) {
			for (int i = indexOne; i <= indexOne + 1; i++) {
				for (int j = indexTwo; j <= indexTwo + 1; j++) {
					if (i == w || j == h) { return; }
					else if (!allButtons.at(i).at(j)->checkCascade()) {
						if (allButtons.at(i).at(j)->getFlagStatus() != 1) {
							allButtons.at(i).at(j)->uncover();
							openBox(i, j);
						}
					}
				}
			}
		}
		//top right corner
		else if (indexOne == (w - 1) && indexTwo == 0) {
			for (int i = indexOne-1; i <= indexOne; i++) {
				for (int j = indexTwo; j <= indexTwo+1; j++) {
					if (i == w || j == h) { return; }
					else if (!allButtons.at(i).at(j)->checkCascade()) {
						if (allButtons.at(i).at(j)->getFlagStatus() != 1) {
							allButtons.at(i).at(j)->uncover();
							openBox(i, j);
						}
					}
				}
			}
		}
		//bottom left corner
		else if (indexOne == 0 && indexTwo == (h - 1)) {
			for (int i = indexOne; i <= indexOne+1; i++) {
				for (int j = indexTwo-1; j <= indexTwo; j++) {
					if (i == w || j == h) { return; }
					else if (!allButtons.at(i).at(j)->checkCascade()) {
						if (allButtons.at(i).at(j)->getFlagStatus() != 1)
						{
							allButtons.at(i).at(j)->uncover();
						}
						openBox(i, j);
					}
				}
			}
		}
		//bottom right corner
		else if ( indexOne == (w-1) && indexTwo == (h-1)){
			for (int i = indexOne-1; i <= indexOne; i++) {
				for (int j = indexTwo-1; j <= indexTwo; j++) {
					if (i == w || j == h) { return; }
					else if (!allButtons.at(i).at(j)->checkCascade()) {
						if (allButtons.at(i).at(j)->getFlagStatus() != 1)
						{
							allButtons.at(i).at(j)->uncover();
						}
						openBox(i, j);
					}
				}
			}
		}
		else {}
		
	}
	else {
		allButtons.at(indexOne).at(indexTwo)->printNumber();
	}
	
}

void Game::lose(int indexOne, int indexTwo) {
	status->label("Lose");
	gameStatus();
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			if (allButtons.at(i).at(j)->getBombValue() == 9) {
				allButtons.at(i).at(j)->mineTiles();
			}

			allButtons.at(i).at(j)->end();
			redraw();
		}
	}
	allButtons.at(indexOne).at(indexTwo)->drawRedMine();
	redraw();
	allButtons.at(indexOne).at(indexTwo)->resetTime();
}

bool Game::isWinner() {
	int count = 0;
	
	if (debugger) { cout << "winner checked" << endl; }
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			if (allButtons.at(i).at(j)->checkCascade()) {
				count++;
			}
		}
	}

	if (debugger) {
		cout << "opened count = " << count;
		cout << endl << "desired open count to win = " << (w*h) - numBombsOnBoard << endl;
		cout << "time status: " << firstClick << endl;
	}

	if (count == (w*h) - numBombsOnBoard) {
		status->label("Winner!");
		gameStatus();
		for (int i = 0; i < w; i++) {
			for (int j = 0; j < h; j++) {
				if (allButtons.at(i).at(j)->getBombValue() == 9) {
					allButtons.at(i).at(j)->flagTiles();
				}

				allButtons.at(i).at(j)->end();
				redraw();
			}
		}

		return true;
	}

	return false;
}



void Game::updateCounter() {
	counter->position(15 * w + 70, 10);
	count.Format("%d", numBombsOnBoard);
	counter->value(count);
	redraw();

}

bool Game::progressButton() {
	if (status->label() == "In Progress") {
		if (status->value() == 0) {
			return true;
		}
	}
	return false;
}

void Game::gameStatus() {
		status->callback(statusCallback);
	}