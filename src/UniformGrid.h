#pragma once
#include "Rigidbody.h"
#include <vector>
#include <unordered_set>

class UniformGrid
{
public:
	UniformGrid();
	~UniformGrid();
	void add(Rigidbody* body);
	void Print();
	void Move(Rigidbody* body, float oldX, float oldY, float newX, float newY);
	static const int NUM_CELLS = 25;
	static const int CELL_SIZE = 2000;

	std::unordered_set <Rigidbody*> *cells[NUM_CELLS][NUM_CELLS];
private:

};

