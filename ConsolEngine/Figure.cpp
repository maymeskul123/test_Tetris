#include "Figure.h"
#include "TestApp.h"
#include "Glass.h"
#include <ctime>
#include<vector>
#include <cstdlib>
#include <list>
#include <sstream>
#include <algorithm>
#include<random>

using namespace std;

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

Figure::Figure(Glass* to_glass)
{
	glass = to_glass;
	x = 8;	
	y = 0;
	RandFigure();
}

vector<int> Figure::GetElements(int numFigure)
{	
	return figures[numFigure];
}

void Figure::RandFigure()
{	
	/*srand(time(NULL));*/
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 6); // distribution in range [0, 6]

	std::cout << dist6(rng) << std::endl;
	char    buf[4096], *p = buf;
	sprintf(buf, "Number %d\n", dist6(rng));
	OutputDebugStringA(buf);
	
	//num = rand() % 7;
	num = dist6(rng);

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
	
	std::uniform_int_distribution<std::mt19937::result_type> dist2(0, 1); // distribution in range [0, 1]
	direction = dist2(rng);
	//direction = rand() % 2;
	if (direction){
		Rotation();		
	}
	y = y - height;
}

void Figure::ShowFigure(TestApp * window)
{
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (figure[row * width + col] == '1' && y + row + 1 > 0) {
				window->SetChar(x + col + 1, y + row + 1, figure[row * width + col]);
			}				
		}
	}
}

void Figure::Rotation()
{	
	int* dst = new int [height * width];
	
	int i, j;
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			dst[i * height + j] = figure[j *width + width - i - 1];
		}
	}
	
	swap(figure, dst);
	swap(height, width);
	direction = direction ^ true;
	bool imposs = false;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (((figure[row * width + col] == '1') && (glass->dataGlass[y + row][x + col] == '1')) || ((x + width > 15) || (x < 0) || (y + height > 20))) {
				imposs = true;
			}
		}
	}
	if (imposs) {
		swap(figure, dst);
		swap(height, width);
		direction = direction ^ true;
	}
}

void Figure::MoveLeft()
{			
	if (x > 0) {
		bool block = false;
		for (int row = 0; row < height; row++) {
			block = block || ((figure[row *width] == '1') && (glass->dataGlass[y + row][x - 1] == '1'));

			/*char    buf[4096], *p = buf;
			sprintf(buf, " block %d\n", block);
			OutputDebugStringA(buf);*/
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
		
			/*char    buf[4096], *p = buf;
			sprintf(buf, " block %d\n", block);
			OutputDebugStringA(buf);*/
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

				/*char    buf[4096], *p = buf;
				sprintf(buf, " block %d\n", block);
				OutputDebugStringA(buf);*/
			}
		}
		if (!block)y++;
	}
	else block = true;
	return block;
}

Figure::~Figure()
{
	delete figure;
}