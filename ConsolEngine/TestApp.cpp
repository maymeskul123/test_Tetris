// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include "TestApp.h"
#include "Figure.h"
#include <ctime>

TestApp::TestApp() : Parent(32, 28)
{	
	
	/*for (int i = 0; i < 7; i++) {
		char s[100];
		sprintf(s, "Element %d rows %d columns %d\n",i, figures[i].size(), figures[i][0].size());
		OutputDebugStringA(s);
	}*/
	
	state = 0; //0 - menu 1 - game start 2 - gameover
	score = 0;
	speed = 4.0;	
	shiftPath = 0;
	turboDown = false;
}

void TestApp::InitStart() {	
	gameGlass = new Glass();	
	currentFigure = new Figure(gameGlass);	
	nextFigure = new Figure(gameGlass);
}

int TestApp::GetState()
{
	return state;
}

void TestApp::BottomEnd()
{
	if (currentFigure->y <= 0) {
		state = 2;
	}

	gameGlass->AddFigure(currentFigure);
	currentFigure->~Figure();
	score = score + gameGlass->CheckBottom();	
	currentFigure = nextFigure;

	for (int row = 5; row < 9; row++) {
		for (int col = 23; col < 28; col++) {
			SetChar(col, row, ' ');
		}
	}	
	turboDown = false;
	speed = 2.0;
	nextFigure = new Figure(gameGlass);	
}

void TestApp::KeyPressed(int btnCode)
{	
	//if (btnCode == 119 && state == 1) //w
	//	currentFigure->MoveUp();
	if (btnCode == 97 && state == 1 && !turboDown) //a
		currentFigure->MoveLeft();
	else if (btnCode == 100 && state == 1 && !turboDown) //d
		currentFigure->MoveRight();
	else if (btnCode == 32 && state == 1 && !turboDown) // |____|
		currentFigure->Rotation();
	else if (btnCode == 115 && state == 1) {
		turboDown = true;
		speed = 15.0;
		if (currentFigure->MoveDown()) {
			BottomEnd();			
			turboDown = true;
			
		}
	} //s		
		
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
			gameGlass->DrawGlass(this);
			ShowScore();
			ShowNextFigure();

			if (shiftPath > 1.0) {
				shiftPath = 0.0;
				if (currentFigure->MoveDown()) {
					BottomEnd();
				}
			}
			else {
				shiftPath += deltaTime * speed;
			}
			
			currentFigure->ShowFigure(this);
			break;
		}
	
				//GameOver
		case 2: {
			ShowGameOver();
			score = 0;
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
		
	sprintf(buf, "Start Again Press Enter");
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
	for (int row = 0; row < nextFigure->height; row++) {
		for (int col = 0; col < nextFigure->width; col++) {			
			SetChar(23 + col, 5 + row, nextFigure->figure[row * nextFigure->width + col]);
		}
	}
}