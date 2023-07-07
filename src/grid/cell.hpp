#include <iostream>
#include <objects/verlet/ball/ball.hpp>
#include "grid.hpp"

#ifndef VERLET_GRID_CELL_HPP
#define VERLET_GRID_CELL_HPP

class Cell
{
public:
    std::vector<VerletBall> objects;
    Cell(std::vector<VerletBall> objects = {})
    {
        this->objects = objects;
    }

    // Update the cell objects
    void update(Grid* grid, Cell* other_cell)
    {
        // Iterate over all the objects in the current cell
        int tot_popped = 0;
        for (int i = 0; i < this->objects.size(); i++)
        {
            int index = i + tot_popped;
            if (index >= this->objects.size())
            {
                break;
            }

            // Get the object
            VerletBall obj = this->objects[index];

            // Update the cell and grid
            int prev_len = this->objects.size();
            this->objects.erase(this->objects.begin() + index);
            if (this->objects.size() != prev_len)
            {
                tot_popped++;
                grid->put(obj);
            }
        }

        // Iterate over all the objects in the other cell
        tot_popped = 0;
        for (int i = 0; i < other_cell->objects.size(); i++)
        {
            int index = i + tot_popped;
            if (index >= other_cell->objects.size())
            {
                break;
            }

            // Get the object
            VerletBall obj = other_cell->objects[index];

            // Update the cell and grid
            int prev_len = other_cell->objects.size();
            other_cell->objects.erase(other_cell->objects.begin() + index);
            if (other_cell->objects.size() != prev_len)
            {
                tot_popped++;
                grid->put(obj);
            }
        }
    }

    // Check for collisions
    void check_collisions(Grid* grid, Cell* other_cell)
    {
        // Iterate over all the objects in the current cell and the other cell
        for (VerletBall obj_1 : this->objects)
        {
            for (VerletBall obj_2 : other_cell->objects)
            {
                // Check if the objects are colliding
                obj_1.handle_collision(&obj_2);
            }
        }

        // Update the cells
        this->update(grid, other_cell);
    }
};

#endif