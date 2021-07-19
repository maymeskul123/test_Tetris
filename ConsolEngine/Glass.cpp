#include "Glass.h"
#include "TestApp.h"
#include "Figure.h"
#include <vector>

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
	for (int i = 0; i < 14; i++) {
		dataGlass[10][0] = '1';
		/*if (i % 2) dataGlass[15][i] = '1';
		if (i % 2) dataGlass[18][i] = '1';*/		
		//dataGlass[15 + i][5] = '1';
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
			if (dataGlass[row][col] == '1') {
				window->SetChar(col + 1, row + 1, '1');
			}
			else {
				window->SetChar(col + 1, row + 1, ' ');
			}
			
		}
	}
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
	bool blocked = false;
	bool equal_fig_1 = false;
	bool equal_data_1 = false;
	//for (int row = 0; row < fig->height; row++) {
	//	for (int col = 0; col < fig->width; col++) {
	//			/*char    buf[4096], *p = buf;
	//			sprintf(buf, "dataGlass= %d  fig_y= %d fig_x= %d \n", dataGlass[fig->y + row][fig->x + col], fig->y + row, fig->x+col);
	//			OutputDebugStringA(buf);*/

	//		equal_fig_1 = (fig->figure[row * fig->width + col] == '1');
	//		equal_data_1 = (dataGlass[fig->y_temp + row][fig->x_temp + col] == '1');

	//		//if ((equal_fig_1) && (fig->y_temp + row > 19) || (equal_fig_1)&&(fig->x_temp + col > 14))blocked = true;
	//		//if ((equal_fig_1) && (fig->y_temp < 0) || (equal_fig_1) && (fig->x_temp < 0))blocked = true;
	//		if (equal_fig_1 && equal_data_1) blocked = true;
	//	}
	//}
	return blocked;
}

bool Glass::CheckBottom()
{	
	//vector<int> lines;
	int Buff[20][15];
	int* src;
	int* dst;
	int lines_del = 0;
	int index = height_data - 1;
	
		for (int row = height_data - 1; row >= 0; row--)
		{
			bool line_compl = true;
			for (int n : dataGlass[row]) {
				line_compl = (line_compl && (n == '1'));
				if (!line_compl)break;
			}
		
			if (!line_compl) {
				dst = &Buff[index][0];
				src = &dataGlass[row][0];
				std::memmove(dst, src, 15 * sizeof(int));
				index--;
			}
		}
		
		char    buf[4096], *p = buf;
		sprintf(buf, "index = %d  \n", index);
		OutputDebugStringA(buf);
		
		int a[15];
		std::memset(a, ' ', sizeof(a));
		
		while (index >= 0) {
			//std::memset(Buff[index], ' ', 15 * sizeof(int));
			dst = &Buff[index][0];
			src = &a[0];
			std::memmove(dst, src, 15 * sizeof(int));
			index--;
		}
		swap(Buff, dataGlass);
	
	return false;
}

Glass::~Glass()
{
	free(this);
}
