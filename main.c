// https://www.mathforengineers.com/math-calculators/3D-point-rotation-calculator.html
// Good reference for testing data against

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

#ifndef PI
#define PI 3.141592653
#endif

// macros to find whether on windows or UNIX systems
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

// Creates a static array of structs
vector vectors[8];

// Some example co-ordinates to use
float cords[8][3] = {
    {0, 0, 0},
    {0, 0, 10},
    {0, 10, 0},
    {0, 10, 10},
    {10, 0, 0},
    {10, 0, 10},
    {10, 10, 0},
    {10, 10, 10},
};

int main()
{
    // Allocation of the co-ordinates
    int vSize = sizeof(vectors) / sizeof(vector);
    for(int i = 0; i < vSize; i++) {
        vectors[i] = setVector(cords[i][0], cords[i][1], cords[i][2], 3);
    }

    // Performs N=loop rotations of all M=vSize vectors
    for(int loop = 0; loop < 5; loop++) {
        for(int ind = 0; ind < vSize; ind++) {
            // Statically create three unique matrices for X Y Z rotation
            float matrixX[3][3], matrixY[3][3], matrixZ[3][3];
            
            // Rotates each vector at 30 degrees X Y and Z and uses paramter
            // passing by reference to re-setVector the vector during calculation
            // Then projects using orthoganol projection to set values correctly
            rotateX(matrixX, 30);
            matMul(3, 3, matrixX, &vectors[ind], (float[3]){0});
            orthMult(&vectors[ind]);
            
            rotateY(matrixY, 30);
            matMul(3, 3, matrixY, &vectors[ind], (float[3]){0});
            orthMult(&vectors[ind]);
            
            rotateZ(matrixZ, 30); 
            matMul(3, 3, matrixZ, &vectors[ind], (float[3]){0});
            
            orthMult(&vectors[ind]);

            // Print debugging
            printf("\n=================================\n");
            printf("%f | %f | %f", vectors[ind].x, vectors[ind].y, vectors[ind].z);
            printf("\n=================================\n");
        }
    }
    return 0;
}