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
	//for (int i = 0; i < 14; i++) {
	//	dataGlass[10][0] = '1';
	//	/*if (i % 2) dataGlass[15][i] = '1';
	//	if (i % 2) dataGlass[18][i] = '1';*/		
	//	//dataGlass[15 + i][5] = '1';
	//}
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

int Glass::CheckBottom()
{	
	int score = 0;
	int buff[20][15];
	int* src;
	int* dst;
	int lines_del = 0;
	int index = height_data - 1;
	
		for (int row = height_data - 1; row >= 0; row--)
		{
			bool save_line = true;
			int fill_str[15];
			std::memset(fill_str, '1', 15 * sizeof(int));
			save_line = (dataGlass[row] == &fill_str[15]);
			for (int n : dataGlass[row]) {
				save_line = (save_line && (n == '1'));
				if (!save_line)break;
			}
		
			if (save_line) {
				dst = &buff[index][0];
				src = &dataGlass[row][0];
				std::memmove(dst, src, 15 * sizeof(int));
				index--;
				score = score + 100;
			}
		}
		
		/*char    buf[4096], *p = buf;
		sprintf(buf, "index = %d  \n", index);
		OutputDebugStringA(buf);*/
		
		int a[15];
		std::memset(a, ' ', sizeof(a));
		
		while (index >= 0) {
			//std::memset(Buff[index], ' ', 15 * sizeof(int));
			dst = &buff[index][0];
			src = &a[0];
			std::memmove(dst, src, 15 * sizeof(int));
			index--;
		}
		swap(buff, dataGlass);
	
	return score;
}

Glass::~Glass()
{
	free(this);
}
