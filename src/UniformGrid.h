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
	static const int NUM_CELLS = 20;
	static const int CELL_SIZE = 500;

	std::unordered_set <Rigidbody*> *cells[NUM_CELLS][NUM_CELLS];
private:

};

