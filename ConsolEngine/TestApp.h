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
		float shiftPath, speed;
		int state;
		bool turboDown;

	public:
		Figure *currentFigure, *nextFigure;
		Glass * gameGlass;
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