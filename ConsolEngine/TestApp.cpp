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
		mObj1Y--;
	else if (btnCode == 115) //s
		//mObj1Y++;
		myFigure->MoveDown();
	else if (btnCode == 97) //a
		myFigure->MoveLeft();
	else if (btnCode == 100) //d
		myFigure->MoveRight();
	else if (btnCode == 32) // |____|
		myFigure->Rotation();

	if (mObj1X < 0)
		mObj1X = 0;
	else if (mObj1X >= X_SIZE)
		mObj1X = X_SIZE - 1;

	if (mObj1Y < 0)
		mObj1Y = 0;
	else if (mObj1Y >=Y_SIZE)
		mObj1Y = Y_SIZE - 1;
}

void TestApp::UpdateF(float deltaTime)
{	
	myGlass->DrawGlass(this);

	if (curTime > endTime) {
		curTime = 0.0;
		if (myFigure->MoveDown()) {
			myGlass->AddFigure(myFigure);
			myFigure->~Figure();
			myFigure = new Figure();
		}
		
		//int *point = myFigure->GetExtrRight();
		//int* test = myGlass->GetDataXY(5, 19);
		/*char    buf[4096], *p = buf;
		sprintf(buf, "%d %d %d %d %X\n", test[0], test[1], test[2], test[3], &test);
		OutputDebugStringA(buf);*/
	}
	else {
		curTime = curTime + deltaTime;
	}
	myFigure->ShowFigure(this);

	//SetChar(mObj1XOld, mObj1YOld, L' ');
	//SetChar(mObj1X, mObj1Y, L'O');

	//mObj1XOld = mObj1X;
	//mObj1YOld = mObj1Y;

	////-----------------------------

	//SetChar(mObj2X, mObj2Y, L' ');
	//if (mDirection)
	//{
	//	mObj2X++;
	//	if (mObj2X == 40)
	//		mDirection = false;
	//}
	//else
	//{
	//	mObj2X--;
	//	if (mObj2X == 10)
	//		mDirection = true;
	//}
	//SetChar(mObj2X, mObj2Y, L'F');
	/*char    buf[4096], *p = buf;
	sprintf(buf, "%d\n", myFigure->num);
	OutputDebugStringA(buf);*/
}