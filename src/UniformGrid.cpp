#include "UniformGrid.h"
#include <iostream>

UniformGrid::UniformGrid()  
{  
    // Initialize the grid cells as empty unordered sets.  
    for (int x = 0; x < NUM_CELLS; x++)  
    {  
        for (int y = 0; y < NUM_CELLS; y++)  
        {  
            cells[x][y] = new std::unordered_set<Rigidbody*>();  
        }  
    }  
}    UniformGrid::~UniformGrid()  
    {  
        // Clean up allocated memory for each cell.  
        for (int x = 0; x < NUM_CELLS; x++)  
        {  
            for (int y = 0; y < NUM_CELLS; y++)  
            {  
                delete cells[x][y];  
            }  
        }  
    }

//
//UniformGrid::~UniformGrid()
//{
//    delete cells;
//}

void UniformGrid::add(Rigidbody* body)
{
    // Determine which grid cell it's in.
    int cellX = (int)(body->globalCentroid.x / UniformGrid::CELL_SIZE);
    int cellY = (int)(body->globalCentroid.y / UniformGrid::CELL_SIZE);

    // Add to the front of list for the cell it's in.
    cells[cellX][cellY]->emplace(body);
}

void UniformGrid::Print()
{
    for (int x = 0; x < NUM_CELLS; x++)
    {
        for (int y = 0; y < NUM_CELLS; y++)
        {
            std::cout<< "BODIES AT: " << x << "," << y << ": " << cells[x][y]->size() << "\n";
        }
    }
}

void UniformGrid::Move(Rigidbody* body, float oldX, float oldY, float newX, float newY)
{
    int oldCellX = static_cast<int>(oldX / UniformGrid::CELL_SIZE);
    int oldCellY = static_cast<int>(oldY / UniformGrid::CELL_SIZE);
    int cellX = static_cast<int>(newX / UniformGrid::CELL_SIZE);
    int cellY = static_cast<int>(newY / UniformGrid::CELL_SIZE);

    // Bounds check
    if (oldCellX < 0 || oldCellX >= NUM_CELLS || oldCellY < 0 || oldCellY >= NUM_CELLS ||
        cellX < 0 || cellX >= NUM_CELLS || cellY < 0 || cellY >= NUM_CELLS)
    {
        return;

    }

    if (oldCellX == cellX && oldCellY == cellY) return;
    // Remove from old cell, add to new cell
    cells[oldCellX][oldCellY]->erase(body);

    //body->globalCentroid.x = newX;
    //body->globalCentroid.y = newY;

    add(body);
}
