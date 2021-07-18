#include "Figure.h"
#include "TestApp.h"
#include<vector>
#include <cstdlib>
#include <time.h>
#include <list>
#include <sstream>
#include <algorithm>

using namespace std;

Figure::Figure()
{
	x = 8;
	y = 0;
	glass = new Glass();	
	RandFigure();
}

vector<int> Figure::GetElements(int numFigure)
{	
	vector<vector<int>> figures = {
	
		{'1', ' ', ' ',
		'1', '1', '1'}
		,
		{ '1', '1', '1',
		'1', ' ', ' ' }
		,
		{'1', '1', ' ',
		' ', '1', '1'
		},
		{' ', '1', '1',
		'1', '1', ' '
		},
		{' ', '1',' ',
		'1', '1', '1'
		},
		{'1', '1',
		'1', '1'
		},
		{'1', '1', '1', '1'}
	};
	
	//return vector<char>();
	return figures[numFigure];
}

void Figure::RandFigure()
{	
	srand(time(0));
	num = rand() % 7;
	num = 6;

	char    buf[4096], *p = buf;
	sprintf(buf, "num= %d \n", num);
	OutputDebugStringA(buf);
	
	if (num != 6 && num != 5) {
		height = 2;
		width = 3;
		figure = new int[6];
	}
	else if (num == 5){
		height = 2;
		width = 2;
		figure = new int[4];
	}
	else if (num == 6) {
		height = 1;
		width = 4;
		figure = new int[4];
	}
	
	vector<int> b(GetElements(num));

	int index = 0;
	for (int n : b) {
		figure[index] = n;
		index++;
		
		/*char    buf[4096], *p = buf;
		sprintf(buf, "element from vector= %d \n", n);
		OutputDebugStringA(buf);*/
	}	
}

void Figure::ShowFigure(TestApp * window)
{
	/*for (int i = 0; i < height * width; i++) {
		char    buf[4096], *p = buf;
		sprintf(buf, "\n element %d from figure= %d \n", i, figure[i]);
		OutputDebugStringA(buf);
	}*/
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (figure[row * width + col] == '1') {
				window->SetChar(x + col, y + row, figure[row * width + col]);
			}
			else {
				window->SetChar(x + col + 1, y + row + 1, 'o');
			}
		}
	}
}

void Figure::Rotation()
{	
	int* dst = new int [height * width];
	
	int i, j;
	for (i = 0; i < width; i++)
		for (j = 0; j < height; j++)
			dst[i * height + j] = figure[j *width + width - i - 1];
	
	/*for (j = 0; j < height; j++) {
		for (i = 0; i < width; i++) {
			char    buf[4096], *p = buf;
			sprintf(buf, "old %i %i %i \t", j, i, figure[j*width + i]);
			OutputDebugStringA(buf);
		}		
	}
	
	for (j = 0; j < width; j++) {
		for (i = 0; i < height; i++) {
			char    buf[4096], *p = buf;
			sprintf(buf, "new %i %i %i \t", j, i, dst[j * height + i]);
			OutputDebugStringA(buf);
		}		
	}*/
	swap(figure, dst);
	swap(height, width);	
}

void Figure::MoveLeft()
{			
	if (x > 0) {
		x--;
	}	
}

void Figure::MoveUp()
{
	y--;
}

bool Figure::MoveDown()
{
	y++;
	bool block;
	block = glass->CheckBlock(this);
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
	if (x + width < 15) {
		x++;
	}
}

Figure::~Figure()
{
	free(this);
}
