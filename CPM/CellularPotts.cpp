#include "CellularPotts.h"

CellularPotts::CellularPotts(std::pair<int, int> gridSize, Parameters parameters) : grid(gridSize.first, gridSize.second), parameters(parameters)
{
	this->cellVolume = std::vector<int>();
	cellVolume.resize(gridSize.first*gridSize.second*10);

	this->cellTypeToKind = std::vector<int>();
	cellTypeToKind.resize(gridSize.first * gridSize.second*10);

	this->_neighbours = std::vector<int>();
	_neighbours.resize(gridSize.first * gridSize.second *10);

	this->simTime = 0;
}

void CellularPotts::addConstraint(HamiltonianConstraint* c)
{
	c->setModel(this);
	this->contraints.push_back(c);
}

std::vector<HamiltonianConstraint*> CellularPotts::getAllContraints()
{
	return this->contraints;
}

void CellularPotts::monteCarloStep()
{
	float delta_t = 0.0f;

	while (delta_t < 1.0)
	{
		delta_t += 1. / (this->borderpixels.length);

		auto tgt_i = this->borderpixels.sample();
		auto Ni = this->grid.neighi(tgt_i);

		bool gotNeigbour = false;

		int src_i = -1;

		while(!gotNeigbour)
		{

			int r = rand() % ((Ni.size()-1) - 0 + 1) + 0;
			//RANDOM!!
			src_i = Ni[r];

			if (0 <= src_i)
				gotNeigbour = true;
		}

		auto src_type = this->grid.pixti(src_i);
		auto tgt_type = this->grid.pixti(tgt_i);

		if (tgt_type != src_type)
		{
			auto hamiltonian = this->deltaH(src_i, tgt_i, src_type, tgt_type);

			if (this->docopy(hamiltonian))
				this->setPixelI(tgt_i, src_type);
		}
	}

	this->simTime++;
}

int CellularPotts::makeNewCellID(int kind)
{
	int newID = ++this->last_cell_id;


	try {
		cellVolume.insert(cellVolume.begin() + newID, kind);
	}
	catch (std::out_of_range& err) {

		cellVolume.resize(cellVolume.size() * 2);
		cellVolume.insert(cellVolume.begin() + newID, kind);
	}

	this->setCellKind(newID, kind);

	return newID;
}

void CellularPotts::setCellKind(int typeID, int kind)
{

	try {
		cellTypeToKind.insert(cellTypeToKind.begin() + typeID, kind);
	}
	catch (std::out_of_range& err) {

		cellTypeToKind.resize(cellTypeToKind.size() * 2);
		cellTypeToKind.insert(cellTypeToKind.begin() + typeID, kind);
	}
}

void CellularPotts::updateBorderNearAri(int index, int old_type, int new_type)
{
	if (old_type == new_type)
		return;

	std::vector<int> Ni = this->grid.neighi(index);

	//TODO: What is wasborder
	bool wasborder = this->_neighbours[index] > 0;
	this->_neighbours[index] = 0;

	for (auto ni : Ni)
	{

		if (0 < ni) {
			int nt = this->grid.pixti(ni);

			if (nt != new_type)
				this->_neighbours[index]++;

			if (nt == old_type) {

				if (this->_neighbours[ni]++ == 0)
					this->borderpixels.insert(ni);
			}

			if (nt == new_type) {

				if (--this->_neighbours[ni] == 0) {
					this->borderpixels.remove(ni);
				}
			}

		}

	}

	if (!wasborder && this->_neighbours[index] > 0)
		this->borderpixels.insert(index);

	if (wasborder && this->_neighbours[index] == 0)
		this->borderpixels.remove(index);

}


float CellularPotts::deltaH(int sourceIndex, int targetIndex, int sourceType, int targetType)
{
	float result = 0;

	for (auto& constraint : this->contraints)
	{

		result += constraint->deltaH(sourceIndex, targetIndex, sourceType, targetType);

	}

	return result;
}

bool CellularPotts::docopy(float deltaH)
{
	if (deltaH < 0) 
		return true;

	float e = std::exp(-deltaH / this->parameters.T);
	int random = ((double)rand() / (RAND_MAX)) + 1;

	return random < e;
}


void CellularPotts::setPixelI(int cellId, int sourceType)
{
	int type_old = this->grid.pixti(cellId);

	if (type_old == sourceType)
		return;

	if (type_old > 0)
	{
		this->cellVolume[type_old]--;

		if (this->cellVolume[type_old] == 0)
		{
			//TODO: Remove cellvolume and tk2 and nr_of_cells
		}


	}

	this->grid.setpixi(cellId, sourceType);

	if (sourceType > 0)
		this->cellVolume[sourceType]++;


	this->updateBorderNearAri(cellId, type_old, sourceType);
}

void CellularPotts::setPixel(std::pair<int, int> point, int sourceType)
{
	this->setPixelI(this->grid.pointToIndex(point), sourceType);
}

int CellularPotts::getCellVolume(int cellId)
{
	return this->cellVolume[cellId];
}
