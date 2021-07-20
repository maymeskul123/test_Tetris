// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include "TestApp.h"
#include "Figure.h"

TestApp::TestApp() : Parent(100, 80)
{	
	score = 0;
	endTime = 2.0;
	curTime = 0.0;
	
	myFigure = new Figure();	
	myGlass = new Glass();
	myFigure->glass = myGlass;
	
	char    buf[22], *p = buf;
	sprintf(buf, "Score=%.14d ", score);	
	
	for (int col = 0; col < 22; col++) SetChar(col, 23, buf[col]);	
}

void TestApp::BottomEnd()
{
	if (myFigure->y <= 0) 
		ShowGameOver();

	myGlass->AddFigure(myFigure);
	myFigure->~Figure();
	score = score + myGlass->CheckBottom();
	myFigure = new Figure();
	myFigure->glass = myGlass;
}

void TestApp::KeyPressed(int btnCode)
{	
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
	//else if (btnCode == 0x1c)
			
}

void TestApp::UpdateF(float deltaTime)
{	
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
}

void TestApp::ShowScore()
{
	char    buf[22], *p = buf;
	sprintf(buf, "Score=%.14d ", score);
	for (int col = 0; col < 22; col++) SetChar(col, 23, buf[col]);
}

void TestApp::ShowGameOver()
{
	char    buf[8], *p = buf;
	sprintf(buf, "GameOver");
	for (int col = 0; col < 8; col++) SetChar(col, 23, buf[col]);
}
