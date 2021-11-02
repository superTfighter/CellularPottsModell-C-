#pragma once
#include "HamiltonianConstraint.h"

class ActivityContraint : public HamiltonianConstraint
{

public:
	float deltaH(int sourceI, int targetI, int  source_type, int target_type) override;

private:
	float activityAt(int index);

};

