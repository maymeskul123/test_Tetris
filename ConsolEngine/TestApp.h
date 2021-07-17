// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#pragma once

#include "BaseApp.h"
#include "Figure.h"
#include "Glass.h"

class TestApp : public BaseApp
{
	typedef BaseApp Parent;

	private:
		int mObj1XOld;
		int mObj1YOld;
		int mObj1X;
		int mObj1Y;

		int mObj2X;
		int mObj2Y;
		float curTime, endTime;

		bool mDirection;
		
		

	public:
		Figure *myFigure;
		Glass * myGlass;
		TestApp();
		virtual void KeyPressed(int btnCode);
		virtual void UpdateF(float deltaTime);
};