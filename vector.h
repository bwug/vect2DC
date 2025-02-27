#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef PI
#define PI 3.141592653
#endif

#ifndef VECTOR_H
#define VECTOR_H

static float orthMatrix[2][3] = {
    {1, 0, 0},
    {0, 1, 0}
}; // Produce a "light" source infinifor(int i = 0; i < size; i++) {

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

void matMul(int rows, int cols, float matrix[rows][cols], vector * vect, float * result);

void rotateX(float matrix[3][3], float angle);
void rotateY(float matrix[3][3], float angle);
void rotateZ(float matrix[3][3], float angle);

void orthMult(vector* vect);

#endif