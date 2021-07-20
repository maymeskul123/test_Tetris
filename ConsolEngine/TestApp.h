// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#pragma once

#include "BaseApp.h"
#include "Figure.h"
#include "Glass.h"

class TestApp : public BaseApp
{
	typedef BaseApp Parent;

	private:
		int score;
		float curTime, endTime;
		bool mDirection;	
		int state;

	public:
		Figure *myFigure;
		Glass * myGlass;
		TestApp();
		void BottomEnd();
		virtual void KeyPressed(int btnCode);
		virtual void UpdateF(float deltaTime);
		void ShowScore();
		void ShowGameOver();
		void ShowStartMenu();
		void InitStart();
		int GetState();
};