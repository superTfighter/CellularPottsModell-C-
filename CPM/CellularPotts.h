#pragma once
#include "Parameters.h"
#include "Grid.h"
#include "HamiltonianConstraint.h"
#include "DiceSet.h"


class HamiltonianConstraint;

class CellularPotts
{
public:
	CellularPotts(std::pair<int, int> gridSize, Parameters parameters);

	void addConstraint(HamiltonianConstraint* c);
	std::vector<HamiltonianConstraint* > getAllContraints();

	void monteCarloStep();
	int makeNewCellID(int kind);

	void setCellKind(int typeID, int kind);
	void updateBorderNearAri(int index, int old_type, int new_type);


	void setPixelI(int cellId, int sourceType);
	void setPixel(std::pair<int, int> point, int sourceType);

	int getCellVolume(int cellId);

	Grid grid;
	Parameters parameters;
	DiceSet borderpixels;
	float simTime;

private:
	int number_of_cells;
	int last_cell_id;

	float deltaH(int sourceIndex,int targetIndex,int sourceType,int targetType);
	bool docopy(float deltaH);

	std::vector<int> cellVolume;
	std::vector<int> cellTypeToKind;
	std::vector<int> _neighbours;

	std::vector<HamiltonianConstraint*> contraints;
};

