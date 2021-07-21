// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include "TestApp.h"
#include "Figure.h"
#include <time.h>

TestApp::TestApp() : Parent(32, 28)
{	
	state = 0; //0 - menu 1 - game start 2 - gameover
	score = 0;
	endTime = 2.0;
	curTime = 0.0;	
}

void TestApp::InitStart() {
	srand(time(0));
	currentFigure.num = rand() % 7;
	srand(time(0));
	currentFigure.direction = rand() % 2; //true - vertical (is Rotation)
	srand(time(0));
	nextFigure.num = rand() % 7;
	srand(time(0));
	nextFigure.direction = rand() % 2;	
	myGlass = new Glass();	
	myFigure = new Figure(currentFigure.num, currentFigure.direction, myGlass);
}

int TestApp::GetState()
{
	return state;
}

void TestApp::BottomEnd()
{
	if (myFigure->y <= 0) {
		state = 2;
	}

	myGlass->AddFigure(myFigure);
	myFigure->~Figure();
	score = score + myGlass->CheckBottom();
	
	myFigure = new Figure(nextFigure.num, nextFigure.direction, myGlass);
	currentFigure = nextFigure;

	srand(time(0));
	nextFigure.num = rand() % 7;
	srand(time(0));
	nextFigure.direction = rand() % 2;	
}

void TestApp::KeyPressed(int btnCode)
{	
	if (btnCode == 119 && state == 1) //w		
		myFigure->MoveUp();
	else if (btnCode == 97 && state == 1) //a
		myFigure->MoveLeft();
	else if (btnCode == 100 && state == 1) //d
		myFigure->MoveRight();
	else if (btnCode == 32 && state == 1) // |____|
		myFigure->Rotation();
	else if (btnCode == 115 && state == 1) //s		
		if (myFigure->MoveDown()) {
			BottomEnd();
		}
		
	if (btnCode == 13) {
		if (state == 0 || state == 2) {			
			for (int col = 0; col < 30; col++) SetChar(col, 15, ' ');
			InitStart();
			state = 1;
		}		
	}
}

void TestApp::UpdateF(float deltaTime)
{	
	switch (state) {
	
		//Menu
	case 0: {
		ShowStartMenu();
		break;
	}
		//Start
	case 1: {
		myGlass->DrawGlass(this);
		ShowScore();
		if (curTime > endTime) {
			curTime = 0.0;
			if (myFigure->MoveDown()) {
				BottomEnd();
			}
		}
		else {
			curTime = curTime + deltaTime;
		}
		myFigure->ShowFigure(this);
		break;
	}
	
			//GameOver
	case 2: {
		ShowGameOver();
		break;
	}
	}
	
}

void TestApp::ShowScore()
{
	for (int col = 0; col < 30; col++) SetChar(col, 23, ' ');
	for (int col = 0; col < 30; col++) SetChar(col, 24, ' ');
	char    buf[19], *p = buf;
	sprintf(buf, "Score=%.11d ", score);
	for (int col = 0; col < 19; col++) SetChar(col, 23, buf[col]);
}

void TestApp::ShowGameOver()

{	
	char    buf[24], *p = buf;
	sprintf(buf, "GameOver               ");
	for (int col = 0; col < 23; col++) SetChar(col, 23, buf[col]);
		
	sprintf(buf, "Again Start Press Enter");
	for (int col = 0; col < 23; col++) SetChar(col, 24, buf[col]);
}

void TestApp::ShowStartMenu()
{	
	char    buf[22], *p = buf;
	sprintf(buf, "For START Press ENTER");
	for (int col = 0; col < 21; col++) SetChar(col, 15, buf[col]);
}

void TestApp::ShowNextFigure()
{

}