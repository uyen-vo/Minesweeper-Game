#include "Button.h"
#include "Game.h"
#include <Windows.h>
#include <FL/Fl.h>
#include <FL/Fl_Window.h>
#include <FL/Fl_Box.H>
#include <FL/Fl_JPEG_Image.h>
#include <FL/Fl_Button.h>
#include <FL/Fl_Output.H>
#include <string>
#include <iostream>
#include <FL/names.h>

using namespace std;

static int timeCount = 0;

void timerCallback(void* u) {
	string sval = to_string(timeCount);
	((Fl_Output*)u)->value(sval.c_str());
	((Fl_Output*)u)->redraw();
	timeCount++;
	Fl::repeat_timeout(1.0, timerCallback, u);
}

int Button::getBombValue() {
	return bombValue;
}

void Button::setBombValue(int value) {
	bombValue = value;
}

void Button::setIndexOne(int one) {
	indexOne = one;

}

void Button::setIndexTwo(int two) {
	indexTwo = two;
}

int Button::handle(int event) {
	switch (event) {
	case FL_PUSH:
	{
		if (Fl::event_button1() != 0 && Fl::event_button3() != 0) {
			if (open && bombValue != 0 && bombValue != 9) {
				if (game->getDebug()) {
					cout << "//simul click//" << endl;
				}
				game->clearAdjacent(indexOne, indexTwo, bombValue);
				
			}
		}
		break;
	}
	case FL_RELEASE:
		if (ender == false) {
			//left click
			if (!game->first()) {
				if (game->getDebug()) {
					cout << "//timercallback//" << endl;
				}
				timerCallback(timer);
			}
			game->firstMouseClick();
			
			if (Fl::event_button() == 1) {
				if (game->getDebug() == true) {
					cout << endl << "left click" << endl;
					cout << indexOne << " " << indexTwo << endl;
				}

				if (flagStatus == 1) {
					return Fl_Widget::handle(event);
				}
				if (bombValue == 9) {
					image(losing);
					redraw();
					redMine();

				}
				else if (bombValue == 1) {
					if (game->getDebug() == true) {
						cout << "clue value: " << bombValue << endl;
					}
					image(emptyUncovered);
					label("1");
					labelfont(FL_BOLD);
					align(FL_ALIGN_IMAGE_BACKDROP);
					labelcolor(FL_BLUE);
					redraw_label();
				}
				else if (bombValue == 2) {
					if (game->getDebug() == true) {
						cout << "clue value: " << bombValue << endl;
					}
					image(emptyUncovered);
					label("2");
					labelfont(FL_BOLD);
					align(FL_ALIGN_IMAGE_BACKDROP);
					labelcolor(FL_DARK_GREEN);
					redraw_label();
				}
				else if (bombValue == 3) {
					if (game->getDebug() == true) {
						cout << "clue value: " << bombValue << endl;
					}
					image(emptyUncovered);
					label("3");
					labelfont(FL_BOLD);
					align(FL_ALIGN_IMAGE_BACKDROP);
					labelcolor(FL_RED);
					redraw_label();
				}
				else if (bombValue == 4) {
					if (game->getDebug() == true) {
						cout << "clue value: " << bombValue << endl;
					}
					image(emptyUncovered);
					label("4");
					labelfont(FL_BOLD);
					align(FL_ALIGN_IMAGE_BACKDROP);
					labelcolor(FL_BLUE);
					redraw_label();
				}
				else if (bombValue == 5) {
					if (game->getDebug() == true) {
						cout << "clue value: " << bombValue << endl;
					}
					image(emptyUncovered);
					label("5");
					labelfont(FL_BOLD);
					align(FL_ALIGN_IMAGE_BACKDROP);
					labelcolor(FL_MAGENTA);
					redraw_label();
				}
				else if (bombValue == 7) {
					if (game->getDebug() == true) {
						cout << "clue value: " << bombValue << endl;
					}
					image(emptyUncovered);
					label("7");
					labelfont(FL_BOLD);
					align(FL_ALIGN_IMAGE_BACKDROP);
					labelcolor(FL_BLACK);
					redraw_label();
				}
				else if (bombValue == 6) {
					if (game->getDebug() == true) {
						cout << "clue value: " << bombValue << endl;
					}
					image(emptyUncovered);
					label("6");
					labelfont(FL_BOLD);
					align(FL_ALIGN_IMAGE_BACKDROP);
					labelcolor(FL_CYAN);
					redraw_label();
				}
				else if (bombValue == 8) {
					if (game->getDebug() == true) {
						cout << "clue value: " << bombValue << endl;
					}
					image(emptyUncovered);
					label("8");
					labelfont(FL_BOLD);
					align(FL_ALIGN_IMAGE_BACKDROP);
					labelcolor(FL_GRAY0);
					redraw_label();
				}
				else if (bombValue == 0) { 
					game->openBox(indexOne, indexTwo);
					image(emptyUncovered);
					if (game->getDebug() == true) {
						cout << "clue value: " << bombValue << endl;
					}
					deactivate();
				}
				close();
				openTile();
				if (game->isWinner()) {
					game->gameStatus();
					resetTime();
				}
			}
			
			//right click
			if (Fl::event_button() == 3) {
				if (!game->first()) {
					if (game->getDebug()) { cout << "//timercallback//" << endl; }

					timerCallback(timer);
				}
				game->firstMouseClick();
				if (closed == false) {
					if (game->getDebug() == true) {
						cout << endl << "right click" << endl;
						cout << indexOne << " " << indexTwo << endl;
					}
					if (flagStatus == 1) {
						game->increaseMineCount();
						game->updateCounter();
						image(question);
						redraw();
						flagStatus = 2;
					
					}

					else if (flagStatus == 2) {
						image(covered);
						redraw();
						flagStatus = 0;
						
					}
					else {
						image(flagged);
						flagStatus = 1;
						game->decreaseMineCount();
						game->updateCounter();

						redraw();	
					}
				}
			}
		}
		return 1;
	default:
		return Fl_Widget::handle(event);
	}
	return 1;
}


void Button::flagTiles() {
	image(flagged);
	game->decreaseMineCount();
	game->updateCounter();
}

int Button::getFlagStatus() {
	return flagStatus;
}

void Button::uncover() { 
	
	if (bombValue == 0) {
		image(emptyUncovered); close();
		openTile();
	}
	else if(bombValue!=9){
		printNumber();
	}
	else{
		if (game->getDebug()) {
			cout << "simul lose" << endl;
		}
		redMine();
	}
}
void Button::printNumber() {
	openTile();
	if (bombValue == 1) {
		image(emptyUncovered);
		label("1");
		labelfont(FL_BOLD);
		align(FL_ALIGN_IMAGE_BACKDROP);
		labelcolor(FL_BLUE);
		redraw_label();
	}
	else if (bombValue == 2) {
		image(emptyUncovered);
		label("2");
		labelfont(FL_BOLD);
		align(FL_ALIGN_IMAGE_BACKDROP);
		labelcolor(FL_DARK_GREEN);
		redraw_label();
	}
	else if (bombValue == 3) {
		image(emptyUncovered);
		label("3");
		labelfont(FL_BOLD);
		align(FL_ALIGN_IMAGE_BACKDROP);
		labelcolor(FL_RED);
		redraw_label();
	}
	else if (bombValue == 4) {
		image(emptyUncovered);
		label("4");
		labelfont(FL_BOLD);
		align(FL_ALIGN_IMAGE_BACKDROP);
		labelcolor(FL_BLUE);
		redraw_label();
	}
	else if (bombValue == 5) {
		image(emptyUncovered);
		label("5");
		labelfont(FL_BOLD);
		align(FL_ALIGN_IMAGE_BACKDROP);
		labelcolor(FL_MAGENTA);
		redraw_label();
	}
	else if (bombValue == 7) {
		image(emptyUncovered);
		label("7");
		labelfont(FL_BOLD);
		align(FL_ALIGN_IMAGE_BACKDROP);
		labelcolor(FL_BLACK);
		redraw_label();
	}
	else if (bombValue == 6) {
		image(emptyUncovered);
		label("6");
		labelfont(FL_BOLD);
		align(FL_ALIGN_IMAGE_BACKDROP);
		labelcolor(FL_CYAN);
		redraw_label();
	}
	else if (bombValue == 8) {
		image(emptyUncovered);
		label("8");
		labelfont(FL_BOLD);
		align(FL_ALIGN_IMAGE_BACKDROP);
		labelcolor(FL_GRAY0);
		redraw_label();
	}
	else {
		image(emptyUncovered);
	}
}

bool Button::checkCascade() {
	return open;
}

void Button::closedTiles() {
	image(covered);
}

void Button::mineTiles() {
	image(mine);
}

void Button::drawRedMine() {
	image(losing);
}

void Button::openTile() {
	open = true;
}
void Button::close() {
	closed = true;
}

void Button::redMine() {
	if (game->getDebug() == true) {
		cout << "red mine found" << endl;
		cout << "new game" << endl;
	}
	game->lose(indexOne, indexTwo);
}

int Button::clickType() {
	return Fl::event_button();
}

void Button::end() {
	Fl::remove_timeout(timerCallback, timer);
	string s = to_string(timeCount);
	timer->value(s.c_str());
	timer->redraw();
	ender = true;
}

void Button::resetTime() {
	Fl::remove_timeout(timerCallback, timer);
	timer = new Fl_Output(109, 15, 30, 30); 
	timeCount = 0;
}

bool Button::isClosed() {
	return closed;
}

int Button::getIndexOne() { return indexOne; }
int Button::getIndexTwo() { return indexTwo; }

bool Button::isNonBomb() { return nonBomb; }
void Button::setNonBomb(bool b) { nonBomb = b; }
