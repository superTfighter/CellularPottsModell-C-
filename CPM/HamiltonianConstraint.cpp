#include "HamiltonianConstraint.h"

float HamiltonianConstraint::deltaH(int sourceI, int targetI, int source_type, int target_type)
{
    return 0.0f;
}

void HamiltonianConstraint::setModel(CellularPotts* modell)
{
    this->model = modell;
}
