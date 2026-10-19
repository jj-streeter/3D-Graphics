// Transcribed from YouTube tutorial: https://youtu.be/p09i_hoFdd0?si=PKn2ySOXoK6-hmZG

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

float A, B, C;

float cubeWidth = 20;
float width = 160, height = 44;

// Buffer to hold the ASCII characters and z-buffer for depth
float zBuffer[160 * 44];
char buffer[160 * 44];

int backgroundASCIICode = ' ';
int distanceFromCam = 100;

float K1 = 40; // constant affecting the size of the cube on the screen

float incrementSpeed = 0.2;
float x, y, z;

float ooz; // reciprocal of z

int xp, yp; // projected x and y coordinates

int idx; // index in buffer arrays

// Calculate x coordinate of cube surface point after rotation
float calculateX(int i, int j, int k) {
    return 
    j * sin(A) * sin(B) * cos(C) - 
    k * cos(A) * sin(B) * cos(C) +
    j * cos(A) * sin(C) + 
    k * sin(A) * sin(C) + 
    i * cos(B) * cos(C);
}

// Calculate y coordinate of cube surface point after rotation
float calculateY(int i, int j, int k) {
    return 
    j * cos(A) * cos(C) + 
    k * sin(A) * cos(C) - 
    j * sin(A) * sin(B) * sin(C) + 
    k * cos(A) * sin(B) * sin(C) - 
    i * cos(B) * sin(C);
}

// Calculate z coordinate of cube surface point after rotation
float calculateZ(int i, int j, int k) {
    return
    k * cos(A) * cos(B) -
    j * sin(A) * cos(B) +
    i * sin(B);
}

// Calculate the surface point of the cube and update the buffer and zBuffer
void calculateForSurface(float cubeX, float cubeY, float cubeZ, int ch) {
    // Calculate 3D coordinates after rotation
    x = calculateX(cubeX, cubeY, cubeZ);
    y = calculateY(cubeX, cubeY, cubeZ);
    z = calculateZ(cubeX, cubeY, cubeZ) + distanceFromCam;

    ooz = 1/z;

    // Project the 3D coordinates to 2D screen coordinates
    xp = (int)(width/2 - 2 * cubeWidth + K1 * ooz * x * 2);
    yp = (int)(height/2 + K1 * ooz * y);

    // Calculate the index in the buffer and zBuffer arrays
    idx = xp + yp * width;

    // Update the buffer and zBuffer if the point is within bounds and closer than previous points
    if (idx >= 0 && idx < width * height) {
        if (ooz > zBuffer[idx]) {
            zBuffer[idx] = ooz;
            buffer[idx] = ch;
        }
    }}

int main() {
    printf("\x1b[2J");
    while (1) {
        memset(buffer, backgroundASCIICode, width * height);
        memset(zBuffer, 0, width * height * 4);
        for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) {
            for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed) {
                // Calculate the 6 surfaces of the cube
                calculateForSurface(cubeX, cubeY, -cubeWidth, '#');
                calculateForSurface(cubeWidth, cubeY, cubeX, '.');
                calculateForSurface(-cubeWidth, cubeY, -cubeX, '@');
                calculateForSurface(-cubeX, cubeY, cubeWidth, '$');
                calculateForSurface(cubeX, -cubeWidth, -cubeY, '~');
                calculateForSurface(cubeX, cubeWidth, cubeY, '/');
            }
        }
        printf("\x1b[H");

        // Print the buffer to the console
        for (int k = 0; k < width * height; k++) {
            putchar(k % (int)width ? buffer[k] : 10);
        }

        // Increment the rotation angles for the next frame
        A += 0.02;
        B += 0.02;

        // Sleep for a short duration to control the frame rate
        usleep(2000);
    }
    return 0;
}