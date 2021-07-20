// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include "TestApp.h"
#include "Figure.h"

TestApp::TestApp() : Parent(100, 80)
{	
	state = 0; //0 - menu 1 - game start 2 - gameover
	score = 0;
	endTime = 2.0;
	curTime = 0.0;	
}

void TestApp::InitStart() {
	myFigure = new Figure();
	myGlass = new Glass();
	myFigure->glass = myGlass;
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
	myFigure = new Figure();
	myFigure->glass = myGlass;
}

void TestApp::KeyPressed(int btnCode)
{	
	if (state = 1) {
		if (btnCode == 119) //w		
			myFigure->MoveUp();
		else if (btnCode == 97) //a
			myFigure->MoveLeft();
		else if (btnCode == 100) //d
			myFigure->MoveRight();
		else if (btnCode == 32) // |____|
			myFigure->Rotation(true);
		else if (btnCode == 115) //s		
			if (myFigure->MoveDown()) {
				BottomEnd();
			}
	}
	
	if (btnCode == 0x1c) {
		if (state == 0 || state == 2) {			
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
	char    buf[22], *p = buf;
	sprintf(buf, "Score=%.14d ", score);
	for (int col = 0; col < 22; col++) SetChar(col, 23, buf[col]);
}

void TestApp::ShowGameOver()

{
	char    buf[15], *p = buf;
	sprintf(buf, "GameOver");
	for (int col = 0; col < 15; col++) SetChar(col, 23, buf[col]);
}

void TestApp::ShowStartMenu()
{
	char    buf[30], *p = buf;
	sprintf(buf, "For START Press ENTER");
	for (int col = 0; col < 30; col++) SetChar(col, 15, buf[col]);
}