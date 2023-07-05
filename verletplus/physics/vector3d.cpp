#include <iostream>

class Vector2D
{
    public:
        float x;
        float y;
        float z;

        // Constructors
        Vector2D() {
            this->x = 0.0f;
            this->y = 0.0f;
            this->z = 0.0f;
        }
        Vector2D(float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        Vector2D(const Vector2D& v) {
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
        }

        // Operations
        Vector2D& operator=(const Vector2D& v) {
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
            return *this;
        }
        Vector2D& operator+=(const Vector2D& v) {
            this->x += v.x;
            this->y += v.y;
            this->z += v.z;
            return *this;
        }
        Vector2D& operator-=(const Vector2D& v) {
            this->x -= v.x;
            this->y -= v.y;
            this->z -= v.z;
            return *this;
        }
        Vector2D& operator*=(float f) {
            this->x *= f;
            this->y *= f;
            this->z *= f;
            return *this;
        }
        Vector2D& operator/=(float f) {
            this->x /= f;
            this->y /= f;
            this->z /= f;
            return *this;
        }
        Vector2D operator+(const Vector2D& v) const {
            return Vector2D(*this) += v;
        }
        Vector2D operator-(const Vector2D& v) const {
            return Vector2D(*this) -= v;
        }
        Vector2D operator*(float f) const {
            return Vector2D(*this) *= f;
        }
        Vector2D operator/(float f) const {
            return Vector2D(*this) /= f;
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
};
