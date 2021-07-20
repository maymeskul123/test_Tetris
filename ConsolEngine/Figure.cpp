#include "Figure.h"
#include "TestApp.h"
#include "Glass.h"
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
	
	return figures[numFigure];
}

void Figure::RandFigure()
{	
	srand(time(0));
	num = rand() % 7;
	//num = 1;

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
	}

	srand(time(0));
	direction = rand() % 2;
	if (direction) Rotation(false);
}

void Figure::ShowFigure(TestApp * window)
{	
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (figure[row * width + col] == '1') {
				window->SetChar(x + col+1, y + row+1, figure[row * width + col]);
			}
			/*else {
				window->SetChar(x + col , y + row, '0');
			}*/
		}
	}
}

void Figure::Rotation(bool check)
{	
	int* dst = new int [height * width];
	
	int i, j;
	for (i = 0; i < width; i++)
		for (j = 0; j < height; j++)
			dst[i * height + j] = figure[j *width + width - i - 1];
	
	
	swap(figure, dst);
	swap(height, width);
	direction = direction ^ true;
	if (check) {
		bool imposs = false;
		for (int row = 0; row < height; row++) {
			for (int col = 0; col < width; col++) {
				imposs = ((figure[row * width + col] == '1') && (glass->dataGlass[y + row][x + col] == '1')) || ((x + width > 15) || (x < 0) || (y > 20));
			}
		}
		if (imposs) {
			swap(figure, dst);
			swap(height, width);
			direction = direction ^ true;
		}
	}	
}

void Figure::MoveLeft()
{			
	if (x > 0) {
		bool block = false;
		for (int row = 0; row < height; row++) {
			block = block || ((figure[row *width] == '1') && (glass->dataGlass[y + row][x - 1] == '1'));

			char    buf[4096], *p = buf;
			sprintf(buf, " block %d\n", block);
			OutputDebugStringA(buf);
		}
		if(!block)x--;
	}
}

void Figure::MoveRight()
{
	if (x + width < 15) {	
		bool block = false;
		for (int row = 0; row < height; row++) {
			block = block || ((figure[row *width + width - 1] == '1') && (glass->dataGlass[y + row][x + width] == '1'));
		
			char    buf[4096], *p = buf;
			sprintf(buf, " block %d\n", block);
			OutputDebugStringA(buf);
		}
		if (!block)x++;	
	}
}

void Figure::MoveUp()
{
	y--;	
}

bool Figure::MoveDown()
{
	bool block = false;
	if ((y + height) < 20) {
		for (int row = 0; row < height; row++) {
			for (int col = 0; col < width; col++) {
				block = block || ((figure[row *width + col] == '1') && (glass->dataGlass[y + row + 1][x + col] == '1'));

				char    buf[4096], *p = buf;
				sprintf(buf, " block %d\n", block);
				OutputDebugStringA(buf);
			}
		}
		if (!block)y++;
	}
	else block = true;
	return block;
}

Figure::~Figure()
{
	free(this);
}
