#include "Game.h"
#include "Board.h"
#include "Button.h"
#include "menuButton.h"
#include <Windows.h>
#include <Fl/FL.h>
#include <Fl/FL_Window.h>
#include <Fl/FL_Button.h>
#include <Fl/FL_JPEG_Image.H>
#include <iostream>
#include <FL/Fl_Output.H>
#include <vector>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Input_.H>
#include <cstring>
#include <atlstr.h>
#include <cstringt.h>
#include <string>
using namespace std;

bool debug = false;

vector<int> i;

void inputCallback(Fl_Int_Input* widget, void*) {
	if (debug) { cout << "input callback called" << endl; }
	Fl_Int_Input* in = dynamic_cast<Fl_Int_Input*>(widget);
	i.push_back(atoi(in->value()));
	in->deactivate();
	
}

void menuCallback(Fl_Widget* widget, void*) {
	menuButton* button = dynamic_cast<menuButton*>(widget);

	if (button->getW() == 1) {
		//about page
		Fl_Window* z = new Fl_Window(700,400);
		z->make_current();
		Fl_Output* text = new Fl_Output(290, 30, 120, 30);
		text->value("About Developers");
		Fl_JPEG_Image a("image1.jpg");
		Fl_JPEG_Image b("image2.jpg");
		Fl_JPEG_Image c("image3.jpg");

		Fl_Box *box1 = new Fl_Box(25, 104, a.w(), a.h());
		box1->image(a);
		box1->label("Matthew Gaskamp");
		Fl_Box *box2 = new Fl_Box(250, 100, b.w(), b.h());
		box2->label("Noe Ortiz");
		box2->image(b);
		Fl_Box *box3 = new Fl_Box(475, 100, c.w(), c.h());
		box3->label("Uyen Vo");
		box3->image(c);

		Fl_Output* text1 = new Fl_Output(170, 325, 345, 30);
		text1->value("J. Michael Moore | CSCE 121-522 | December 4, 2015");

		z->end();
		z->show();
		Fl::run();
	}

	else {
		//custom button
		if (button->getW() == 0)
		{
			Fl_Window* f = new Fl_Window(200, 200);
			if (debug) { cout << "custom button called" << endl; }
			Fl_Output* text = new Fl_Output(10, 30, 180, 30);
			text->value("Type & press enter in order: ");
			Fl_Int_Input* width = new Fl_Int_Input(85, 60, 80, 30);
			Fl_Int_Input* height = new Fl_Int_Input(85, 90, 80, 30);
			Fl_Int_Input* mine = new Fl_Int_Input(85, 120, 80, 30);
			width->label("Width: ");
			height->label("Height: ");
			mine->label("Mine: ");
			width->maximum_size(2);
			height->maximum_size(2);
			mine->maximum_size(2);
			width->callback((Fl_Callback*)inputCallback);
			width->when(FL_WHEN_ENTER_KEY);
			height->callback((Fl_Callback*)inputCallback);
			height->when(FL_WHEN_ENTER_KEY);
			mine->callback((Fl_Callback*)inputCallback);
			mine->when(FL_WHEN_ENTER_KEY);
			f->redraw();
			f->end();
			f->show();
			
			while (i.size() != 3) {
				Fl::wait();
			}

			if (debug) {
				for (int j = 0; j < i.size(); j++) {
					cout << i.at(j) << " ";
				}
				cout << endl << endl;
			}

			button->setW(i.at(0));
			button->setH(i.at(1));
			button->setM(i.at(2));
		}
	
		int w = button->getW();
		int h = button->getH();
		int m = button->getM();

		Game* p = new Game(15 * w, 15 * h + 60);
		Board* b = new Board();
		p->setDebug(debug);
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

		if (i.size() > 0) {
			if (button->getW() == i.at(0) && button->getH() == i.at(1) && button->getM() == i.at(2)) {
				button->setW(0);
				button->setH(0);
				button->setM(0);
				i.clear();
			}
		}

		

		Fl::run();
	}
}

int main(int argc, char **argv) {
	Fl_Window* g = new Fl_Window(400,175);
	Fl_Output* text = new Fl_Output(120, 20, 180, 30);
	text->value("Please choose the difficulty");
	menuButton* easy = new menuButton(10, 65, 70, 50, 9,9, 10);
	easy->label("9x9");
	easy->align(FL_ALIGN_IMAGE_BACKDROP);
	easy->callback(menuCallback);
	menuButton* med = new menuButton(115, 65, 70, 50,16,16,40);
	med->label("16x16");
	med->align(FL_ALIGN_IMAGE_BACKDROP);
	med->callback(menuCallback);
	menuButton* hard = new menuButton(400-80-80-20, 65, 70, 50,30,16,99);
	hard->label("30x16");
	hard->align(FL_ALIGN_IMAGE_BACKDROP);
	hard->callback(menuCallback);
	menuButton* custom = new menuButton(400-80, 65, 70, 50,0,0,0);
	custom->label("Custom");
	custom->align(FL_ALIGN_IMAGE_BACKDROP);
	custom->callback(menuCallback);
	menuButton* about = new menuButton(130, 125, 140, 40,1,1,1);
	about->label("About");
	about->align(FL_ALIGN_IMAGE_BACKDROP);
	about->callback(menuCallback);

	g->end();
	g->show(argc, argv);
	return Fl::run();
}