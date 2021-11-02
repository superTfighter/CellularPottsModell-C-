#include "AdhesionConstraint.h"
#include <vector>
#include <iostream>

float AdhesionConstraint::deltaH(int sourceI, int targetI, int source_type, int target_type)
{
    return this->H(targetI, source_type) - this->H(targetI, target_type);
}

float AdhesionConstraint::H(int i, int tp)
{
    int r = 0;

	std::vector<int> neigbours = this->model->grid.neighi(i);

    for (auto& elem : neigbours)
    {
        if(elem != -1)
        {
            int tn = this->model->grid.pixti(elem);

            if (tn != tp)
                r += this->J(tn, tp);
        }
    }

    return r;
}

//TODO: Solve adhesion parameters...honestly every parameter should be solved
float AdhesionConstraint::J(int t1, int t2)
{
    std::vector<int> J = this->model->parameters.J[t1];

    return J[t2];
}
