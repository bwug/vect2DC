#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vector.h"

void handleError(const char* errorMessage) {
    printf("%s\n", errorMessage);
    exit(0);
}

vector setVector(float x, float y, float z, int size) {
    /** 
        @param x
        @param y
        @param z
        @param size: {0, 1}
    */    
    vector retVector;
    retVector.x = x; retVector.y = y; retVector.z = z;
    retVector.dim = size; // size = 0 dim = 1; size = 1; dim = 3
    
    // Computes magnitude of each component
    retVector.magnitude = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

    // Calculates the angle between each component and the respective plane
    retVector.angle[0] = acos(x / retVector.magnitude);
    retVector.angle[1] = acos(y / retVector.magnitude);
    if(retVector.dim == 3) {
        retVector.angle[2] = acos(z / retVector.magnitude);
    }
    return retVector;
}

void scalarMult(vector* vect, float scale) {
    if(!vect) return;
    
    float x = vect->x * scale;
    float y = vect->y * scale;
    float z = vect->z * scale;
    
    *vect = setVector(x, y, z, vect->dim);
}

void addComponent(vector* vect, char point, float value) {
    switch(point){
        case 'x':
            vect->x += value;
            break;
        case 'y':
            vect->y += value;
            break;
        case 'z':
            vect->z += value;
            break;
        default:
            printf("Error in addComponent, char input must be {x, y, z}");
            exit(0);
    }
    *vect = setVector(vect->x, vect->y, vect->z, vect->dim);
}

float dotProduct(vector* vectorA, vector* vectorB, int definition) {
    /*
        vector A and B are input vectors, definition is integer in {0, 1}
        that defines whether in co-ordinate or geometric form
        co-ord form returns sum[0, i](a[i]*b[i]) and geometric form returns acos(co-ord / ||A|| ||B||)
    */
    if((vectorA == NULL) || (vectorB == NULL)) handleError("Error in dotProduct: vector pointer is NULL");
    if(definition > 1 || definition < 0) handleError("Error in dotProduct: ensure definition is {0, 1}");
    if(vectorA->dim != vectorB->dim) handleError("Error in dotProduct: vector dimensions not matched");

    float dot;

    // Calculating each component in the dot
    float compA = vectorA->x * vectorB->x;
    float compB = vectorA->y * vectorB->y;
    float compC = vectorA->z * vectorB->z;
    dot = compA + compB + compC;

    if(definition == 1) {
        float angle = acos(dot / (vectorA->magnitude * vectorB->magnitude));
        return angle;
    }
    return dot;
}

vector addVector(vector* vectorA, vector* vectorB) {
    if((vectorA == NULL) || (vectorB == NULL)) handleError("Error in addVector: vector pointer is NULL");
    if(vectorA->dim != vectorB->dim) handleError("Error in addVector: vector dimensions not matched");
    vector vectorC;
    float x = vectorA->x + vectorB->x;
    float y = vectorA->y + vectorB->y;
    float z = vectorA->z + vectorB->z;
    vectorC = setVector(x, y, z, vectorA->dim);
    return vectorC;
}

void rotateVector(vector* vect, float angle) {
    /** 
     * @param vect: Input vector of type &vector
     * @param angle: Float in radians
    */
    if(vect->dim == 2) {
        float x2, y2;
        x2 = cos(angle) * vect->x - sin(angle) * vect->y;
        y2 = sin(angle) * vect->x + cos(angle) * vect->y;
        *vect = setVector(x2, y2, 0, vect->dim);
        return;
    } else {
        return;
    }
}

void matMul(int rows, int cols, float matrix[rows][cols], vector* vect, float * result) {
    if(cols != vect->dim) handleError("Error in matMul, sizes must be equal");

    for(int row = 0; row < rows; row++) {
        result[row] = 0;
        for(int col = 0; col < cols; col++) {
            float t;
            switch(col) {
                case 0: t = vect->x; break;
                case 1: t = vect->y; break;
                case 2: t = vect->z; break;
                default: handleError("Error in matMul");
            }
            result[row] += t * matrix[row][col];
        }
    }
    vect->x = result[0];
    vect->y = result[1];
    vect->z = result[2];
    *vect = setVector(vect->x, vect->y, vect->z, vect->dim);
    return;
}

void rotateX(float matrix[3][3], float angle) {
    angle = angle * PI / 180;
    matrix[0][0] = 1; matrix[0][1] = 0;          matrix[0][2] = 0;
    matrix[1][0] = 0; matrix[1][1] = cos(angle); matrix[1][2] = -sin(angle);
    matrix[2][0] = 0; matrix[2][1] = sin(angle); matrix[2][2] = cos(angle);
}

void rotateY(float matrix[3][3], float angle) {
    angle = angle * PI / 180;
    matrix[0][0] = cos(angle);  matrix[0][1] = 0; matrix[0][2] = sin(angle);
    matrix[1][0] = 0;           matrix[1][1] = 1; matrix[1][2] = 0;
    matrix[2][0] = -sin(angle); matrix[2][1] = 0; matrix[2][2] = cos(angle);
}

void rotateZ(float matrix[3][3], float angle) {
    angle = angle * PI / 180;
    matrix[0][0] = cos(angle); matrix[0][1] = -sin(angle); matrix[0][2] = 0;
    matrix[1][0] = sin(angle); matrix[1][1] = cos(angle);  matrix[1][2] = 0;
    matrix[2][0] = 0;          matrix[2][1] = 0;           matrix[2][2] = 1;
}

void orthMult(vector* vect) {
    matMul(2, 3, orthMatrix, vect, (float[3]){0});
}