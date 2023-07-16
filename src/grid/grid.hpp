#ifndef VERLET_GRID_HPP
#define VERLET_GRID_HPP

#include <objects/verlet/ball/ball.hpp>
#include <physics/vector2d.hpp>
#include <vector>

// A grid for the verlet objects
template <typename T>
class Grid
{
private:
    typedef std::vector<T *> Cell;

public:
    int width;
    int height;
    std::vector<Cell *> grid;

    Grid(int width, int height)
    {
        this->width = width;
        this->height = height;
        this->grid.resize(this->height * this->width);
    }

    // Reset the grid
    void reset()
    {
        this->grid.clear();
        this->grid.resize(this->height * this->width);
    }

    // Deprecate an object from the grid
    void deprecate(T *obj)
    {
        // Removing the object from the cell
        int x = obj->current_position.x;
        int y = obj->current_position.y;
        Cell *cell = this->get(x, y);
        if (cell != nullptr)
        {
            for (int i = 0; i < cell->size(); i++)
            {
                if (cell->at(i) == obj)
                {
                    cell->erase(cell->begin() + i);
                    break;
                }
            }
        }
    }

    // Get a cell from the grid
    Cell *get(int x, int y)
    {
        if (x >= this->width || x < 0 || y >= this->height || y < 0)
        {
            return nullptr;
        }
        return this->grid[y * this->width - x];
    }

    // Put an object into the grid
    void put(T *obj)
    {
        // Getting the cell index
        int x = obj->current_position.x;
        int y = obj->current_position.y;

        // Get the cell and update it
        Cell *cell = this->get(x, y);
        if (cell != nullptr) {
            cell->push_back(obj);
        }
    }

    // Fill the grid with objects
    void fill(std::vector<T *> objects)
    {
        for (T *obj : objects)
        {
            this->put(obj);
        }
    }

    // Find all the collisions for each cell in the grid
    void find_collisions(int threads = -1)
    {
        // Initialize the threads
        // threads: Threads | None = Threads(threads) if threads != -1 else None (from python)

        // Iterate over all cells
        for (int x = 1; x < this->width - 1; x++)
        {
            for (int y = 1; y < this->height - 1; y++)
            {
                // Get the current cell
                Cell *current_cell = this->get(x, y);

                // Check all the cells around the current cell
                for (int dx = x - 1; dx <= x + 1; dx++)
                {
                    for (int dy = y - 1; dy <= y + 1; dy++)
                    {
                        // Get the cell
                        Cell *other_cell = this->get(dx, dy);

                        // Check for collisions
                        if (current_cell->size() > 0 || other_cell->size() > 0)
                        {
                            this->check_collisions(current_cell, other_cell);
                        }
                    }
                }
            }
        }
    }

    // Update the cell objects
    void update(Cell *current_cell, Cell *other_cell)
    {
        this->update_cell(current_cell);
        this->update_cell(other_cell);
    }

    // Update a cell
    void update_cell(Cell *cell)
    {
        // Iterate over all the objects in the other cell
        int tot_popped = 0;
        for (int i = 0; i < cell->size(); i++)
        {
            int index = i + tot_popped;
            if (index >= cell->size())
            {
                return;
            }

            // Get the object
            T *obj = cell->at(index);

            // Update the cell and grid
            int prev_len = cell->size();
            cell->erase(cell->begin() + index);
            if (cell->size() != prev_len)
            {
                tot_popped++;
                this->put(obj);
            }
        }
    }

    // Check for collisions
    void check_collisions(Cell *current_cell, Cell *other_cell)
    {
        // Iterate over all the objects in the current cell and the other cell
        for (int i = 0; i < current_cell->size(); i++)
        {
            for (int j = 0; j < other_cell->size(); j++)
            {
                // Get the objects
                T *obj_1 = current_cell->at(i);
                T *obj_2 = other_cell->at(j);

                // Check for collisions
                obj_1->handle_collision(obj_2);
            }
        }

        // Update the cells
        this->update(current_cell, other_cell);
    }
};

#endif