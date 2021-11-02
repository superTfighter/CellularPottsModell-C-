#include "GridManadger.h"

int GridManadger::seedCell(int kind, int maxAttempts)
{
	std::pair<int, int> position = this->model.grid.middle;


	//TODO:FIX, SEARCH FOR 0 POSITION AROUND THE MIDDLE!!
	/*while (this->model.grid.pointToIndex(middle) != 0 && maxAttempts-- > 0)
	{
		

	}*/

	int newID = this->model.makeNewCellID(kind);
	this->model.grid.setPixel(position, newID);

	return newID;
}
