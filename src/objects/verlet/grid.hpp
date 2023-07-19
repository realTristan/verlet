#ifndef VERLET_GRID_HPP
#define VERLET_GRID_HPP

#include <objects/verlet/ball/ball.hpp>
#include <physics/vector2d.h>
#include <vector>

// A cell for the grid
template <typename T>
class Cell
{
public:
    int index;
    std::vector<T *> objects;

    Cell(int index)
    {
        this->index = index;
    }

    // Get the size of the cell
    int size()
    {
        return this->objects.size();
    }

    // Get an object from the cell
    T *at(int index)
    {
        if (index < 0 || index >= this->objects.size())
        {
            return nullptr;
        }
        return this->objects[index];
    }

    // Push an object into the cell
    void push_back(T *obj)
    {
        this->objects.push_back(obj);
    }

    // Erase an object from the cell
    void erase(int index)
    {
        if (index < 0 || index >= this->objects.size())
        {
            return;
        }
        this->objects.erase(this->objects.begin() + index);
    }

    // Set the objects
    void set(std::vector<T *> objects)
    {
        this->objects = objects;
    }
};

// A grid for the verlet objects
template <typename T>
class Grid
{
public:
    int width;
    int height;
    int cell_size;

    std::vector<Cell<T> *> grid = std::vector<Cell<T> *>();

    Grid(int width, int height, int cell_size = 100)
    {
        this->width = width;
        this->height = height;
        this->cell_size = cell_size;
        this->reset();
    }

    // Reset the grid
    void reset()
    {
        this->grid.clear();
        this->grid = std::vector<Cell<T> *>(this->width * this->height / this->cell_size / this->cell_size);
        for (int i = 0; i < this->grid.size(); i++)
        {
            this->grid[i] = new Cell<T>(i);
        }
    }

    // Deprecate an object from the grid
    void deprecate(T *obj)
    {
        // Removing the object from the cell
        int x = obj->current_position.x;
        int y = obj->current_position.y;
        Cell<T> *cell = this->get(x, y);
        if (cell != nullptr)
        {
            for (int i = 0; i < cell->size(); i++)
            {
                if (cell->at(i) == obj)
                {
                    cell->erase(i);
                    break;
                }
            }
        }

        // Set the object's grid cell to null
        obj->set_grid_cell(nullptr);
    }

    // Get a cell from the grid
    Cell<T> *get(int x, int y)
    {
        if (x > this->width || y > this->height || x < 0 || y < 0)
        {
            return nullptr;
        }
        return this->grid[x * y / this->cell_size / this->cell_size];
    }

    // Put an object into the grid
    Cell<T> *put(T *obj)
    {
        // Getting the cell index
        int x = obj->current_position.x;
        int y = obj->current_position.y;

        // Get the cell and update it
        Cell<T> *cell = this->get(x, y);
        if (cell != nullptr)
        {
            cell->push_back(obj);
            obj->set_grid_cell(cell);
        }
        return cell;
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
    void find_collisions(Cell<T> *current_cell)
    {
        // Check collisions in the current cell
        check_collisions(current_cell, current_cell);

        // FIX THIS
        /* Check all the cells around the current cell
        int x = current_cell->index % (this->width * this->height / this->cell_size);
        int y = current_cell->index / (this->width * this->height / this->cell_size);
        for (int i = -1; i <= 1; i++)
        {
            int new_x = x + i * this->cell_size;
            if (new_x < 0 || new_x >= this->width / this->cell_size)
            {
                continue;
            }
            for (int j = -1; j <= 1; j++)
            {
                int new_y = y + j * this->cell_size;
                if (new_y < 0 || new_y >= this->height / this->cell_size)
                {
                    continue;
                }
                Cell<T> *other_cell = this->get(new_x, new_y);
                if (other_cell != nullptr)
                {
                    check_collisions(current_cell, other_cell);
                }
            }
        }*/
    }

    // Update a cell
    void update_cell(Cell<T> *cell)
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
            cell->erase(index);
            if (cell->size() != prev_len)
            {
                tot_popped++;
                this->put(obj);
            }
        }
    }

    // Update the cell objects
    void update(Cell<T> *current_cell, Cell<T> *other_cell)
    {
        this->update_cell(current_cell);
        this->update_cell(other_cell);
    }

    // Check for collisions
    void check_collisions(Cell<T> *current_cell, Cell<T> *other_cell)
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