// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#pragma once

#include "BaseApp.h"
#include "Figure.h"
#include "Glass.h"

struct Figura {
	int num;
	bool direction;
};

class TestApp : public BaseApp
{
	typedef BaseApp Parent;

	private:
		int score;
		float curTime, endTime;		
		int state;
		Figura currentFigure, nextFigure;

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
		void ShowNextFigure();
		void InitStart();
		int GetState();
};