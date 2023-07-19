#ifndef OBJECT_LIMITER_HPP
#define OBJECT_LIMITER_HPP

#include <vector>
#include <objects/verlet/grid.hpp>

class ObjectLimiter {
public:
    int max_objects;

    ObjectLimiter(int max_objects) {
        this->max_objects = max_objects;
    }

    // Set the max objects
    void set_max_objects(int max_objects) {
        this->max_objects = max_objects;
    }

    // Check if the object is within the limit
    bool within_limit(int current_objects) {
        return current_objects < this->max_objects;
    }

    // Pop object from array if over limit
    template <typename T>
    void update(std::vector<T *> *objects, Grid<T> *grid = nullptr) {
        if (objects->size() > this->max_objects) {
            if (grid != nullptr) {
                grid->deprecate(objects->at(0));
            }
            objects->erase(objects->begin());
        }
    }
};

#endif // OBJECT_LIMITER_HPP