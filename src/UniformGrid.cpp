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

void UniformGrid::Move(Rigidbody* body, float oldX, float oldY, float newX, float newY)
{
    int oldCellX = (int)(oldX / UniformGrid::CELL_SIZE);
    int oldCellY = (int)(oldY / UniformGrid::CELL_SIZE);

    int cellX = (int)(newX / UniformGrid::CELL_SIZE);
    int cellY = (int)(newY / UniformGrid::CELL_SIZE);

    if (oldCellX == cellX && oldCellY == cellY) return;

    // Remove from old cell, add to new cell
    auto& oldCell = cells[oldCellX][oldCellY];
    auto it = std::find(oldCell.begin(), oldCell.end(), body);

    if (it != oldCell.end())
    {
        oldCell.erase(it);
    }

    body->globalCentroid.x = newX;
    body->globalCentroid.y = newY;

    add(body);
}
