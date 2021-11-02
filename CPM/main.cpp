#include <iostream>
#include "Grid.h"
#include "GridManadger.h"
#include "CellularPotts.h"
#include "AdhesionConstraint.h"
#include <cstdint> // for specific size integers
#include <fstream> // for file handling
#include "VolumeConstraint.h"


void drawToConsole(CellularPotts* m)
{

	for (size_t i = 0; i < m->grid.size.first; i++)
	{
		for (size_t j = 0; j < m->grid.size.second; j++)
		{
			std::cout << m->grid.pixti(m->grid.pointToIndex(std::pair<int, int>(i, j))) << " ";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;

}

//I think it has a bug when drawing so i need to replace it soon. 
void drawToFile(CellularPotts* m)
{
	FILE* f;
	unsigned char* img = NULL;
	int filesize = 54 + 3 * m->grid.size.first * m->grid.size.second;  //w is your image width, h is image height, both int

	img = (unsigned char*)malloc(3 * m->grid.size.first * m->grid.size.second);
	memset(img, 0, 3 * m->grid.size.first * m->grid.size.second);

	int w = m->grid.size.first;
	int h = m->grid.size.second;

	int x, y, r, g, b;

	for (size_t i = 0; i < m->grid.size.first; i++)
	{
		for (size_t j = 0; j < m->grid.size.second; j++)
		{
			int type = m->grid.pixti(m->grid.pointToIndex(std::pair<int, int>(i, j)));

			if (type == 0)
			{
				r = 255;
				g = 255;
				b = 255;

				x = i;
				y = (m->grid.size.second - 1) - j;

				img[(x + y * m->grid.size.first) * 3 + 2] = (unsigned char)(r);
				img[(x + y * m->grid.size.first) * 3 + 1] = (unsigned char)(g);
				img[(x + y * m->grid.size.first) * 3 + 0] = (unsigned char)(b);

			}
			else
			{
				r = 255;
				g = 0;
				b = 0;

				x = i;
				y = (m->grid.size.second - 1) - j;

				img[(x + y * m->grid.size.first) * 3 + 2] = (unsigned char)(r);
				img[(x + y * m->grid.size.first) * 3 + 1] = (unsigned char)(g);
				img[(x + y * m->grid.size.first) * 3 + 0] = (unsigned char)(b);
			}
		}


	}

	unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
	unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };
	unsigned char bmppad[3] = { 0,0,0 };

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w >> 8);
	bmpinfoheader[6] = (unsigned char)(w >> 16);
	bmpinfoheader[7] = (unsigned char)(w >> 24);
	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h >> 8);
	bmpinfoheader[10] = (unsigned char)(h >> 16);
	bmpinfoheader[11] = (unsigned char)(h >> 24);

	std::string a = std::to_string(m->simTime) + "_img.bmp";

	f = fopen(a.c_str(), "wb");
	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);
	for (int i = 0; i < h; i++)
	{
		fwrite(img + (w * (h - i - 1) * 3), 3, w, f);
		fwrite(bmppad, 1, (4 - (w * 3) % 4) % 4, f);
	}

	free(img);
	fclose(f);
}


int main()
{
	srand(time(NULL));

	Parameters p(1, { {0,20},{20,100} }, 20.0f, { 0,50 }, { 0,500 });
	CellularPotts m(std::pair<int, int>(200, 200), p);

	auto cellId = m.makeNewCellID(1);

	for (size_t i = 0; i < m.grid.size.first; i++)
	{
		for (size_t j = 0; j < m.grid.size.second; j++)
		{

			m.setPixel(std::pair<int, int>(i, j), 0);
		}
	}

	m.setPixel(std::pair<int, int>(m.grid.size.first / 2, m.grid.size.second/2), cellId);

	AdhesionConstraint a;
	VolumeConstraint v;

	m.addConstraint(&a);
	m.addConstraint(&v);


	int iterNumber = 0;

	while (true)
	{
		m.monteCarloStep();

		//drawToConsole(&m);
		drawToFile(&m);

		iterNumber++;
	}





	return 0;
}