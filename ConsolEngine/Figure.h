#pragma once
//class Figure;
#include <cstdlib>
#include <vector>

class TestApp;
class Glass;

using namespace std;

class Figure
{
private:
	int num;
	bool direction;

public:		
	Glass *glass;
	int x, y;	
	int height, width;
	int* figure;
	vector<int> GetElements(int);
	void RandFigure();
	void ShowFigure(TestApp*);
	void Rotation(bool);
	void MoveLeft();
	void MoveUp();
	bool MoveDown();
	void MoveRight();	
	Figure();
	~Figure();
};