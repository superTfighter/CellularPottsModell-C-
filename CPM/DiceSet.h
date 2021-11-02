#pragma once
#include <vector>
#include <map>

class DiceSet
{
public:
	DiceSet();

	std::vector<int> elements;
	std::map<int, int> indices;

	float length;

	bool contains(int uniqueID);
	void insert(int uniqueID);
	void remove(int uniqueID);
	int sample();

private:


};

