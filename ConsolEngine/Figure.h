#pragma once
class TestApp;
#include "Glass.h"

class Figure
{
private:
	int num;
	Glass *glass;

public:	
	int short_left;
	int x, y, oldX, oldY;
	int figure[4][4];
	Figure();
	void RandFigure();
	void ShowFigure(TestApp *window);
	void Rotation();
	void MoveLeft();
	bool MoveDown();
	void MoveRight();
	int* GetExtrLeft();
	int* GetExtrRight();
	int* GetExtrDown();
	//byte GetLeftMatrix
	~Figure();
};