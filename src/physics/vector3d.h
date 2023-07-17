#ifndef PHYSICS_VEC3D_H
#define PHYSICS_VEC3D_H

#include <math.h>
#include <tuple>

template <typename T>
class Vec3D
{
public:
    T x;
    T y;
    T z;

    // Constructors
    Vec3D()
    {
        this->x = 0.0f;
        this->y = 0.0f;
        this->z = 0.0f;
    }
    Vec3D(T x, T y, T z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Vec3D(const Vec3D<T> &v)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
    }

    // Operations
    Vec3D<T> &operator=(const Vec3D<T> &v)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
        return *this;
    }
    Vec3D<T> &operator+=(const Vec3D<T> &v)
    {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        return *this;
    }
    Vec3D<T> &operator-=(const Vec3D<T> &v)
    {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        return *this;
    }
    Vec3D<T> &operator*=(T f)
    {
        this->x *= f;
        this->y *= f;
        this->z *= f;
        return *this;
    }
    Vec3D<T> &operator/=(T f)
    {
        this->x /= f;
        this->y /= f;
        this->z /= f;
        return *this;
    }
    Vec3D<T> operator+(const Vec3D<T> &v) const
    {
        return Vec3D<T>(*this) += v;
    }
    Vec3D<T> operator-(const Vec3D<T> &v) const
    {
        return Vec3D<T>(*this) -= v;
    }
    Vec3D<T> operator*(T f) const
    {
        return Vec3D<T>(*this) *= f;
    }
    Vec3D<T> operator/(T f) const
    {
        return Vec3D<T>(*this) /= f;
    }

    // Copy the vector
    Vec3D<T> copy() const
    {
        return Vec3D<T>(*this);
    }

    // Set the vector
    Vec3D<T> set(T x, T y, T z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        return *this;
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
        this->z = 0.0f;
    }

    // Multiply by another vector
    Vec3D<T> multiply(const Vec3D<T> &v)
    {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        return *this;
    }

    // Divide by another vector
    Vec3D<T> divide(const Vec3D<T> &v)
    {
        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;
        return *this;
    }

    // Add a scalar
    Vec3D<T> add(T f)
    {
        this->x += f;
        this->y += f;
        this->z += f;
        return *this;
    }

    // Subtract a scalar
    Vec3D<T> subtract(T f)
    {
        this->x -= f;
        this->y -= f;
        this->z -= f;
        return *this;
    }
};

#endif // PHYSICS_VEC3D_H