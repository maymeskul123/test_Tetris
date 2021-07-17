#include "Glass.h"
#include "TestApp.h"
#include "Figure.h"

Glass::Glass()
{
	height_border = 22;
	width_border = 17;
	height_data = 20;
	width_data = 15;
	for (int row = 0; row < height_data; row++) {
		for (int col = 0; col < width_data; col++) {
			dataGlass[row][col] = ' ';
		}
	}
	for (int i = 0; i < 4; i++) {
		dataGlass[19][5 + i] = '1';
	}
}

void Glass::DrawGlass(TestApp * window)
{
	for (int l = 0; l < height_border; l++) {
		for (int c = 0; c < width_border; c++) {						
			if ((c == 0) || (c == 16) || (l == 0) || (l == 21))
			{
				window->SetChar(c, l, L'#');
			}				
		}
	}

	for (int row = 0; row < height_data; row++) {
		for (int col = 0; col < width_data; col++)	{
			window->SetChar(col+1, row+1, (wchar_t)dataGlass[row][col]);
		}
	}
}

int * Glass::GetDataXY(int x, int y)
{	
	int* mass = &dataGlass[y][x];
	return mass;
}

void Glass::AddFigure(Figure *fig)
{
	for (int l = 0; l < 4; l++) {
		for (int col = 0; col < 4; col++) {
			if (fig->figure[l][col] == '1') {
				dataGlass[fig->y + l - 1][fig->x + col - 1] = '1';
			}		
		}
	}
}

bool Glass::Check4x4(Figure * fig)
{
	bool blocked = false;	
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			if (((fig->figure[row][col] == '1') && (dataGlass[fig->y + row][fig->x + col] == 1)) || ((fig->figure[row][col] == '1') && (fig->y + row >19))) {
				blocked = true;
			}
		}
	}
	return blocked;
}

Glass::~Glass()
{
	free(this);
}