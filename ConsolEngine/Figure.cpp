#include "Figure.h"
#include <cstdlib>
#include <time.h>
//#include <iostream>
#include <sstream>
#include "TestApp.h"
#include <algorithm>



Figure::Figure()
{
	x = 8;
	y = 0;
	glass = new Glass();
	RandFigure();
}

void Figure::RandFigure() 
{
	int figures[128] = { 
			' ', ' ',' ',' ',
			' ', '1', ' ', ' ',
			' ', '1', '1', '1',
			' ', ' ', ' ', ' '
		,
			' ', ' ',' ',' ',
			' ', '1', '1', '1',
			' ', '1', ' ', ' ',
			' ', ' ', ' ', ' '		
		,
			' ', ' ',' ',' ',
			'1', '1', ' ', ' ',
			' ', '1', '1', ' ',
			' ', ' ', ' ', ' '
		,
			' ', ' ',' ',' ',
			' ', '1', '1', ' ',
			'1', '1', ' ', ' ',
			' ', ' ', ' ', ' '
		,
			' ', ' ',' ',' ',
			' ', '1', '1', ' ',
			' ', '1', '1', ' ',
			' ', ' ', ' ', ' '
		,
			' ', ' ',' ',' ',
			'1', '1', '1', '1',
			' ', ' ', ' ', ' ',
			' ', ' ', ' ', ' '
		,
			' ', '1',' ',' ',
			' ', '1', '1', ' ',
			' ', '1', ' ', ' ',
			' ', ' ', ' ', ' '
	};
	srand(time(0));
	num = rand() % 7;
	//num = 5;
	
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			figure[row][col] = figures[(num * 16) + row*4 + col];
		}
	}
}

void Figure::ShowFigure(TestApp * window)
{
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {					
			if (figure[row][col] == '1') {
				window->SetChar(x + col, y + row, (wchar_t)figure[row][col]);
			}
			/*else {
				window->SetChar(x + col, y + row, L'.');
			}*/
		}
	}
}

void Figure::Rotation()
{
		int copy_a[4][4];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				copy_a[3 - j][i] = figure[i][j];
			}
		}		
		swap(figure, copy_a);

		/*for (int i = 0; i < 4; i++)	{
			wstringstream wss;
			char    buf[4096], *p = buf;
			if (i == 0) {
				sprintf(buf, "After\n%c %c %c %c\n", figure[i][0], figure[i][1], figure[i][2], figure[i][3]);
			}			
			else if (i == 3) {
				sprintf(buf, "%c %c %c %c\n\n", figure[i][0], figure[i][1], figure[i][2], figure[i][3]);
			}			
			else {
				sprintf(buf, "%c %c %c %c\n", figure[i][0], figure[i][1], figure[i][2], figure[i][3]);
			}			
			OutputDebugStringA(buf);
		}*/
}

void Figure::MoveLeft()
{
	int *col_left = GetExtrLeft();
	if (x + col_left[1] > 1) {
		x--;
	}
}

bool Figure::MoveDown()
{
	y++;
	bool block;
	block = glass->Check4x4(this);
	if (block) {
		y--;
	}
	char    buf[4096], *p = buf;
	sprintf(buf, "%d\n", block);
	OutputDebugStringA(buf);
	return block;
}

void Figure::MoveRight()
{
	int *col_right = GetExtrRight();
	if (x+3 - col_right[1] < 15) {
		x++;
	}
}

int* Figure::GetExtrLeft()
{
	int arr[2];
	bool find = false;
	int col = 0;
	while (!find && col<5) {
		for (int row = 0; row < 4; row++) {
			if (figure[row][col] == '1') {
				arr[0] = row;
				arr[1] = col;
				find = true;
				break;
			}
		}
		col++;
	}
	return arr;
}

int * Figure::GetExtrRight()
{
	int arr[2];
	bool find = false;
	int col = 3;
	while (!find && col >= 0) {
		for (int row = 0; row <4 ; row++) {
			if (figure[row][col] == '1') {
				arr[0] = row;
				arr[1] = 3 - col;
				find = true;
				break;
			}
		}
		col--;
	}
	return arr;
}

int * Figure::GetExtrDown()
{
	int arr[2];
	bool find = false;
	int col = 3;
	while (!find && col >= 0) {
		for (int row = 0; row < 4; row++) {
			if (figure[row][col] == '1') {
				arr[0] = row;
				arr[1] = 3 - col;
				find = true;
				break;
			}
		}
		col--;
	}
	return arr;
}

Figure::~Figure()
{
	free(this);
}
