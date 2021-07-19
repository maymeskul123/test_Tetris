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
	
	//OutputDebugStringA(buf);
	//char a[15];
	//std::memset(a, '+', sizeof(a));
	for (int col = 0; col < 22; col++) SetChar(col, 23, buf[col]);
	
	/*for (int row = 25; row < 35; row ++)
		for (int col = 9; col < 20; col++) {
			SetChar(col, row, L'!');
		}*/
}

void TestApp::BottomEnd()
{
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
}

void TestApp::UpdateF(float deltaTime)
{	
	myGlass->DrawGlass(this);

	/*char    buf[4096], *p = buf;
	sprintf(buf, "x= %d  y= %d \n", myFigure->x, myFigure->y);
	OutputDebugStringA(buf);*/
	
	if (curTime > endTime) {
		curTime = 0.0;		
		ShowScore();
		if (myFigure->MoveDown()) {
			BottomEnd();
		}
		/*char buf[4096], *p = buf;
		sprintf(buf, "x %d   y %d \n", myFigure->x, myFigure->y);
		OutputDebugStringA(buf);*/
	}
	else {
		curTime = curTime + deltaTime;
	}
	if (!myFigure->check) {
		myFigure->ShowFigure(this);
	}
}

void TestApp::ShowScore()
{
	char    buf[22], *p = buf;
	sprintf(buf, "Score=%.14d ", score);
	for (int col = 0; col < 22; col++) SetChar(col, 23, buf[col]);
}
