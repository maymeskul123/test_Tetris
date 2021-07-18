#pragma once
class TestApp;
class Figure;

class Glass
{
	private:
		int width_border;
		int height_border;
		int height_data;
		int width_data;
		
		int dataGlass[20][15];

	public:		
		Glass();
		~Glass();
		void DrawGlass(TestApp*);
		int* GetDataXY(int col, int line);
		void AddFigure(Figure*);
		bool CheckBlock(Figure*);
};