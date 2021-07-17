#include "Figure.h"
#include <cstdlib>
#include <sstream>
#include "TestApp.h"
#include <algorithm>



Figure::Figure()
{
	x = 8;
	y = 1;
	glass = new Glass();
}

void Figure::NewFigure() 
{
	int figures[128] = { ' ', ' ',' ',' ',
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
	//srand(rand() % 100);
	num = rand() % 7;	
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			figure[i][j] = figures[(num * 16) + i*4 + j];
		}
	}
}

void Figure::ShowFigure(TestApp * window)
{
	for (int l = 0; l < 4; l++) {
		for (int col = 0; col < 4; col++) {					
			if (figure[col][l] == '1') {
				window->SetChar(x + col, y + l, (wchar_t)figure[col][l]);
			}			
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

		for (int i = 0; i < 4; i++)	{
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
		}
}

void Figure::MoveLeft()
{
	if (GetExtrLeft() + x -1 != glass->GetDataXY() =='1'
	x--;
}

void Figure::MoveDown()
{
	y++;
}

void Figure::MoveRight()
{
	x++;
}

int* Figure::GetExtrLeft()
{
	int arr[2];
	int (*arr)[2] = &arr;
	for (int col = 0; col < 4; col++)
		for (int l = 0; l < 4; l++) {
		 {
			if (figure[col][l] == '1') {				
				arr[0] = col;
				arr[1] = l;
				break;
				break;
			}
		}
	}
	return arr;
}

Figure::~Figure()
{
	free(this);
}
