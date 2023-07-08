#include <iostream>
#include <math.h>

#ifndef VEC3D_HPP
#define VEC3D_HPP

class Vec3D
{
public:
    float x;
    float y;
    float z;

    // Constructors
    Vec3D()
    {
        this->x = 0.0f;
        this->y = 0.0f;
        this->z = 0.0f;
    }
    Vec3D(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Vec3D(const Vec3D &v)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
    }

    // Operations
    Vec3D &operator=(const Vec3D &v)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
        return *this;
    }
    Vec3D &operator+=(const Vec3D &v)
    {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        return *this;
    }
    Vec3D &operator-=(const Vec3D &v)
    {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        return *this;
    }
    Vec3D &operator*=(float f)
    {
        this->x *= f;
        this->y *= f;
        this->z *= f;
        return *this;
    }
    Vec3D &operator/=(float f)
    {
        this->x /= f;
        this->y /= f;
        this->z /= f;
        return *this;
    }
    Vec3D operator+(const Vec3D &v) const
    {
        return Vec3D(*this) += v;
    }
    Vec3D operator-(const Vec3D &v) const
    {
        return Vec3D(*this) -= v;
    }
    Vec3D operator*(float f) const
    {
        return Vec3D(*this) *= f;
    }
    Vec3D operator/(float f) const
    {
        return Vec3D(*this) /= f;
    }

    // Copy the vector
    Vec3D copy() const
    {
        return Vec3D(*this);
    }

    // Set the vector
    Vec3D set(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        return *this;
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
        this->z = 0.0f;
    }

    // Multiply by another vector
    Vec3D multiply(const Vec3D &v)
    {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        return *this;
    }

    // Divide by another vector
    Vec3D divide(const Vec3D &v)
    {
        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;
        return *this;
    }

    // Add a scalar
    Vec3D add(float f)
    {
        this->x += f;
        this->y += f;
        this->z += f;
        return *this;
    }

    // Subtract a scalar
    Vec3D subtract(float f)
    {
        this->x -= f;
        this->y -= f;
        this->z -= f;
        return *this;
    }
};

#endif // VEC3D_HPP