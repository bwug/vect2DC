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
        * x, y, z :   float -> inputs by the user
        * size    :   int   -> input by the user to determine dimension
    */
    if(size < 0 || size > 1){
        handleError("Error in makeVector: size not in {0, 1}");
    }
    
    vector retVector;
    retVector.x = x; retVector.y = y; retVector.z = z;
    retVector.dim = size + 2; // size = 0 dim = 1; size = 1; dim = 3
    
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
    
    *vect = setVector(x, y, z, (vect->dim - 2));
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
    *vect = setVector(vect->x, vect->y, vect->z, (vect->dim - 2));
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
    int size = vectorA->dim - 2;
    vectorC = setVector(x, y, z, size);
    return vectorC;
}

void rotateVector(vector* vect, float angle) {
    /** 
     * @param vect: Input vector of type &vector
     * @param angle: Float in radians
    */
    if(vect->dim-2 == 0) {
        float beta = angle * 180 / PI;
        float x2, y2;
        x2 = cos(beta) * vect->x - sin(beta) * vect->y;
        y2 = sin(beta) * vect->x + cos(beta) * vect->y;
        *vect = setVector(x2, y2, 0, (vect->dim-2));
        return;
    } else {
        return;
    }
}