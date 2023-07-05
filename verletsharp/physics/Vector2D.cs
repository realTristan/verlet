using System;

namespace physics
{
    class Vector2D
    {
        // x and y components of the vector
        public double x;
        public double y;

        // When two vectors are added
        public Vector2D operator +(Vector2D vec)
        {
            return new Vector2D(this.x + vec.x, this.y + vec.y);
        }

        // When two vectors are subtracted
        public Vector2D operator -(Vector2D vec)
        {
            return new Vector2D(this.x - vec.x, this.y - vec.y);
        }

        // When a vector is multiplied by a scalar
        public Vector2D operator Mult(double scalar)
        {
            this.x *= scalar;
            this.y *= scalar;
        }

        // When a vector is divided by a scalar
        public Vector2D Div(double scalar)
        {
            this.x /= scalar;
            this.y /= scalar;
            return this;
        }
        // When a vector is held to the power of a scalar
        public Vector2D Pow(double scalar)
        {
            this.x = Math.Pow(this.x, scalar);
            this.y = Math.Pow(this.y, scalar);
            return this;
        }

        // Add a scalar
        public Vector2D Add(double b)
        {
            this.x += b;
            this.y += b;
            return this;
        }

        // Subtract a scalar
        public Vector2D Sub(double b)
        {
            this.x -= b;
            this.y -= b;
            return this;
        }

        // Multiply by a vector
        public Vector2D MultVector(Vector2D vec)
        {
            this.x *= vec.x;
            this.y *= vec.y;
            return this;
        }

        // Copy the vector
        public Vector2D Copy()
        {
            return new Vector2D(this.x, this.y);
        }

        // Get the vector
        public (double, double) Get()
        {
            return (this.x, this.y);
        }

        // Vector magnitude
        public double Magnitude()
        {
            return Math.Sqrt(this.x * this.x + this.y * this.y);
        }

        // Dot product of two vectors
        public double Dot(Vector2D vec)
        {
            return this.x * vec.x + this.y * vec.y;
        }
    }
}