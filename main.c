#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

vector vectors[8]; // 8 3D co-ordinates

const int cords[8][3] = {
    {0, 0, 0},
    {0, 0, 10},
    {0, 10, 0},
    {0, 10, 10},
    {10, 0, 0},
    {10, 0, 10},
    {10, 10, 0},
    {10, 10, 10}
};

int euler_angles[3];

int main() {
    
    //for(int i = 0; i < 8; i++) {
    //    vectors[i] = setVector(cords[i][0], cords[i][1], cords[i][2], 1);
    //}
    vector v = setVector(4, 1, 0, 0);
    rotateVector(&v, 0.5235);
    printf("%f\n", v.x);
    printf("%f\n", v.y);
    
    return 0;
}