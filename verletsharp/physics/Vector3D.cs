using System;

namespace physics
{
    class Vector3D
    {
        // x, y, and z components of the vector
        public double x;
        public double y;
        public double z;

        // When two vectors are added
        public Vector3D operator +(Vector3D vec)
        {
            this.x += vec.x;
            this.y += vec.y;
            this.z += vec.z;
            return this;
        }

        // When two vectors are subtracted
        public Vector3D operator -(Vector3D vec)
        {
            this.x -= vec.x;
            this.y -= vec.y;
            this.z -= vec.z;
            return this;
        }

        // When a vector is multiplied by a scalar
        public Vector3D operator *(double scalar)
        {
            this.x *= scalar;
            this.y *= scalar;
            this.z *= scalar;
            return this;
        }

        // When a vector is divided by a scalar
        public Vector3D operator /(double scalar)
        {
            this.x /= scalar;
            this.y /= scalar;
            this.z /= scalar;
            return this;
        }
        // When a vector is held to the power of a scalar
        public Vector3D operator ^(double scalar)
        {
            this.x **= scalar;
            this.y **= scalar;
            this.z **= scalar;
            return this;
        }

        // Add a scalar
        public Vector3D AddScalar(double b)
        {
            this.x += b;
            this.y += b;
            this.z += b;
            return this;
        }

        // Subtract a scalar
        public Vector3D SubScalar(double b)
        {
            this.x -= b;
            this.y -= b;
            this.z -= b;
            return this;
        }

        // Multiply by a vector
        public Vector3D MultVector(Vector3D vec)
        {
            this.x *= vec.x;
            this.y *= vec.y;
            this.z *= vec.z;
            return this;
        }

        // Copy the vector
        public Vector3D Copy()
        {
            return new Vector3D(this.x, this.y, this.z);
        }

        // Get the vector
        public (double, double, double) Get()
        {
            return (this.x, this.y, this.z);
        }

        // Vector magnitude
        public double Magnitude()
        {
            return Math.Sqrt(this.x * this.x + this.y * this.y + this.z * this.z);
        }

        // Dot product of two vectors
        public double Dot(Vector3D vec)
        {
            return this.x * vec.x + this.y * vec.y + this.z * vec.z;
        }
    }
}