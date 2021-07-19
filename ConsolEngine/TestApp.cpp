// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include "TestApp.h"
#include "Figure.h"

TestApp::TestApp() : Parent(100, 80)
{
	mDirection = true;
	endTime = 2.0;
	curTime = 0.0;
	
	myFigure = new Figure();	
	myGlass = new Glass();
	myFigure->glass = myGlass;
}

void TestApp::BottomEnd()
{
	myGlass->AddFigure(myFigure);
	myFigure->~Figure();
	myGlass->CheckBottom();
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
		myFigure->Rotation();
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
	
	if (curTime > endTime && !myFigure->check) {
		curTime = 0.0;		
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