// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include "TestApp.h"
#include "Figure.h"

TestApp::TestApp() : Parent(100, 80)
{
	mDirection = true;
	mObj1XOld = mObj1X = 10;
	mObj1YOld = mObj1Y = 10;
	mObj2X = 10;
	mObj2Y = 12;

	endTime = 1.0;
	curTime = 0.0;
	
	myFigure = new Figure();
	myGlass = new Glass();
	//myFigure->NewFigure();
}

void TestApp::KeyPressed(int btnCode)
{
	if (btnCode == 119) //w
		//mObj1Y--;
		myFigure->MoveUp();
	else if (btnCode == 115) //s
		//mObj1Y++;
		myFigure->MoveDown();
	else if (btnCode == 97) //a
		myFigure->MoveLeft();
	else if (btnCode == 100) //d
		myFigure->MoveRight();
	else if (btnCode == 32) // |____|
		myFigure->Rotation();	
}

void TestApp::UpdateF(float deltaTime)
{	
	myGlass->DrawGlass(this);

	/*char    buf[4096], *p = buf;
	sprintf(buf, "x= %d  y= %d \n", myFigure->x, myFigure->y);
	OutputDebugStringA(buf);*/
	
	if (curTime > endTime && !myFigure->check) {
		curTime = 0.0;		
		if (myFigure->MoveDown()) {
			myGlass->AddFigure(myFigure);
			myFigure->~Figure();
			myFigure = new Figure();
		}
		char    buf[4096], *p = buf;
		sprintf(buf, "x %d   y %d \n", myFigure->x, myFigure->y);
		OutputDebugStringA(buf);
	}
	else {
		curTime = curTime + deltaTime;
	}
	myFigure->ShowFigure(this);
}