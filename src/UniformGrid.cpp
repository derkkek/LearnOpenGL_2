#include "UniformGrid.h"
#include <iostream>

UniformGrid::UniformGrid()
{
    // Clear the grid.
    for (int x = 0; x < NUM_CELLS; x++)
    {
        for (int y = 0; y < NUM_CELLS; y++)
        {
            cells[x][y].clear();
        }
    }
}

void UniformGrid::add(Rigidbody* body)
{
    // Determine which grid cell it's in.
    int cellX = (int)(body->globalCentroid.x / UniformGrid::CELL_SIZE);
    int cellY = (int)(body->globalCentroid.y / UniformGrid::CELL_SIZE);

    // Add to the front of list for the cell it's in.
    cells[cellX][cellY].push_back(body);
}

void UniformGrid::Print()
{
    for (int x = 0; x < NUM_CELLS; x++)
    {
        for (int y = 0; y < NUM_CELLS; y++)
        {
            std::cout<< "BODIES AT: " << x << "," << y << ": " << cells[x][y].size() << "\n";
        }
    }
}
