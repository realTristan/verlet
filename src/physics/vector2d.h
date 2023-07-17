#ifndef PHYSICS_VEC2D_H
#define PHYSICS_VEC2D_H

#include <math.h>
#include <tuple>

template <typename T>
class Vec2D
{
public:
    T x;
    T y;

    // Constructors
    Vec2D()
    {
        this->x = 0.0f;
        this->y = 0.0f;
    }
    Vec2D(T x, T y)
    {
        this->x = x;
        this->y = y;
    }
    Vec2D(const Vec2D<T> &v)
    {
        this->x = v.x;
        this->y = v.y;
    }

    // Operations
    Vec2D<T> &operator=(const Vec2D<T> &v)
    {
        this->x = v.x;
        this->y = v.y;
        return *this;
    }
    Vec2D<T> &operator+=(const Vec2D<T> &v)
    {
        this->x += v.x;
        this->y += v.y;
        return *this;
    }
    Vec2D<T> &operator-=(const Vec2D<T> &v)
    {
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }
    Vec2D<T> &operator*=(T f)
    {
        this->x *= f;
        this->y *= f;
        return *this;
    }
    Vec2D<T> &operator/=(T f)
    {
        this->x /= f;
        this->y /= f;
        return *this;
    }
    Vec2D<T> operator+(const Vec2D<T> &v) const
    {
        return Vec2D<T>(*this) += v;
    }
    Vec2D<T> operator-(const Vec2D<T> &v) const
    {
        return Vec2D<T>(*this) -= v;
    }
    Vec2D<T> operator*(T f) const
    {
        return Vec2D<T>(*this) *= f;
    }
    Vec2D<T> operator/(T f) const
    {
        return Vec2D<T>(*this) /= f;
    }

    // Get the magnitude of the vector
    T magnitude() const
    {
        return sqrt(this->x * this->x + this->y * this->y);
    }

    // Get the vector and return the x and y as a tuple
    std::tuple<T, T> get() const
    {
        return std::make_tuple(this->x, this->y);
    }

    // Set everything to zero
    void zero()
    {
        this->x = 0.0f;
        this->y = 0.0f;
    }

    // Copy the vector
    Vec2D<T> copy()
    {
        return Vec2D<T>(*this);
    }

    // Set the vector
    Vec2D<T> set(T x, T y)
    {
        this->x = x;
        this->y = y;
        return *this;
    }

    // Multiply by another vector
    Vec2D<T> multiply(const Vec2D<T> &v)
    {
        this->x *= v.x;
        this->y *= v.y;
        return *this;
    }

    // Divide by another vector
    Vec2D<T> divide(const Vec2D<T> &v)
    {
        this->x /= v.x;
        this->y /= v.y;
        return *this;
    }

    // Add a scalar
    Vec2D<T> add(T f)
    {
        this->x += f;
        this->y += f;
        return *this;
    }

    // Subtract a scalar
    Vec2D<T> subtract(T f)
    {
        this->x -= f;
        this->y -= f;
        return *this;
    }
};

#endif // PHYSICS_VEC2D_H