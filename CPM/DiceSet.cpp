#include "DiceSet.h"
#include <random>
#include <iostream>

DiceSet::DiceSet()
{
	this->indices = std::map<int, int>();
	this->elements = std::vector<int>();

	this->length = 0;
}

bool DiceSet::contains(int uniqueID)
{
	for (std::pair<int, int> element : indices)
	{
		if (uniqueID == element.first)
			return true;
	}

	return false;
}

void DiceSet::insert(int uniqueID)
{
	if (this->contains(uniqueID))
		return;

	this->indices.insert(std::pair<int, int>(length,uniqueID));
	this->elements.push_back(uniqueID);
	this->length++;

}

void DiceSet::remove(int uniqueID)
{
	if (!this->contains(uniqueID))
		return;

	std::map<int,int>::iterator i = this->indices.find(uniqueID);

	int length = i->first;

	this->indices.erase(i);

	
	int e = this->elements.back();
	this->elements.pop_back();
	this->length--;

	if (e == uniqueID)
		return;

	//TODO:FIX THIS

	this->insert(length);

	//PUSH LENGHT INTO THIS 
	//int a = i->first;

	//this->elements[i->first] = e;
	//this->indices[e] = i->first;

	

}

int DiceSet::sample()
{
	//the random device that will seed the generator -- TODO: FIX!!!
	int index = rand() % ((this->elements.size() - 1 - 0) + 1);

	return elements[index];
}

