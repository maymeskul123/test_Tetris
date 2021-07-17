#include "Glass.h"
#include "TestApp.h"
#include "Figure.h"

Glass::Glass()
{
	height = 22;
	width = 17;
	for (int l = 0; l < height; l++) {
		for (int c = 0; c < width; c++) {
			dataGlass[l][c] = L' ';
		}
	}
}

void Glass::DrawGlass(TestApp * window)
{
	for (int l = 0; l < height; l++) {
		for (int c = 0; c < width; c++) {						
			if ((c == 0) || (c == 16) || (l == 0) || (l == 21))
			{
				window->SetChar(c, l, L'#');
			}				
		}
	}

	for (int l = 1; l < height - 1; l++) {
		for (int c = 1; c < width - 1; c++)	{
			window->SetChar(c, l, (wchar_t)dataGlass[l][c]);
		}
	}
}

char Glass::GetDataXY(int col, int line)
{	
	return dataGlass[col][line];
}

void Glass::AddFigure(Figure *fig)
{
	for (int l = 0; l < 4; l++) {
		for (int col = 0; col < 4; col++) {
			if (fig->figure[l][col] == '1') {
				dataGlass[l][col] = '1';
			}		
		}
	}
}

Glass::~Glass()
{
	free(this);
}