#pragma once
class TestApp;
#include "Glass.h"

class Figure
{
private:
	int num;
	Glass *glass;

public:	
	
	int x, y, oldX, oldY;
	int figure[4][4];
	Figure();
	void NewFigure();
	void ShowFigure(TestApp *window);
	void Rotation();
	void MoveLeft();
	void MoveDown();
	void MoveRight();
	int* GetExtrLeft();
	~Figure();
};
