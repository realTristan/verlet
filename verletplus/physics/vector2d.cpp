#include <iostream>

class Vector2D
{
    public:
        float x;
        float y;

        // Constructors
        Vector2D() {
            this->x = 0.0f;
            this->y = 0.0f;
        }
        Vector2D(float x, float y) {
            this->x = x;
            this->y = y;
        }
        Vector2D(const Vector2D& v) {
            this->x = v.x;
            this->y = v.y;
        }

        // Operations
        Vector2D& operator=(const Vector2D& v) {
            this->x = v.x;
            this->y = v.y;
            return *this;
        }
        Vector2D& operator+=(const Vector2D& v) {
            this->x += v.x;
            this->y += v.y;
            return *this;
        }
        Vector2D& operator-=(const Vector2D& v) {
            this->x -= v.x;
            this->y -= v.y;
            return *this;
        }
        Vector2D& operator*=(float f) {
            this->x *= f;
            this->y *= f;
            return *this;
        }
        Vector2D& operator/=(float f) {
            this->x /= f;
            this->y /= f;
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
        }
};
