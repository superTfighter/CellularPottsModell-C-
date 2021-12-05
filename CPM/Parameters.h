#pragma once
#include <string>
#include <iostream>
#include <vector>

//TODO:REFACTOR AND RETHINK THIS 
class Parameters
{
public:
	Parameters(int numberOfCells, std::vector<std::vector<int>> J, float T, std::vector<float> LAMBDA_V, std::vector<float> V, std::vector<float> LAMBDA_P, std::vector<float> P)
	{
		this->numberOfCells = numberOfCells;


		this->J = J;
		this->T = T;

		this->LAMBDA_V = LAMBDA_V;
		this->V = V;

		this->LAMBDA_P = LAMBDA_P;
		this->P = P;
 	}

	//Adhesion parameter , Multidimensional vector => [[0,20],[20,100]] => means 0:0 => 0 , 0:1 => 20, 1:0 => 20 , 1:1 => 100
	std::vector<std::vector<int>> J;
	
	//Temperature parameter
	float T;

	//How many cellkinds do we have
	int numberOfCells;

	// Volume constraint parameters per cellKind
	std::vector<float> LAMBDA_V;
	std::vector<float> V;

	// Perimeter constraint parameters per cellKind
	std::vector<float> LAMBDA_P;
	std::vector<float> P;

};

