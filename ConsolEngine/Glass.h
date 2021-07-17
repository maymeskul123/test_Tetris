#pragma once
class TestApp;
class Figure;

class Glass
{
	private:
		int width;
		int height;
		char dataGlass[22][17];

	public:		
		Glass();
		~Glass();
		void DrawGlass(TestApp * window);
		char GetDataXY(int col, int line);
		void AddFigure(Figure *fig);
};