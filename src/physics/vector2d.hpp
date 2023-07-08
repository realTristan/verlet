#include <iostream>
#include <math.h>

#ifndef VEC2D_HPP
#define VEC2D_HPP

class Vec2D
{
public:
    float x;
    float y;

    // Constructors
    Vec2D()
    {
        this->x = 0.0f;
        this->y = 0.0f;
    }
    Vec2D(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
    Vec2D(const Vec2D &v)
    {
        this->x = v.x;
        this->y = v.y;
    }

    // Operations
    Vec2D &operator=(const Vec2D &v)
    {
        this->x = v.x;
        this->y = v.y;
        return *this;
    }
    Vec2D &operator+=(const Vec2D &v)
    {
        this->x += v.x;
        this->y += v.y;
        return *this;
    }
    Vec2D &operator-=(const Vec2D &v)
    {
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }
    Vec2D &operator*=(float f)
    {
        this->x *= f;
        this->y *= f;
        return *this;
    }
    Vec2D &operator/=(float f)
    {
        this->x /= f;
        this->y /= f;
        return *this;
    }
    Vec2D operator+(const Vec2D &v) const
    {
        return Vec2D(*this) += v;
    }
    Vec2D operator-(const Vec2D &v) const
    {
        return Vec2D(*this) -= v;
    }
    Vec2D operator*(float f) const
    {
        return Vec2D(*this) *= f;
    }
    Vec2D operator/(float f) const
    {
        return Vec2D(*this) /= f;
    }

    // Get the magnitude of the vector
    float magnitude() const
    {
        return sqrt(this->x * this->x + this->y * this->y);
    }

    // Get the vector and return the x and y as a tuple
    std::tuple<float, float> get() const
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
    Vec2D copy()
    {
        return Vec2D(*this);
    }

    // Set the vector
    Vec2D set(float x, float y)
    {
        this->x = x;
        this->y = y;
        return *this;
    }

    // Multiply by another vector
    Vec2D multiply(const Vec2D &v)
    {
        this->x *= v.x;
        this->y *= v.y;
        return *this;
    }

    // Divide by another vector
    Vec2D divide(const Vec2D &v)
    {
        this->x /= v.x;
        this->y /= v.y;
        return *this;
    }

    // Add a scalar
    Vec2D add(float f)
    {
        this->x += f;
        this->y += f;
        return *this;
    }

    // Subtract a scalar
    Vec2D subtract(float f)
    {
        this->x -= f;
        this->y -= f;
        return *this;
    }
};

#endif // VEC2D_HPP