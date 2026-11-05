/// DEBUG NOTES
// Noise pattern is not entirely random
// Using srand inside of random_vector causing seed to not be random
// Regions of pixels that reach full black or white rebound to the inverse color

/// A program to procedurally generate Perlin noise
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>
#include "Vector2.hpp"
using namespace std;

// Image width and height
// constant for now, change to input later
const int w = 500;
const int h = 500;
const float scale = 65;
const int seed = 0;

unsigned char pixel[w * h * 3];

// Function for generating random vector based on seed and x, y value
Vector2 random_vector(int x, int y, int seed){
    // RNG an angle value given an x and y position and seed
    srand(x * 1000 + y + seed);
    float angle = rand() % 360;

    // Return the Vector2 object using cos and sin of the angle
    Vector2 random_v = {cos(angle), sin(angle)};
    return random_v;
}

// Function to get the int grid points value for a given (x, y) pixel
Vector2 get_grid_points(float x, float y, Vector2 grid[h][w]){
    Vector2 grid_val = grid[int(floor(y))][int(floor(x))];
    return grid_val;
}

// Dot product of two vectors
float dot(Vector2 rhs, Vector2 lhs){
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

// Fade function for smoothing
float fade(float t){
    return ((6 * t - 15) * t + 10) * t * t * t;
}

// Function to calculate noise value for an (x, y) pixel
float perlin_noise2D(float x, float y, Vector2 grid[h][w]){
    // The factors used
    int ix = int(floor(x));
    int iy = int(floor(y));

    float x_factor = x - ix;
    float y_factor = y - iy;

    // The four corners around the pixel
    Vector2 v00 = {x_factor, y_factor};
    Vector2 v10 = {x_factor - 1, y_factor};
    Vector2 v01 = {x_factor, y_factor - 1};
    Vector2 v11 = {x_factor - 1, y_factor - 1};

    // dot products of each corner vector on the grid with the pixel vector
    float dot00 = dot(v00, get_grid_points(ix, iy, grid));
    float dot10 = dot(v10, get_grid_points(ix + 1, iy, grid));
    float dot01 = dot(v01, get_grid_points(ix, iy + 1, grid));
    float dot11 = dot(v11, get_grid_points(ix + 1, iy + 1, grid));

    // interpolate the dot products to find the value of the pixel
    float u = fade(x_factor);
    float v = fade(y_factor);

    float a = (1 - u) * dot00 + u * dot10;
    float b = (1 - u) * dot01 + u * dot11;
    float c = (1 - v) * a + v * b;

    return c;
}

int main(){
    // Generate a 2D grid of random Vector2 objects
    Vector2 grid[h][w];
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            grid[y][x] = random_vector(x, y, seed);
        }
    }

    // Iterate pixels
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x< w; x++)
        {
            // Apply scale factor
            float sx = x / scale;
            float sy = y / scale;

            // Calculate Perlin Noise value for grid point
            float perlin = perlin_noise2D(sx, sy, grid);

            // Convert value to intensity value (0-255) for grayscale image
            int v = int(floor((perlin + 1) * 255 - 255/2));

            // Set pixel value in image
            pixel[(y * w + x) * 3 + 0] = v; // Red channel
            pixel[(y * w + x) * 3 + 1] = v; // Green channel
            pixel[(y * w + x) * 3 + 2] = v; // Blue channel
        }
    }
    // Write the image to a PNG
    stbi_write_png("perlin_noise.png", w, h, 3, pixel, w * 3);
    return 0;
}