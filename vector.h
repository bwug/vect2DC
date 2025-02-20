#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef PI
#define PI 3.14
#endif

#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    float x;
    float y;
    float z;
    int dim;
    float magnitude;
    float angle[3]; // Angle to the X, Y and Z axes, angle[2] = 0 if dim == 2;
} vector;

void handleError(const char* errorMessage);

vector setVector(float x, float y, float z, int size);

void scalarMult(vector* vect, float scale);

void addComponent(vector* vect, char point, float value);

float dotProduct(vector* vectorA, vector* vectorB, int definition);

vector addVector(vector* vectorA, vector* vectorB);

void rotateVector(vector* vect, float angle);

#endif