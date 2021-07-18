#include "Glass.h"
#include "TestApp.h"
#include "Figure.h"

Glass::Glass()
{
	height_border = 22;
	width_border = 17;
	height_data = 20;
	width_data = 15;
	add_fig = false;
	for (int row = 0; row < height_data; row++) {
		for (int col = 0; col < width_data+1; col++) {
			dataGlass[row][col] = ' ';
		}
	}
	/*for (int i = 1; i < 5; i++) {
		dataGlass[15 + i][0] = '1';
		dataGlass[15 + i][5] = '1';
	}
	dataGlass[16][1] = '1';*/
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
	//add_fig = true;
	for (int row = 0; row < fig->height; row++) {
		for (int col = 0; col < fig->width; col++) {
			if (fig->figure[row * fig->width + col] == '1') {
				dataGlass[fig->y + row][fig->x + col] = '1';
			}
		}
	}
	//add_fig = false;
}

bool Glass::CheckBlock(Figure * fig)
{
	fig->check = true;
	bool blocked = false;
	for (int row = 0; row < fig->height; row++) {
		for (int col = 0; col < fig->width; col++) {
			char    buf[4096], *p = buf;
			sprintf(buf, "dataGlass= %d  fig_y= %d fig_x= %d \n", dataGlass[fig->y + row][fig->x + col], fig->y + row, fig->x+col);
			OutputDebugStringA(buf);

			if (((fig->figure[row * fig->width + col] == '1') && (dataGlass[fig->y + row][fig->x + col] == '1')) || ((fig->figure[row * fig->width + col] == '1') && (fig->y + row >19))) {
				blocked = true;
			}
		}
	}
	fig->check = false;
	return blocked;
}

Glass::~Glass()
{
	free(this);
}