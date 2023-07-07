#include <iostream>
#include <vector>
#include <grid/cell.hpp>
#include <physics/vector2d.hpp>
#include <objects/verlet/ball/ball.hpp>

#ifndef VERLET_GRID_HPP
#define VERLET_GRID_HPP

class Grid
{
public:
    int cell_size;
    int width;
    int height;
    void reset();

    std::vector<std::vector<Cell>> grid;
    Grid(int width, int height, int cell_size = 100)
    {
        this->cell_size = cell_size;
        this->width = width / this->cell_size;
        this->height = height / this->cell_size;
        this->reset();
    }

    // Reset the grid
    void reset()
    {
        for (int i = 0; i < this->height; i++)
        {
            std::vector<Cell> row;
            for (int j = 0; j < this->width; j++)
            {
                row.push_back(Cell());
            }
            this->grid[i] = row;
        }
    }

    // Deprecate an object from the grid
    void deprecate(VerletBall obj)
    {
        // Getting the cell index
        std::tuple<int, int> index = this->calculate_cell_index(obj.current_position);
        int x = std::get<0>(index);
        int y = std::get<1>(index);

        // Removing the object from the cell
        Cell *cell = this->get(x, y);
        cell->objects.erase(
            std::remove(
                cell->objects.begin(), cell->objects.end(), obj),
            cell->objects.end());
    }

    // Get a cell from the grid
    Cell *get(int x, int y)
    {
        if (x >= this->width || x < 0 || y >= this->height || y < 0)
        {
            return &Cell();
        }
        return &this->grid[y][x];
    }

    // Get the cell index from a position
    std::tuple<int, int> calculate_cell_index(Vector2D position)
    {
        return std::make_tuple(int(position.x / this->cell_size), int(position.y / this->cell_size));
    }

    // Put an object into the grid
    void put(VerletBall obj)
    {
        // Getting the cell index
        std::tuple<int, int> index = this->calculate_cell_index(obj.current_position);
        int x = std::get<0>(index);
        int y = std::get<1>(index);

        // Get the cell and update it
        Cell *cell = this->get(x, y);
        cell->objects.push_back(obj);
    }

    // Fill the grid with objects
    void fill(std::vector<VerletBall> objects)
    {
        for (VerletBall obj : objects)
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
        for (int x = 0; x < this->width; x++)
        {
            for (int y = 0; y < this->height; y++)
            {
                // Get the current cell
                Cell *current_cell = this->get(x, y);
                if (current_cell->objects.size() == 0)
                {
                    continue;
                }

                // Check all the cells around the current cell
                for (int dx = x - 1; dx < x + 2; dx++)
                {
                    for (int dy = y - 1; dy < y + 2; dy++)
                    {
                        // Get the cell
                        Cell *other_cell = this->get(dx, dy);
                        if (other_cell->objects.size() == 0)
                        {
                            continue;
                        }

                        // Check for collisions
                        if (current_cell->objects.size() > 0 || other_cell->objects.size() > 0)
                        {
                            current_cell->check_collisions(this, other_cell);
                        }
                    }
                }
            }
        }
    }
};

#endif