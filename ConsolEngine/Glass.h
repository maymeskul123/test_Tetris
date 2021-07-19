#pragma once
class TestApp;
class Figure;
#include <vector>

class Glass
{
	private:
		int width_border;
		int height_border;
		int height_data;
		int width_data;

	public:		
		int dataGlass[20][15];
		bool add_fig;
		Glass();
		~Glass();		
		void DrawGlass(TestApp*);		
		void AddFigure(Figure*);		
		int CheckBottom();
};