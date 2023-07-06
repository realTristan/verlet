#include <iostream>
#include <math.h>

#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

class Vector3D
{
    public:
        float x;
        float y;
        float z;

        // Constructors
        Vector3D() {
            this->x = 0.0f;
            this->y = 0.0f;
            this->z = 0.0f;
        }
        Vector3D(float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        Vector3D(const Vector3D& v) {
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
        }

        // Operations
        Vector3D& operator=(const Vector3D& v) {
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
            return *this;
        }
        Vector3D& operator+=(const Vector3D& v) {
            this->x += v.x;
            this->y += v.y;
            this->z += v.z;
            return *this;
        }
        Vector3D& operator-=(const Vector3D& v) {
            this->x -= v.x;
            this->y -= v.y;
            this->z -= v.z;
            return *this;
        }
        Vector3D& operator*=(float f) {
            this->x *= f;
            this->y *= f;
            this->z *= f;
            return *this;
        }
        Vector3D& operator/=(float f) {
            this->x /= f;
            this->y /= f;
            this->z /= f;
            return *this;
        }
        Vector3D operator+(const Vector3D& v) const {
            return Vector3D(*this) += v;
        }
        Vector3D operator-(const Vector3D& v) const {
            return Vector3D(*this) -= v;
        }
        Vector3D operator*(float f) const {
            return Vector3D(*this) *= f;
        }
        Vector3D operator/(float f) const {
            return Vector3D(*this) /= f;
        }

        // Copy the vector
        Vector3D copy() const {
            return Vector3D(*this);
        }

        // Set the vector
        Vector3D set(float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
            return *this;
        }

        // Get the magnitude of the vector
        float magnitude() const {
            return sqrt(this->x * this->x + this->y * this->y);
        }

        // Get the vector and return the x and y as a tuple
        std::tuple<float, float> get() const {
            return std::make_tuple(this->x, this->y);
        }

        // Set everything to zero
        void zero() {
            this->x = 0.0f;
            this->y = 0.0f;
            this->z = 0.0f;
        }

        // Multiply by another vector
        Vector3D multiply(const Vector3D& v) {
            this->x *= v.x;
            this->y *= v.y;
            this->z *= v.z;
            return *this;
        }

        // Divide by another vector
        Vector3D divide(const Vector3D& v) {
            this->x /= v.x;
            this->y /= v.y;
            this->z /= v.z;
            return *this;
        }

        // Add a scalar
        Vector3D add(float f) {
            this->x += f;
            this->y += f;
            this->z += f;
            return *this;
        }

        // Subtract a scalar
        Vector3D subtract(float f) {
            this->x -= f;
            this->y -= f;
            this->z -= f;
            return *this;
        }
};

#endif