#pragma once
class TestApp;
class Glass;

//class Figure;
#include <cstdlib>
#include <vector>

using namespace std;

class Figure
{
private:
	int num;

public:	
	bool check;
	Glass *glass;
	int x, y;
	int height, width;
	int* figure;
	vector<int> GetElements(int);
	void RandFigure();
	void ShowFigure(TestApp*);
	void Rotation();
	void MoveLeft();
	void MoveUp();
	bool MoveDown();
	void MoveRight();	
	Figure();
	~Figure();
};