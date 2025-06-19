#pragma once
#include "Rigidbody.h"
#include <vector>

class UniformGrid
{
public:
	UniformGrid();
	~UniformGrid()=default;
	void add(Rigidbody* body);
	void Print();
	static const int NUM_CELLS = 10;
	static const int CELL_SIZE = 200;

	std::vector<Rigidbody*> cells[NUM_CELLS][NUM_CELLS];
private:

};

