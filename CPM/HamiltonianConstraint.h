#pragma once
#include "CellularPotts.h"


class CellularPotts;

class HamiltonianConstraint
{
public:

	virtual float deltaH(int sourceI, int targetI,int  source_type,int target_type);
	void setModel(CellularPotts* modell);

protected:
	CellularPotts* model;

private:
	

};

