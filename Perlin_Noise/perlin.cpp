/// A program to procedurally generate Perlin noise

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#include <random>
#include <array>
using namespace std;

// Class for 2D vectors
class Vector2
{
    public:
    float x, y;

    Vector2& operator+=(const Vector2& rhs){
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& rhs){
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vector2& operator*=(const float rhs){
        x *= rhs;
        y *= rhs;
        return *this;
    }

    float dot(const Vector2& rhs){
        return x * rhs.x + y * rhs.y;
    }

    float length(){
        return sqrt(x * x + y * y);
    }

    Vector2 normalize(){
        float l = length();
        return Vector2{x / l, y / l};
    }
};

// Function for generating random vector based on seed and x, y value
Vector2 random_vector(int x, int y, int seed){
    // RNG float values for x and y value of a vector
    
    // Return the vector
}

// Function to get the int grid points 

// Function to calculate noise value

int main(){
    // Image width and height
    const int w = 640;
    const int h = 640;

    const int scale = 50;

    // Generate a grid of random 2D vectors
    array<array<Vector2, 640>, 640> grid;

    // Iterate pixels
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x< w; x++)
        {
            // Apply a scale factor

            // Calculate Perlin Noise value for grid point

            // Convert value and apply pixel color
        }
    }
    // Return the image
}