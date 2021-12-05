#include "Grid.h"
#include "GridManadger.h"
#include "CellularPotts.h"
#include "AdhesionConstraint.h"
#include "VolumeConstraint.h"
#include "PerimeterConstraint.h"
#include "SimpleDisplay.h"

#include <iostream>
#include <cstdint> // for specific size integers
#include <fstream> // for file handling

constexpr int FLOAT_MIN = 0;
constexpr int FLOAT_MAX = 1;

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

void singleCell()
{
	srand(time(NULL));

	Parameters p(1, { {0,20},{20,100} }, 20.0f, { 0,5 }, { 0,10000 }, { 0,0 }, { 0,0 });
	CellularPotts m(std::pair<int, int>(200, 200), &p);

	auto cellId = m.makeNewCellID(1);

	for (size_t i = 0; i < m.grid.size.first; i++)
	{
		for (size_t j = 0; j < m.grid.size.second; j++)
		{
			m.setPixel(std::pair<int, int>(i, j), 0);
		}
	}

	m.setPixel(std::pair<int, int>(m.grid.size.first / 2, m.grid.size.second / 2), cellId);

	m.setPixel(std::pair<int, int>((m.grid.size.first/2)+20, (m.grid.size.second /2)+20), cellId);

	AdhesionConstraint a;
	VolumeConstraint v;

	m.addConstraint(&a);
	m.addConstraint(&v);

	int iterNumber = 0;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Single Cell");
	SimpleDisplay display(&m, &window);

	while (true)
	{
		m.monteCarloStep();
		display.render();
	}
}

void ising()
{
	srand(time(NULL));

	Parameters p(3, { {0,20},{20,100} }, 0.01f, { 0,5 }, { 0,1000 }, { 0,0 }, { 0,0 });

	CellularPotts m(std::pair<int, int>(250, 250), &p);

	auto cellId = m.makeNewCellID(1);

	std::cout << "Starting to init..." << std::endl;

	for (size_t i = 0; i < m.grid.size.first; i++)
	{
		for (size_t j = 0; j < m.grid.size.second; j++)
		{
			std::cout << "Index: " << ((i* m.grid.size.first) + j) << " out of: " << m.grid.size.first * m.grid.size.second << "\r";

			float randomNumber = FLOAT_MIN + (float)(rand()) / ((float)(RAND_MAX / (FLOAT_MAX - FLOAT_MIN)));

			if (randomNumber < 0.49) {
				m.setPixel(std::pair<int, int>(i, j), cellId);
			}
			else {

				m.setPixel(std::pair<int, int>(i, j), 0);
			}
		}
	}

	std::cout << "Init finished" << std::endl;

	AdhesionConstraint a;
	m.addConstraint(&a);


	sf::RenderWindow window(sf::VideoMode(800, 600), "CMP");
	SimpleDisplay display(&m, &window);

	while (true)
	{
		m.monteCarloStep();
		display.render();
	}
}

void EpithelialSheet()
{
	srand(time(NULL));
	Parameters p(3, { {0,0},{0,-2} }, 50.0f, { 0,70 }, { 0,100 }, { 0,3 }, { 0,0 });

	CellularPotts m(std::pair<int, int>(1000, 300), &p);

	std::cout << "INIT BEGIN..." << std::endl;

	for (size_t i = 5; i < 500; i+=10)
	{
		for (size_t j = 5; j <300; j+=10)
		{
			m.setPixel(std::pair<int,int>(i, j), m.makeNewCellID(1));
		}

	}

	std::cout << "INIT END!" << std::endl;

	AdhesionConstraint a;
	VolumeConstraint v;
	PerimeterConstraint per;

	m.addConstraint(&a);
	m.addConstraint(&v);
	m.addConstraint(&per);

	int iterNumber = 0;

	sf::RenderWindow window(sf::VideoMode(800, 600), "CMP");
	SimpleDisplay display(&m, &window);

	while (true)
	{
		m.monteCarloStep();
		display.render();
	}




}

void singleCellMiniature()
{
	srand(time(NULL));

	Parameters p(1, { {0,20},{20,100} }, 20.0f, { 0,5 }, { 0,50 }, { 0,0 }, { 0,0 });
	CellularPotts m(std::pair<int, int>(50, 50), &p);

	auto cellId = m.makeNewCellID(1);

	for (size_t i = 0; i < m.grid.size.first; i++)
	{
		for (size_t j = 0; j < m.grid.size.second; j++)
		{
			m.setPixel(std::pair<int, int>(i, j), 0);
		}
	}

	m.setPixel(std::pair<int, int>(m.grid.size.first / 2, m.grid.size.second / 2), cellId);

	AdhesionConstraint a;
	VolumeConstraint v;

	m.addConstraint(&a);
	m.addConstraint(&v);

	int iterNumber = 0;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Single Cell");
	SimpleDisplay display(&m, &window);

	while (true)
	{
		m.monteCarloStep();
		display.render();
	}
}


int main()
{
	//singleCellMiniature();
	//singleCell();
	
	//ising();
	EpithelialSheet();
	
	return 0;
}